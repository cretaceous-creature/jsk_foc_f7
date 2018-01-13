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
//this API should run at a frequency of
// Fovsr*Iovsr*0.1us +- (half encoder data period)
// 256*2*0.1us +- 4us = 51.2 +- 4 us..
//PWM  50Khz, 20us, duty should be from 0~2160..
//centralaligned, frequency should be half..
#define setMotorDuty(dutyA,dutyB,dutyC) {htim1.Instance->CCR1=dutyA, \
		htim1.Instance->CCR2=dutyB, \
		htim1.Instance->CCR3=dutyC;}

#define sq3 1.732051
/*
 * clarke transform: 3 120 phase to 2 orthogonal phase
 */
inline void ClarkeTrans(float a, float b, float *apha, float *beta)
{
	*apha = 1.5 * a;
	*beta = sq3 * b + (sq3 * a)/2;
}
/*
 * reverse clarke transform: 2 orthogonal phase to 3 120 phase
 */
inline void RevClarkeTrans(float *a, float *b, float *c, float apha, float beta)
{
	*a = 2*apha/3;
	*b = -apha/3 + beta/sq3;
	*c = -apha/3 - beta/sq3;
}
/*
 * park transform: 2 orthogonal phase to  Dq coordinate consider the theta
 */
inline void ParkTrans(float apha, float beta, float theta, float *i_d, float *i_q)
{
	*i_d = apha*cos(theta) + beta*sin(theta);
	*i_q = -apha*sin(theta) + beta*cos(theta);
}
/*
 * reverse park transform: Dq to 2 orthogonal phase
 */
inline void RevParkTrans(float *apha, float *beta, float theta, float i_d, float i_q)
{
	*apha = i_d*cos(theta) - i_q*sin(theta);
	*beta = i_d*sin(theta) + i_q*cos(theta);
}



/*
 * Start FOC control task...
 * clark -> park -> control -> rev park -> rev clark -> PWM
 *
 */

void StartcontrolTask(void const * argument)
{
	uint16_t duty_a = 0;
	for(;;)
	{
		CURDATA shuntdata;
		if(xQueueReceive(shuntQueueHandle,&shuntdata,2)==pdPASS)
		{
			//copy the data use float type.
			//as we have FPU, fast..
			float c_a = ((float)shuntdata.cur_a)/100;
			float c_b = ((float)shuntdata.cur_b)/100;
			float c_c = ((float)shuntdata.cur_c)/100;
			//now the unity is 1 for 1ma..
			//clarke
			float c_apha, c_beta;
			ClarkeTrans(c_a, c_b, &c_apha, &c_beta);
			//then park...


//			setMotorDuty(duty_a,0,0);
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
