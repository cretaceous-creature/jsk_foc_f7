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
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"

//uart4 DMA data buffer
//0xf8, 1xxx|xxxx, 011x|xxxx, byte, byte
#define TXHEADER 0xF8
#define UART4BYTE 5
volatile uint8_t enchall_buff[UART4BYTE];
static ENCHD enchall = {.recon_counter=5000,.z_count=0,.w=0,.MAX_W=80};
volatile static uint16_t last5bitsdata;
volatile static int32_t lasttick;
volatile static int32_t cnt;
volatile static int32_t cnt_e;
volatile static int16_t last_recon = 0;
volatile static int8_t fivetimecount = 51;
#define MAX_COUNT 2000
#define ALLONECOUNT 1984
//rotor speed estimation
#define MAX_V_FRAME 10
static int32_t v_buff[MAX_V_FRAME][3];
uint8_t v_index = 0;

//only when triggered the position event then the encoder count is valid

//usart1 DMA data buffer
// 0xf8 1xxx|xxxx 01xx|xxxx byte byte
#define HEAD2 0x80  //1xxx xxxx   Kp = 128~255 - 128
#define HEAD3 0x60  //01xx xxxx   Ki  64~128 - 64
#define UART1BYTE 7
volatile uint8_t order_buff[UART1BYTE];
//current data from dfsdm..
static CURDATA motorcurrent = {.Kp=0,.Ki=0,.target_cur=0,.centeroffset=0};
static uint8_t flag = 0;
//queue handle
extern osMessageQId enchallQueueHandle;
extern osMessageQId shuntQueueHandle;

/***********
 * UART4 error handler
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//error...
	Error_Handler();
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
		for(int i=0; i<UART4BYTE; i++)
		{
			if(enchall_buff[i] == TXHEADER)
			{
				uint8_t s = i==UART4BYTE-1?0:i+1; //second byte  1xxx|xxxx
				uint8_t t = s==UART4BYTE-1?0:s+1; //third byte   011x|xxxx
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
					uint8_t b1 = t==UART4BYTE-1?0:t+1;
					uint8_t b2 = b1==UART4BYTE-1?0:b1+1;
					enchall.enc_high = enchall_buff[b1]&0xff;
					enchall.enc_low = enchall_buff[b2]&0xff;
					//process the data... change to from 0-2000 encoder count..
					if(enchall.calc_tag == 2) //all 0
					{
						enchall.recon_counter = enchall.enc_counter;  //only 5bit has number, other bits are 0
						if(flag==2)
							enchall.z_count++;
						flag = 1;
					}
					else if(enchall.calc_tag == 3) //all 1    except the last 5 bits... other bits are 1
					{
						enchall.recon_counter = ALLONECOUNT + enchall.enc_counter;
						if(flag==1)
							enchall.z_count--;
						flag = 2;
					}
					else
					{
						flag = 0;
						if(enchall.enc_counter-last5bitsdata>16) //overflowed..
						{
							enchall.recon_counter = (enchall.recon_counter - 32)&0xFFE0|enchall.enc_counter;
						}
						else if(enchall.enc_counter-last5bitsdata<-16)
						{
							enchall.recon_counter = (enchall.recon_counter + 32)&0xFFE0|enchall.enc_counter;
						}
						else //not overflow
							enchall.recon_counter = enchall.recon_counter&0xFFE0|enchall.enc_counter;
					}
					//get the last data..
					last5bitsdata = enchall.enc_counter;


					//about 400us for every speed estimation, bug solved,
					//timer 2 and timer 4 not stable..
					if(fivetimecount--<=0&&cnt==lasttick)
					{
						cnt = (int32_t)htim3.Instance->CNT;
						cnt_e = cnt-lasttick;
						cnt_e = cnt_e<0?cnt_e+50000:cnt_e;
						if(cnt_e>390&&cnt_e<400)
						{
							//enchall.timetick++; //for debug
							volatile int16_t ct = enchall.recon_counter - last_recon;
							ct = ct>1000?enchall.recon_counter-last_recon-2000:ct;
							ct = ct<-1000?enchall.recon_counter-last_recon+2000:ct;
							// every element in v_buff has 3 members,
							//0 is count changed, 1 is time(us), 2 is the calculated speed(c/s)
							v_buff[v_index][0] = ct;v_buff[v_index][1] = cnt_e;
							v_buff[v_index][2] = 1e+6 * (int32_t)ct/cnt_e;
							volatile int32_t v_all = 0;
							for(uint8_t i=0;i<MAX_V_FRAME;i++)
								v_all += v_buff[i][2];
							//average speed
							v_all /= MAX_V_FRAME;
							//10 * (2*PI*v_all/2000)rad/s 10 is the factor
							enchall.w = (int16_t)(PI*v_all/100);
							v_index = v_index+1>=MAX_V_FRAME?0:v_index+1;
						}
						lasttick = cnt;
						last_recon = enchall.recon_counter;
						enchall.timetick = cnt_e;
						fivetimecount = 51;
					}

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

					//send the queue to tasks...
					//since we need to always refresh the data, need to use overwrite, only return pass
					xQueueOverwriteFromISR(enchallQueueHandle,&enchall, &xHigherPriorityTaskWoken);
				}
			}
		}
		//continue DMA
		HAL_UART_DMAResume(&huart4);
			//call a context switch if needed..
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}


}

