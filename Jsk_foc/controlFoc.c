/**
 *
 * Jsk foc project
 *
 * foc control folder,
 *
 * obtain the current and encoder data to do the foc control
 *
 */

#include "gpio.h"
#include "dfsdm.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"
#include "math.h"
extern osMessageQId shuntQueueHandle;
extern osMessageQId enchallQueueHandle;
extern osMessageQId conresQueueHandle;
//this API should run at a frequency of
// Fovsr*Iovsr*0.1us +- (half encoder data period)
// 256*2*0.1us +- 4us = 51.2 +- 4 us..
//PWM  50Khz, 20us, duty should be from 0~2160..
//centralaligned, frequency should be half..
#define MAXDUTY 2160
#define VOLTSUP 12
#define PHASERES 0.21/3
#define setMotorDuty(dutyA,dutyB,dutyC) {htim1.Instance->CCR1=dutyA, \
		htim1.Instance->CCR2=dutyB, \
		htim1.Instance->CCR3=dutyC;}

#define sq3 1.732051
#define CENTERCOUNT 500
#define MAXCOUNT 2000
#define PI 3.1416
#define T_ID 0
/*
 * clarke transform: 3 120 phase to 2 orthogonal phase
 */
inline void ClarkeTrans(volatile float a, volatile float b, volatile float *apha, volatile float *beta)
{
	*apha = 1.5 * a;
	*beta = sq3 * b + (sq3 * a)/2;
}
/*
 * reverse clarke transform: 2 orthogonal phase to 3 120 phase
 */
inline void RevClarkeTrans(volatile float *va, volatile float *vb, volatile float *vc, volatile float apha, volatile float beta)
{
	*va = 2*apha/3;
	*vb = -apha/3 + beta/sq3;
	*vc = -apha/3 - beta/sq3;
}
/*
 * rk transform: 2 orthogonal phase to  Dq coordinate consider the theta
 */
inline void ParkTrans(float apha, float beta, float theta, float *i_d, float *i_q)
{
	*i_d = apha*cos(theta) + beta*sin(theta);
	*i_q = -apha*sin(theta) + beta*cos(theta);
}
/*
 * reverse park transform: Dq to 2 orthogonal phase
 */
inline void RevParkTrans(float *apha, float *beta, float theta, float v_d, float v_q)
{
	*apha = v_d*cos(theta) - v_q*sin(theta);
	*beta = v_d*sin(theta) + v_q*cos(theta);
}

/*
 * SVMDuty
 */
inline void SVMDuty(volatile float *v_a, volatile float *v_b, volatile float *v_c)
{
	float v_big, v_small;
	//note that the duty direction and the current plus direction have a -1
	v_big = *v_a>*v_b?*v_a:*v_b;
	v_big = v_big>*v_c?v_big:*v_c;
	*v_a -= v_big;
	*v_b -= v_big;
	*v_c -= v_big;
	v_small = *v_a<*v_b?*v_a:*v_b;
	v_small = v_small<*v_c?v_small:*v_c;
	if(v_small<-MAXDUTY+1) // <-2159..
	{
		*v_a *= -(MAXDUTY-1)/v_small;
		*v_b *= -(MAXDUTY-1)/v_small;
		*v_c *= -(MAXDUTY-1)/v_small;  //then the data is proportional under maxduty
	}

}

/*
 * Start FOC control task...
 * clark -> park -> control -> rev park -> rev clark -> PWM
 *
 */
void StartcontrolTask(void const * argument)
{
	float integra_Cd = 0;
	float integra_Cq = 0;
	float vd_st = 0, vq_st = 0;
	CONRES conres;
	for(;;)
	{
		CURDATA shuntdata;
		ENCHD encdata;
		if(xQueueReceive(shuntQueueHandle,&shuntdata,2)==pdPASS)
		{
			//to test the calculation time.. arount 25us
			//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_12);
			//copy the data use float type.
			//as we have FPU, fast..
			volatile float c_a = ((float)shuntdata.cur_a)/100;
			volatile float c_b = ((float)shuntdata.cur_b)/100;
			volatile float c_c = ((float)shuntdata.cur_c)/100;
			//now the unity is 1 for 1ma..

			//obtain the encoder angle
			if(xQueuePeek(enchallQueueHandle,&encdata,0)!=pdPASS)
				return;
			//clarke
			volatile float c_apha, c_beta;
			ClarkeTrans(c_a, c_b, &c_apha, &c_beta);
			//then park...
			volatile float theta = 4 * PI * (encdata.recon_counter - CENTERCOUNT
					+ shuntdata.centeroffset) / MAXCOUNT;
			volatile float c_d, c_q;
			ParkTrans(c_apha,c_beta,theta,&c_d,&c_q);

			/*
			 * PID control
			*/
			//P part
			volatile float er_q = shuntdata.target_cur - c_q;
			volatile float er_d = T_ID - c_d;
			//debug view.. send back to PC to view the control result
			conres.feedback_cq = ((int16_t)c_q + conres.feedback_cq)/2;
			conres.feedback_cd = ((int16_t)c_d + conres.feedback_cd)/2;

			//I part..
			integra_Cd +=  er_d;
			integra_Cq +=  er_q;
			if(integra_Cq>1000)
				integra_Cq = 1000;
			if(integra_Cq<-1000)
				integra_Cq = -1000;
			if(integra_Cd>1000)
				integra_Cd = 1000;
			if(integra_Cd<-1000)
				integra_Cd = -1000;

			//get the control voltage
			volatile float v_d = shuntdata.Kp * er_d + shuntdata.Ki * integra_Cd * 51.2 * 1e-6;
			volatile float v_q = shuntdata.Kp * er_q + shuntdata.Ki * integra_Cq * 51.2 * 1e-6;
			v_d *= 0.1; v_q *=0.1;

#define MAXVqd 4000000
			if((vd_st + v_d) <MAXVqd && (vd_st +v_d)>-MAXVqd &&
					(vq_st + v_q)<MAXVqd && (vq_st + v_q)>-MAXVqd)
			{
				vd_st += v_d;  //equals to Kp..
				vq_st += v_q;
			}

			//reverse park...
			volatile float v_apha,v_beta;
			RevParkTrans(&v_apha,&v_beta,theta,vd_st,vq_st);

			//reverse clarke
			volatile float v_a,v_b,v_c;
			RevClarkeTrans(&v_a,&v_b,&v_c,v_apha,v_beta);

			//mapping the v_a v_b v_c to the real voltage and to the max duty of 2160
			v_a *= VOLTSUP * PHASERES/1000;  //because of 1 is 1 mv
			v_b *= VOLTSUP * PHASERES/1000;
			v_c *= VOLTSUP * PHASERES/1000;

			//find the bigest one.. sent the duty to 0;
			SVMDuty(&v_a,&v_b,&v_c);
			volatile uint16_t cont_a = (uint16_t)(-v_a);
			volatile uint16_t cont_b = (uint16_t)(-v_b);
			volatile uint16_t cont_c = (uint16_t)(-v_c);
			setMotorDuty(cont_a, cont_b, cont_c);
			//for debug view..
			conres.duty_a = cont_a;conres.duty_b = cont_b;conres.duty_c = cont_c;
			xQueueOverwrite(conresQueueHandle,&conres);
			//to test the control frequency
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_12);
		}
		else
		{
			//1ms no current data was receieved...something is wrong...error handle
			//  _Error_Handler("controlFOC, 1ms no data receved.",500);
			osDelay(1);
		}
  }
}
