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
extern osMutexId encdataMutexHandle;

void StartenchallTask(void const * argument)
{
  for(;;)
  {
	  ENCHD encdata;
	  uint8_t datatosend[8];
	  if(xQueueReceiveFromISR(enchallQueueHandle,&encdata,0)==pdPASS)
	  {
		  xSemaphoreTake(encdataMutexHandle,0);
		  datatosend[0] = encdata.mseq_out + 0x30;//1bit
		  datatosend[1] = encdata.auxbit_in + 0x30;//1bit
		  datatosend[2] = encdata.hole_in + 0x30; //3bits
		  datatosend[3] = encdata.calc_tag + 0x30; //2bits
		  datatosend[4] = encdata.enc_counter/10 + 0x30; //msb unit
		  datatosend[5] = encdata.enc_counter%10 + 0x30; //lsb unit
		  datatosend[6] = '\r';
		  datatosend[7] = '\n';
//		  volatile int32_t data1,data2;
//		  if(HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter0,0) == HAL_OK)
//			  data1 = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter0,&hdfsdm1_channel0);
//		  if(HAL_DFSDM_FilterPollForRegConversion(&hdfsdm1_filter1,0) == HAL_OK)
//			  data2 = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter1,&hdfsdm1_channel3);
		  HAL_UART_Transmit(&huart1,datatosend,8,1);
		  xSemaphoreGive(encdataMutexHandle);
	  }
	  //every 5 mini
	  osDelay(100);
  }
}
