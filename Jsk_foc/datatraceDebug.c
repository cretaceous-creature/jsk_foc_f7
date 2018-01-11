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

void StartenchallTask(void const * argument)
{
  for(;;)
  {
	  ENCHD encdata;
	  uint8_t datatosend[50];
	  //We dont wanna read out and destory the data in the queue therefore use xQueuePeek
	  if(xQueuePeek(enchallQueueHandle,&encdata,0)==pdPASS)
	  {
		  int i = 0;
		  datatosend[i] = encdata.mseq_out + 0x30;//1bit
		  datatosend[++i] = encdata.auxbit_in + 0x30;//1bit
		  datatosend[++i] = '\t';
		  datatosend[++i] = encdata.hole_in + 0x30; //3bits
		  datatosend[++i] = '\t';
		  datatosend[++i] = encdata.calc_tag + 0x30; //2bits
		  datatosend[++i] = '\t';
		  datatosend[++i] = encdata.enc_counter/10 + 0x30; //msb unit
		  datatosend[++i] = encdata.enc_counter%10 + 0x30; //lsb unit
		  datatosend[++i] = '\t';
		  datatosend[++i] = '\r';
		  datatosend[++i] = '\n';
		  HAL_UART_Transmit(&huart1,datatosend,i,10);
	  }
	  //every 5 mini
	  osDelay(100);
  }
}
