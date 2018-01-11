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
extern osMessageQId shuntQueueHandle;
//this API should run at a frequency of
// Fovsr*Iovsr*0.1us +- (half encoder data period)
// 256*2*0.1us +- 4us = 51.2 +- 4 us..
//PWM  50Khz, 20us, duty should be from 0~2160..
//centralaligned, frequency should be half..
#define setMotorDuty(dutyA,dutyB,dutyC) {htim1.Instance->CCR1=dutyA, \
		htim1.Instance->CCR2=dutyB, \
		htim1.Instance->CCR3=dutyC;}
void StartcontrolTask(void const * argument)
{
	uint16_t duty_a = 0;
	for(;;)
	{
		CURDATA shuntdata;
		if(xQueueReceive(shuntQueueHandle,&shuntdata,2)==pdPASS)
		{

			//to test the control frequency
			volatile int32_t a = shuntdata.cur_a;
			volatile int32_t b = shuntdata.cur_b;
			volatile float cc = a+b;
//			setMotorDuty(duty_a,0,0);
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
