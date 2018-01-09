/**
 *
 * Jsk foc project
 *
 * ISRs folder,
 *
 * hall sensor and encoder receiver from intelligent board
 *
 * get the data from DMA and send to PC through UART1..
 *
 * get the DFSDM0 1 data...
 *
 */

#include "gpio.h"
#include "usart.h"
#include "dma.h"
#include "dfsdm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"

//uart4 DMA data buffer
//0xf8, 1xxx|xxxx, 011x|xxxx, byte, byte
#define TXHEADER 0xF8
uint8_t enchall_buff[5];
static ENCHD enchall;

//current data from dfsdm..
int32_t cur_u;
int32_t cur_v;

//queue handle
extern osMessageQId enchallQueueHandle;
extern osMutexId encdataMutexHandle;

/***********
 * UART4 error handler
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//error...
	_Error_Handler("isrSensors.c, uart error",41);
}

/***********
 * UART4 receive complete callback..
 * obtain hall sensor, encoder, etc data from intelligent board.
 * data updating rate <10us  ~100khz
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart4.Instance) //not necessary to check..
	{
		for(int i=0; i<5; i++)
		{
			if(enchall_buff[i] == TXHEADER)
			{
				uint8_t s = i==4?0:i+1; //second byte  1xxx|xxxx
				uint8_t t = s==4?0:s+1; //third byte   011x|xxxx
				if(enchall_buff[s]&0x80&&enchall_buff[t]&0x60)
				{
					//then we can obtain the correct bytes...
					enchall.mseq_out = enchall_buff[s]&0x01;
					enchall.auxbit_in = (enchall_buff[s]&0x02)>>1;
					enchall.hole_in = (enchall_buff[s]&0x1c)>>2; //0001|1100
					enchall.calc_tag = (enchall_buff[s]&0x60)>>5; // 0110|0000
					//next byte
					enchall.enc_counter = enchall_buff[t]&0x1f; // 0001|1111
					//next two bytes
					uint8_t b1 = t==4?0:t+1;
					uint8_t b2 = b1==4?0:b1+1;
					enchall.enc_high = enchall_buff[b1]&0xff;
					enchall.enc_low = enchall_buff[b2]&0xff;
					if(xSemaphoreTakeFromISR(encdataMutexHandle,0)==pdPASS)
					{
						xQueueSendFromISR(enchallQueueHandle,&enchall,0);
						xSemaphoreGiveFromISR(encdataMutexHandle,0);
					}
					volatile int32_t data1,data2;
					if(HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter0,0) == HAL_OK &&
							HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter1,0) == HAL_OK)
					{
						data1 = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter0,(uint32_t *)&hdfsdm1_channel0);
						data2 = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter1,(uint32_t *)&hdfsdm1_channel3);
						HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_12);
					}
					b2= data1 + data2;
				}
			}
		}
		//continue DMA
		HAL_UART_DMAResume(&huart4);
	}
}

/***********
 * DFSDM DMA call back no need to use cpu..
 * ireserved... now use cpu to read the data..j
 * put the data into the queue.
 */
void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
	if(hdfsdm_filter->Instance == hdfsdm1_filter0.Instance)
	{

	}
	else if(hdfsdm_filter->Instance == hdfsdm1_filter1.Instance)
	{

	}
	else
		_Error_Handler("isrSensor.c, hdfsdm DMA problem", 120);
}
