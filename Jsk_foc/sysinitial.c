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
 */

#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "dfsdm.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"


//databuff
extern uint8_t enchall_buff[5];

void SystemInitialization(void)
{
  //start tim2 for BUZZER
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  //register the call back of uart4 transmit..
  //HAL_DMA_RegisterCallback(&hdma_uart4_rx,HAL_DMA_XFER_CPLT_CB_ID, UART4_DMA2_Cplt_Callback);
  HAL_UART_Receive_DMA(&huart4,enchall_buff,5);
}
