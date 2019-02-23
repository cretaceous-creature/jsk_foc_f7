/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

//define the pin to the channel
#define Channel_1 GPIO_PIN_11
#define Channel_2 GPIO_PIN_12
#define Channel_3 GPIO_PIN_0
#define Channel_4 GPIO_PIN_1
#define Channel_5 GPIO_PIN_15
#define Channel_6 GPIO_PIN_10
//define timer value
#define COUNTER_RELOAD 50000
//define the duty
#define MAX_DUTY 54000
//param to store the counter
static uint16_t c_counter[6];
uint8_t radio_flag;
void Delay(uint16_t speed)
{
	uint16_t i;
	while(speed!=0)
	{
		speed--;
		for(i=0;i<400;i++);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//all the external pin interrupts come in this call back
	uint16_t temp_timer = TIM8->CNT;
	float signal_interval;
	Delay(1);
	switch(GPIO_Pin)
	{
	case Channel_1:  //right motor, 1.5->1ms forward, 1.5->2ms backward
	{
		if(!(GPIOC->IDR & Channel_1))
		{
			//falling
			signal_interval = (temp_timer - c_counter[0])>0?
					(temp_timer - c_counter[0]):
					(temp_timer - c_counter[0] + COUNTER_RELOAD);
			//from 1000-2000 indicates time in micro seconds
			if(radio_flag) //in remote control mode
			{
				htim4.Instance->CCR1 = (float)(MAX_DUTY * signal_interval/2000);
			}
		}
		else
			//rising
			c_counter[0] = temp_timer;
		break;
	}
	case Channel_2:
	{
		if(!(GPIOC->IDR & Channel_2))
		{
			//falling

		}
		else
			//rising
			c_counter[1] = temp_timer;

		break;
	}
	case Channel_3:
	{
		if(!(GPIOD->IDR & Channel_3))
		{
			//falling

		}
		else
			//rising
			c_counter[2] = temp_timer;

		break;
	}
	case Channel_4://left motor, 1.5->2ms forward, 1.5->1ms backward
	{
		if(!(GPIOD->IDR & Channel_4))
		{
			//falling
			signal_interval = (temp_timer - c_counter[3])>0?
					(temp_timer - c_counter[3]):
					(temp_timer - c_counter[3] + COUNTER_RELOAD);
			//from 1000-2000 indicates time in micro seconds
			if(radio_flag) //in remote control mode
			{
				htim4.Instance->CCR2 = (float)(MAX_DUTY * signal_interval/2000);
			}
		}
		else
			//rising
			c_counter[3] = temp_timer;

		break;
	}
	case Channel_5:
	{
		if(!(GPIOA->IDR & Channel_5))
		{
			//falling
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET);
			signal_interval = (temp_timer - c_counter[4])>0?
					(temp_timer - c_counter[4]):
					(temp_timer - c_counter[4] + COUNTER_RELOAD);
			if(signal_interval < 1500) //less than 1.5ms  1ms
				radio_flag = 0;

			else						//more than 1.5ms  2ms
				radio_flag = 1;

		}
		else
		{
			//rising
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);
			c_counter[4] = temp_timer;
		}

		break;
	}
	case Channel_6:
	{
		if(!(GPIOC->IDR & Channel_6))
		{
			//falling

		}
		else
			//rising
			c_counter[5] = temp_timer;
		break;
	}
	default:
		break;
	}
}
