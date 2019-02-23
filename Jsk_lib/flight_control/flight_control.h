/*
******************************************************************************
* File Name          : flight_control.h
* Description        : flight control(attitude, position)  interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __FLIGHT_CONTROL_H
#define __FLIGHT_CONTROL_H

#include "stm32f7xx_hal.h"
#include "config.h"
/* #include "arm_math.h" */

/* state estimate  */
#include "state_estimate/state_estimate.h"

/* controller  */
#include "flight_control/attitude/attitude_control.h"
#include "flight_control/position/position_control.h"

/* ros */
#include <ros.h>
#include <std_msgs/UInt8.h>

#define UAV_DATA_ADDRESS  0x08020000
#define UAV_DATA_SECTOR FLASH_SECTOR_4 //CALIB_DATA_SECTOR + 1

class FlightControl
{
public:
  FlightControl()
  {
  }
  ~FlightControl(){}

  void  init(TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim2, StateEstimate* estimator, ros::NodeHandle* nh)
  {
    nh_ = nh;
    /* flight control base config */
    flight_config_sub_ = new ros::Subscriber2<std_msgs::UInt8, FlightControl> ("/flight_config_cmd", &FlightControl::flightConfigCallback, this );
    nh_->subscribe<std_msgs::UInt8, FlightControl>(*flight_config_sub_);
    /* config ack to ROS */
    config_ack_pub_  = new ros::Publisher("flight_config_ack", &config_ack_msg_);
    nh_->advertise(*config_ack_pub_);

    /* uav & motor type */
    uav_type_sub_ = new ros::Subscriber2<std_msgs::UInt8, FlightControl> ("/uav_type_config", &FlightControl::uavTypeConfigCallback, this );
    nh_->subscribe<std_msgs::UInt8, FlightControl>(*uav_type_sub_);

    estimator_ = estimator;

    pwm_htim1_ = htim1;
    pwm_htim2_ = htim2;

 att_controller_.init(htim1, htim2, estimator, nh);
   // att_controller_ = new AttitudeController(htim1, htim2, estimator, nh); => cannot use the pointer why?
   pos_controller_.init(estimator_, &att_controller_, nh_);
    

   readUavType();
    start_control_flag_ = false;
    pwm_test_flag_ = false;
  }

  void update()
  {
    //pos_controller_->update();
    att_controller_.update();
  }

  static const uint8_t MOTOR_START_MSG = 0x20;
  static const uint8_t MOTOR_STOP_MSG = 0x21;
  static const uint8_t PWM_TEST_MODE_MSG = 0x30;

private:
  ros::NodeHandle* nh_;
  ros::Subscriber2<std_msgs::UInt8, FlightControl>* flight_config_sub_;
  ros::Subscriber2<std_msgs::UInt8, FlightControl>* uav_type_sub_;
  ros::Publisher* config_ack_pub_;
  std_msgs::UInt8 config_ack_msg_;
  
  bool  start_control_flag_;
  bool pwm_test_flag_;

  uint8_t uav_type_;
  uint8_t motor_number_;

  StateEstimate* estimator_;
  TIM_HandleTypeDef* pwm_htim1_;
  TIM_HandleTypeDef*  pwm_htim2_;
   AttitudeController att_controller_;
  PositionController pos_controller_;

  void flightConfigCallback(const std_msgs::UInt8& config_msg)
  {
    switch(config_msg.data)
      {
      case MOTOR_START_MSG:
        start_control_flag_ = true;
        att_controller_.setStartControlFlag(start_control_flag_);
        //pos_controller_->setStartControlFlag(start_control_flag_);
      
        /* ack to ROS */
        config_ack_msg_.data = MOTOR_START_MSG;
        config_ack_pub_->publish(&config_ack_msg_);
        break;
      case MOTOR_STOP_MSG:
        start_control_flag_ = false;
        att_controller_.setStartControlFlag(start_control_flag_);
        //pos_controller_->setStartControlFlag(start_control_flag_);

        /* ack to ROS */
        config_ack_msg_.data = MOTOR_STOP_MSG;
        config_ack_pub_->publish(&config_ack_msg_);
        break;
      case PWM_TEST_MODE_MSG:
        pwm_test_flag_ = true;
        att_controller_.setPwmTestMode(pwm_test_flag_);	
        break;
      }
  }

  void uavTypeConfigCallback(const std_msgs::UInt8& config_msg)
  {
    uav_type_ = config_msg.data;
    writeUavType();
  }


  void readUavType(void)
  {
    HAL_StatusTypeDef status = HAL_ERROR;

    status = FLASH_WaitForLastOperation((uint32_t)50000); //50s

    if(status == HAL_OK)
      {
        uav_type_ = (*(__IO uint32_t*)(UAV_DATA_ADDRESS));
        motor_number_ = uav_type_ / 16;
        FLASH->CR &= (~FLASH_CR_PG);
      }

    att_controller_.setUavType(uav_type_);
    att_controller_.setMotorNumber(motor_number_);

    //pos_controller_->setUavType(uav_type_);
    //pos_controller_->setMotorNumber(motor_number_);
  }

  void writeUavType(void)
  {
    HAL_StatusTypeDef r;

    r = HAL_FLASH_Unlock();
    if( r != HAL_OK ) return;

    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SectorError = 0;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.Sector = UAV_DATA_SECTOR ;
    EraseInitStruct.NbSectors = 1;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    r = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
    if ( r != HAL_OK ) return;

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, UAV_DATA_ADDRESS, (*(__IO uint16_t*)(&uav_type_)));
    motor_number_ =  uav_type_ / 16;

    r = HAL_FLASH_Lock();

    att_controller_.setUavType(uav_type_);
    att_controller_.setMotorNumber(motor_number_);

    // pos_controller_->setUavType(uav_type_);
    // pos_controller_->setMotorNumber(motor_number_);
  }

};

#endif
