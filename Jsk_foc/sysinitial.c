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
extern volatile uint8_t order_buff[7];
extern DMA_HandleTypeDef hdma_uart4_rx;
extern void UART4_DMA2_Cplt_Callback(DMA_HandleTypeDef *_hdma);
//int32_t cur_u;
//int32_t cur_v;

void SystemInitialization(void)
{
	/*
	 * start tim2 for BUZZER
	 */
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);
	/*
	 * tim1 pwm initialization
	 * About the dead time...
	 * according to the datasheet the recovery time is about 114ns..
	 * thus if we consider the driver delay and blabla...
	 * we choose the dead time to be 300ns~...
	 * lookinto the tim.c file the dead time is calculated by
	 * 1/216mhz * DeadTime,  thus we choose DeadTime to be 66~
	 */
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);

	/*
	 * register the call back of uart4 transmit..
	 */

	HAL_UART_Receive_DMA(&huart4,enchall_buff,5);
	HAL_UART_Receive_DMA(&huart1,order_buff,7);
//HAL_DMA_RegisterCallback(&hdma_uart4_rx,HAL_DMA_XFER_CPLT_CB_ID,UART4_DMA2_Cplt_Callback);
	/*
	 * DFSDM initial
	 */
	//polling mode
	HAL_DFSDM_FilterRegularStart(&hdfsdm1_filter0);
	HAL_DFSDM_FilterRegularStart(&hdfsdm1_filter1);
}
