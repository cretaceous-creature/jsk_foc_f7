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
#include "string.h"
extern osMessageQId enchallQueueHandle;
extern osMessageQId conresQueueHandle;

#define Header1 'T'
#define Header2 'E'
#define Tail 'N'

// debug view for visualization
//#define DVIEW


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
		  uint8_t i = 0;
#ifdef DVIEW
		  datatosend[i] = 'H';datatosend[++i] = ':';
		  datatosend[++i] = encdata.hole_in + 0x30; //3bits
		  datatosend[++i] = '\t';
		  //get the z phase count
		  if(encdata.z_count<0) //minus
		  {
			  datatosend[++i] = '-';
			  encdata.z_count = ~(encdata.z_count - 1);
		  }
		  else
			  datatosend[++i] = '+';

		  datatosend[++i] = 'Z';datatosend[++i] = ':';
		  datatosend[++i] = encdata.z_count%1000/100 + 0x30;
		  datatosend[++i] = encdata.z_count%100/10 + 0x30;
		  datatosend[++i] = encdata.z_count%10 + 0x30;
		  datatosend[++i] = '\t';
		  //speed
		  datatosend[++i] = 'w';datatosend[++i] = ':';
		  if(encdata.w<0) //minus
		  {
			  datatosend[++i] = '-';
			  encdata.w = ~(encdata.w - 1);
		  }
		  else
			  datatosend[++i] = '+';
		  datatosend[++i] = encdata.w%10000/1000 + 0x30;
		  datatosend[++i] = encdata.w%1000/100 + 0x30;
		  datatosend[++i] = encdata.w%100/10 + 0x30;
		  datatosend[++i] = encdata.w%10 + 0x30;
		  datatosend[++i] = '\t';

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
		  datatosend[++i] = encdata.target_cur%1000/100 + 0x30;
		  datatosend[++i] = '.';
		  datatosend[++i] = encdata.target_cur%100/10 + 0x30;
		  datatosend[++i] = encdata.target_cur%10 + 0x30;
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
			  datatosend[++i] = conresdata.feedback_cq%1000/100 + 0x30;
			  datatosend[++i] = '.';
			  datatosend[++i] = conresdata.feedback_cq%100/10 + 0x30;
			  datatosend[++i] = conresdata.feedback_cq%10 + 0x30;
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
			  datatosend[++i] = conresdata.feedback_cd%1000/100 + 0x30;
			  datatosend[++i] = '.';
			  datatosend[++i] = conresdata.feedback_cd%100/10 + 0x30;
			  datatosend[++i] = conresdata.feedback_cd%10 + 0x30;
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
#else
		  /***********
		   *
		   * here transmit the brief data to ros interface...
		   *
		   * 0xa2  size    data(size)   0x2a   // for now the size of the data should be 2+4+2+2+2 + 6 = 18
		   */
		  datatosend[i] = Header1; datatosend[++i] = Header2; i+=2;
		  memcpy(&datatosend[i],&encdata.z_count,sizeof(encdata.z_count));   //int16
		  i += sizeof(encdata.z_count);
		  memcpy(&datatosend[i],&encdata.recon_counter,sizeof(encdata.recon_counter)); //uint16
		  i += sizeof(encdata.recon_counter);
		  memcpy(&datatosend[i],&encdata.w,sizeof(encdata.w));                 //int16
		  i += sizeof(encdata.w);
		  if(xQueuePeek(conresQueueHandle,&conresdata,0)==pdPASS)
		  {
			  memcpy(&datatosend[i],&conresdata.feedback_cq,sizeof(conresdata.feedback_cq)); //int16
			  i += sizeof(conresdata.feedback_cq);
			  memcpy(&datatosend[i],&conresdata.feedback_cd,sizeof(conresdata.feedback_cd)); //int16
			  i += sizeof(conresdata.feedback_cd);
		  }
		  datatosend[i] = Tail;
		  datatosend[2] = i;
		  datatosend[++i] = '\r';datatosend[++i] = '\n';


#endif
		  __HAL_UNLOCK(&huart1);
		  HAL_UART_Transmit(&huart1,datatosend,i,1);
		  //HAL_UART_Transmit_IT(&huart1,datatosend,i);
//		  __HAL_LOCK(&huart1);
	  }
	  //every 100mini
#ifdef DVIEW
	  osDelay(100);
#else
	  osDelay(5);
#endif

  }
}
