/*
******************************************************************************
* File Name          : attitude_control.h
* Description        : attitude control interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __POSITION_CONTROL_H
#define __POSITION_CONTROL_H

#include "stm32f7xx_hal.h"
#include "config.h"
#include <ros.h>

/* state estimate  */
#include "state_estimate/state_estimate.h"

#define MAX_PWM  54000
#define IDLE_DUTY 0.5f
#define MIN_DUTY  0.55f   //1100/2000
#define MAX_DUTY 0.95f // 1900/2000

#define UAV_DATA_ADDRESS  0x08020000
#define UAV_DATA_SECTOR FLASH_SECTOR_4 //CALIB_DATA_SECTOR + 1

#define QUADX 0x40
#define QUADP 0x41
#define HEXP  0x60

#define FORCE_TO_PWM  0.0005f // 1/2000 // 1.0f
#define FORCE_TO_PWM_OFFSET 0.0f

#define P_TERM_LEVEL_LIMIT 500
#define I_TERM_LEVEL_LIMIT 25
#define I_TERM_YAW_LIMIT 90

#define LEVEL_P_GAIN 403.065f
#define LEVEL_I_GAIN 419.85f
#define LEVEL_D_GAIN 106.1913f

#define YAW_P_GAIN 0.0f
#define YAW_I_GAIN 300.0f //multiwii: 339.3897f
#define YAW_D_GAIN 300.0f //multiwii: 218.818f


class PositionController
{
public:
  PositionController(){}
	void init(StateEstimate* estimator, AttitudeController* att_controller, ros::NodeHandle* nh)
  {
nh_ = nh;
estimator_ = estimator;
 att_controller_ = att_controller;
	  start_control_flag_ = false;
  }
  ~PositionController(){}

  void update();

private:
  ros::NodeHandle* nh_;
  StateEstimate* estimator_;
  AttitudeController* att_controller_;

  //PID Control
  float p_gain_[3];
  float i_gain_[3];
  float d_gain_[3];
  float p_term_[3];
  float i_term_[3];
  float d_term_[3];
  float pid_value_[3];

  //Control Output
  float target_angle_[3];
  float throttle_force_;

  //Control flag
  bool start_control_flag_;
};
#endif

