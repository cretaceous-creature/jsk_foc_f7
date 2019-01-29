/**
 *
 * Jsk foc project
 *
 * idletasks folder,
 *
 * LEDblue task, LEDgreen task and Iwdg watch dog feed task...
 *
 * also buzzer tasks
 *
 */

#include "main.h"
#include "gpio.h"
//#include "iwdg.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "usart.h"

//queue
extern osMessageQId buzzerQueueHandle;
extern osMessageQId rythmQueueHandle;
//mutex
extern osMutexId buzzerMutexHandle;

//#define ENSOUND

#ifdef ENSOUND
#define SetbuzzerFreq(freq) {htim2.Instance->ARR=(uint32_t)((1e+6)/freq), \
htim2.Instance->CCR1=htim2.Instance->ARR/2;}
#else
#define SetbuzzerFreq(freq) {htim2.Instance->ARR=(uint32_t)((1e+6)/freq), \
htim2.Instance->CCR1=0;}
#endif

/* StartledblueTask function */
void StartledblueTask(void const * argument)
{
	for(;;)
	{
		HAL_GPIO_TogglePin(LEDBLUE_GPIO_Port,LEDBLUE_Pin);
		osDelay(500);
	}
}

/* StartledgreenTask function */
void StartledgreenTask(void const * argument)
{
	for(;;)
	{
		HAL_GPIO_TogglePin(LEDGREEN_GPIO_Port,LEDGREEN_Pin);
		osDelay(1000);
	}
}

/* StartiwdgTask function */
void StartiwdgTask(void const * argument)
{
	for(;;)
	{
		//feed the watchdog every 100 msec
//		HAL_IWDG_Refresh(&hiwdg);
		osDelay(50);
	}
}
void StartbuzzerrythmTask(void const * argument)
{
#define SONGNUM 2
#define SONGLENGTH 50
	uint16_t rythm[SONGNUM][SONGLENGTH]={{1013, 2013, 2015, 8000, 1015, 2015, 4000,
			1013, 2013, 2012, 8000, 1011, 2011, 4000, 1012, 2012, 2013, 8000, 1015, 2015, 2013, 1012, 1000,
			1013, 2013, 2015, 8000, 1015, 2015, 4000,
			1021, 2021, 2022, 8000, 1023, 2023, 2000,
			1022, 2022, 2021, 1022, 1016, 4016, 1021, 1021, 0},
			{}};
	volatile uint16_t i = 0;
	for(;;)
	{
		if(xSemaphoreTake(buzzerMutexHandle,0)==pdPASS)
		{
			if(xQueueSend(buzzerQueueHandle,&rythm[0][i],0)==pdPASS)
			{
				i=i==SONGLENGTH-1?0:i+1;
			}
			xSemaphoreGive(buzzerMutexHandle);
		}
		osDelay(10);
	}
}

void StartbuzzertoneTask(void const * argument)
{
	uint16_t tonedata;
#define timebase 1000  //60 per min
	const float tonetable_white[7] = {261.63, 293.66, 329.63, 349.23,
			392, 440, 493.88};
	const float tonetable_black[5] = {277.18, 311.13, 369.99,
			415.30/4, 466.16/4};
	volatile float tonefreq = 0, time = 0;;
	for(;;)
	{
		//ring the buzzer
		if(xQueueReceive(buzzerQueueHandle,&tonedata,10)==pdPASS)
		{
			uint16_t black,white,num;
			//here we define a tone..
			//number is ****, 1,time 2,black 3,num 4,white
			//black goes first, num decides the height of the tone..
			//if all is 0 then no sound...
			//like 512 should be black[5-1] = 466.16/4   la+
			//013 should be white[3-1] = 329.63/4    mi
			//023 should be 2 * white[3-1] = 329.63/2
			xSemaphoreTake(buzzerMutexHandle,1);// take the mutex
			time = tonedata/1000;
			black = (tonedata%1000)/100;
			num = (tonedata%100)/10;
			white  = tonedata%10;
			if((tonedata%1000) != 0)
			{
				if(black)
					tonefreq = tonetable_black[black-1] * num *2 ;
				else
					tonefreq = tonetable_white[white-1] * num *2;
				//ring
				SetbuzzerFreq(tonefreq);
			}
			else
			{
				htim2.Instance->CCR1=htim2.Instance->CCR1 = 0;
				tonefreq = 0;
			}
			if(time!=0)
				osDelay(500/time); //time is used to shorter the sound..
			xSemaphoreGive(buzzerMutexHandle);
		}
		else
		{
			htim2.Instance->CCR1=htim2.Instance->CCR1 = 0;
			osDelay(10);
		}
	}
}
