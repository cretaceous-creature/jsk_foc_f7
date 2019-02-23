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
#ifdef __cplusplus
extern "C"{
#endif
#include "gpio.h"
#include "usart.h"
#include "dfsdm.h"
#include "dma.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"
#include "string.h"
#include "spi.h"
extern osMessageQId enchallQueueHandle;
extern osMessageQId conresQueueHandle;
#ifdef __cplusplus
}
#endif
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
void StartenchallTask(void const * argument);
#ifdef __cplusplus
}
#endif



void StartenchallTask(void const * argument)
{
	/*****************ros node init**************/
	ros::NodeHandle  nh_;
	nh_.initNode(&huart1);
	IMU imu_;
	imu_.init(&hspi1, &nh_);
	StateEstimate estimator_;
	estimator_.init(&imu_,NULL,NULL,&nh_);//  att mode

	for(;;)
	{
	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET);
	  nh_.spinOnce();
	  if(nh_.connected())
	  {
			  imu_.update();
			  estimator_.update();
	  }
	    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET);

		osDelay(5);

	}
}

