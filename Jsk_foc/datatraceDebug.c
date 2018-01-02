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
	  uint8_t datatosend[8];
	  if(xQueueReceiveFromISR(enchallQueueHandle,&encdata,0)==pdPASS)
	  {
		  datatosend[0] = encdata.mseq_out + 0x30;//1bit
		  datatosend[1] = encdata.auxbit_in + 0x30;//1bit
		  datatosend[2] = encdata.hole_in + 0x30; //3bits
		  datatosend[3] = encdata.calc_tag + 0x30; //2bits
		  datatosend[4] = encdata.enc_counter/10 + 0x30; //msb unit
		  datatosend[5] = encdata.enc_counter%10 + 0x30; //lsb unit
		  datatosend[6] = '\r';
		  datatosend[7] = '\n';
		  HAL_UART_Transmit(&huart1,datatosend,8,1);
	  }
	  //every 5 mini
	  osDelay(100);
  }
}
