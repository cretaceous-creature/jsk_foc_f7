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
static ENCHD enchall = {.recon_counter=5000};
static uint16_t last5bitsdata;
#define MAX_COUNT 2000
#define ALLONECOUNT 1984
//only when triggered the position event then the encoder count is valid

//usart1 DMA data buffer
// 0xf8 1xxx|xxxx 01xx|xxxx byte byte
#define HEAD2 0x80  //1xxx xxxx   Kp = 128~255 - 128
#define HEAD3 0x60  //01xx xxxx   Ki  64~128 - 64
uint8_t order_buff[5];

//current data from dfsdm..
static CURDATA motorcurrent = {.Kp=0,.Ki=0,.target_cur=0};

//queue handle
extern osMessageQId enchallQueueHandle;
extern osMessageQId shuntQueueHandle;

/***********
 * UART4 error handler
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//error...
	_Error_Handler("isrSensors.c, uart error",53);
}

/***********
 * UART4 receive complete callback..
 * obtain hall sensor, encoder, etc data from intelligent board.
 * data updating rate <10us  ~100khz
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*
	 * firstly when the ISR is called it knows a the previous task A when the ISR is not triggered
	 * if some other task B that has higher priority than A are being woken by the passing queue or semaphore,
	 * the xHigherPriorityTaskWoken will be set to pdTrue and we can directly perform a context switch and thus
	 * leaves the ISR and go to task B, if not so, we need to go back to task A and wait for a tick to switch to B.
	 */

	if(huart->Instance==huart4.Instance) //not necessary to check..
	{
		static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		for(int i=0; i<5; i++)
		{
			if(enchall_buff[i] == TXHEADER)
			{
				uint8_t s = i==4?0:i+1; //second byte  1xxx|xxxx
				uint8_t t = s==4?0:s+1; //third byte   011x|xxxx
				if(enchall_buff[s]&0x80&&enchall_buff[t]&0x60)
				{
					//then we can obtain the correct bytes...
					enchall.mseq_out = (enchall_buff[s]&0x40)>>6; //0100|0000
					enchall.auxbit_in = (enchall_buff[s]&0x20)>>5; //0010|0000
					enchall.hole_in = (enchall_buff[s]&0x1c)>>2; //0001|1100
					enchall.calc_tag = enchall_buff[s]&0x03; // 0000|0011
					//next byte
					enchall.enc_counter = enchall_buff[t]&0x1f; // 0001|1111
					//next two bytes
					uint8_t b1 = t==4?0:t+1;
					uint8_t b2 = b1==4?0:b1+1;
					enchall.enc_high = enchall_buff[b1]&0xff;
					enchall.enc_low = enchall_buff[b2]&0xff;
					//process the data... change to from 0-2000 encoder count..
					if(enchall.calc_tag == 2) //all 0
					{
						enchall.recon_counter = enchall.enc_counter;  //only 5bits OK
					}
					else if(enchall.calc_tag == 3) //all 1
					{
						enchall.recon_counter = ALLONECOUNT + enchall.enc_counter;
					}
					else
					{
						if(enchall.enc_counter-last5bitsdata>16) //overflowed..
							enchall.recon_counter = (enchall.recon_counter - 32)&0xFFE0|enchall.enc_counter;
						else if(enchall.enc_counter-last5bitsdata<-16)
							enchall.recon_counter = (enchall.recon_counter + 32)&0xFFE0|enchall.enc_counter;
						else //not overflow
							enchall.recon_counter = enchall.recon_counter&0xFFE0|enchall.enc_counter;
					}
					//get the last data..
					last5bitsdata = enchall.enc_counter;

					//send the queue to tasks...
					//since we need to always refresh the data, need to use overwrite, only return pass
					xQueueOverwriteFromISR(enchallQueueHandle,&enchall, &xHigherPriorityTaskWoken);
					//send the DFSDM current sensing data.
					if(HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter0,0) == HAL_OK &&
							HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter1,0) == HAL_OK)
					{
						//also we need to deal with the offset by shorting the shunt sensor..
						motorcurrent.cur_b = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter0,(uint32_t *)&hdfsdm1_channel0);
						motorcurrent.cur_a = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter1,(uint32_t *)&hdfsdm1_channel3);
						// f 256, I 2,  a: 8600 b:18400;  1ma = 100
						// f 128, I 2,  a:1200 b:2300;   1ma = 100/(2^3) = 12.5
						motorcurrent.cur_a -= 8600;
						motorcurrent.cur_b -= 18400;
						motorcurrent.cur_c = - motorcurrent.cur_a - motorcurrent.cur_b;
						xQueueSendFromISR(shuntQueueHandle,&motorcurrent,&xHigherPriorityTaskWoken);
					}
				}
			}
		}
		//continue DMA
		HAL_UART_DMAResume(&huart4);
			//call a context switch if needed..
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

	//USART 1 DMA interrupt
	else if(huart->Instance==huart1.Instance)
	{
		for(int i=0; i<5; i++)
		{
			if(order_buff[i] == TXHEADER)
			{
				uint8_t s = i==4?0:i+1; //second byte  1xxx|xxxx
				uint8_t t = s==4?0:s+1; //third byte   011x|xxxx
				if(order_buff[s]&0x80&&order_buff[t]&0x60)
				{
					//then we can obtain the correct bytes...
					motorcurrent.Kp = order_buff[s] & 0x7f;
					motorcurrent.Ki = order_buff[t] & 0x1f;
					//next two bytes
					uint8_t b1 = t==4?0:t+1;
					uint8_t b2 = b1==4?0:b1+1;
					motorcurrent.target_cur =  (((int16_t)order_buff[b2]&0x7f) << 8) | order_buff[b1];
					if(order_buff[b2]&0x80) //minus
						motorcurrent.target_cur = -motorcurrent.target_cur;

					enchall.Kp = motorcurrent.Kp;
					enchall.Ki = motorcurrent.Ki;
					enchall.target_cur = motorcurrent.target_cur;
				}
			}
		}
		//continue DMA
		HAL_UART_DMAResume(&huart1);
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
