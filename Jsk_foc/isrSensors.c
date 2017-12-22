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
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

//uart4 DMA data buffer
uint8_t enchall_buff[8];

void UART4_DMA2_Cplt_Callback(DMA_HandleTypeDef *hdma)
{


}
