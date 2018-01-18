/**
 *
 * Jsk foc project
 *
 * debug folder,
 *
 * check the data and send throught uart to
 * the PC to see.
 *
 */

#include "gpio.h"
#include "usart.h"
#include "dfsdm.h"
#include "dma.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"
extern osMessageQId enchallQueueHandle;
extern osMessageQId conresQueueHandle;

void StartenchallTask(void const * argument)
{
  for(;;)
  {
	  ENCHD encdata;
	  CONRES conresdata;
	  uint8_t datatosend[80];
	  //We dont wanna read out and destory the data in the queue therefore use xQueuePeek
	  if(xQueuePeek(enchallQueueHandle,&encdata,0)==pdPASS)
	  {
		  int i = 0;
		  datatosend[i] = 'H';datatosend[++i] = ':';
		  datatosend[++i] = encdata.hole_in + 0x30; //3bits
		  datatosend[++i] = '\t';
//		  datatosend[++i] = encdata.calc_tag + 0x30; //2bits
//		  datatosend[++i] = '\t';
		  //datatosend[++i] = encdata.enc_counter/10 + 0x30; //msb unit
		  //datatosend[++i] = encdata.enc_counter%10 + 0x30; //lsb unit
		  //datatosend[++i] = '\t';
		  datatosend[++i] = 'E';datatosend[++i] = ':';
		  datatosend[++i] = encdata.recon_counter/1000 + 0x30; //msb unit
		  datatosend[++i] = encdata.recon_counter%1000/100 + 0x30;
		  datatosend[++i] = encdata.recon_counter%100/10 + 0x30;
		  datatosend[++i] = encdata.recon_counter%10 + 0x30;
		  datatosend[++i] = '\t';
		  datatosend[++i] = 'P';datatosend[++i] = ':';
		  datatosend[++i] = encdata.Kp/10 + 0x30;
		  datatosend[++i] = encdata.Kp%10 + 0x30;
		  datatosend[++i] = '\t';
		  datatosend[++i] = 'I';datatosend[++i] = ':';
		  datatosend[++i] = encdata.Ki/10 + 0x30;
		  datatosend[++i] = encdata.Ki%10 + 0x30;
		  datatosend[++i] = '\t';
		  datatosend[++i] = 'T';datatosend[++i] = 'Q';datatosend[++i] = ':';
		  if(encdata.target_cur<0) //minus
		  {
			  datatosend[++i] = '-';
			  encdata.target_cur = ~(encdata.target_cur - 1);
		  }
		  else
			  datatosend[++i] = '+';
		  datatosend[++i] = encdata.target_cur/10000 + 0x30;
		  datatosend[++i] = encdata.target_cur%10000/1000 + 0x30;
		  datatosend[++i] = '.';
		  datatosend[++i] = encdata.target_cur%1000/100 + 0x30;
		  datatosend[++i] = encdata.target_cur%100/10 + 0x30;
		  datatosend[++i] = 'A';
		  if(xQueuePeek(conresQueueHandle,&conresdata,0)==pdPASS)
		  {
			  //feedback q
			  datatosend[++i] = '\t';
			  datatosend[++i] = 'F';datatosend[++i] = 'Q';datatosend[++i] = ':';
			  if(conresdata.feedback_cq<0) //minus
			  {
				  datatosend[++i] = '-';
				  conresdata.feedback_cq = ~(conresdata.feedback_cq - 1);
			  }
			  else
				  datatosend[++i] = '+';
			  datatosend[++i] = conresdata.feedback_cq/10000 + 0x30;
			  datatosend[++i] = conresdata.feedback_cq%10000/1000 + 0x30;
			  datatosend[++i] = '.';
			  datatosend[++i] = conresdata.feedback_cq%1000/100 + 0x30;
			  datatosend[++i] = conresdata.feedback_cq%100/10 + 0x30;
			  datatosend[++i] = 'A';
			  datatosend[++i] = '\t';
			  //feedback d
			  datatosend[++i] = 'F';datatosend[++i] = 'D';datatosend[++i] = ':';
			  if(conresdata.feedback_cd<0) //minus
			  {
				  datatosend[++i] = '-';
				  conresdata.feedback_cd = ~(conresdata.feedback_cd - 1);
			  }
			  else
				  datatosend[++i] = '+';
			  datatosend[++i] = conresdata.feedback_cd/10000 + 0x30;
			  datatosend[++i] = conresdata.feedback_cd%10000/1000 + 0x30;
			  datatosend[++i] = '.';
			  datatosend[++i] = conresdata.feedback_cd%1000/100 + 0x30;
			  datatosend[++i] = conresdata.feedback_cd%100/10 + 0x30;
			  datatosend[++i] = 'A';
			  datatosend[++i] = '\t';
			  //duty
			  datatosend[++i] = 'd';datatosend[++i] = 'u';
			  datatosend[++i] = 't';datatosend[++i] = 'y';datatosend[++i] = ':';

			  datatosend[++i] = conresdata.duty_a/1000 + 0x30;
			  datatosend[++i] = conresdata.duty_a%1000/100 + 0x30;
			  datatosend[++i] = conresdata.duty_a%100/10 + 0x30;
			  datatosend[++i] = conresdata.duty_a%10 + 0x30;
			  datatosend[++i] = ',';
			  datatosend[++i] = conresdata.duty_b/1000 + 0x30;
			  datatosend[++i] = conresdata.duty_b%1000/100 + 0x30;
			  datatosend[++i] = conresdata.duty_b%100/10 + 0x30;
			  datatosend[++i] = conresdata.duty_b%10 + 0x30;
			  datatosend[++i] = ',';
			  datatosend[++i] = conresdata.duty_c/1000 + 0x30;
			  datatosend[++i] = conresdata.duty_c%1000/100 + 0x30;
			  datatosend[++i] = conresdata.duty_c%100/10 + 0x30;
			  datatosend[++i] = conresdata.duty_c%10 + 0x30;
		  }


		  datatosend[++i] = '\t';
		  datatosend[++i] = '\r';
		  datatosend[++i] = '\n';
		  __HAL_UNLOCK(&huart1);
		  HAL_UART_Transmit(&huart1,datatosend,i,50);
		  __HAL_LOCK(&huart1);
	  }
	  //every 5 mini
	  osDelay(100);
  }
}
