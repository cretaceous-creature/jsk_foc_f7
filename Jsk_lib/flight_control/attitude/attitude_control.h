/*
******************************************************************************
* File Name          : attitude_control.h
* Description        : attitude control interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __ATTITUDE_CONTROL_H
#define __ATTITUDE_CONTROL_H

#include "stm32f7xx_hal.h"
#include "config.h"
#include <ros.h>
#include <math/AP_Math.h>

/* state estimate  */
#include "state_estimate/state_estimate.h"
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>
#include <aerial_robot_msgs/RcData2.h>
//#include <aerial_robot_msgs/Pwms.h>

#define MAX_PWM  54000
#define IDLE_DUTY 0.5f
#define MIN_DUTY  0.55f   //1100/2000
#define MAX_DUTY 0.95f // 1900/2000

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

enum AXIS {
  ROLL = 0,
  PITCH = 1,
  YAW = 2,
  THROTTLE = 3,
};

class AttitudeController
{
public:
AttitudeController(){}

  ~AttitudeController(){}

void init(TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim2, StateEstimate* estimator, ros::NodeHandle* nh);
  void update();

 void setStartControlFlag(bool start_control_flag){start_control_flag_ = start_control_flag; }
 void setUavType(uint8_t uav_type){uav_type_ = uav_type; }
 void setMotorNumber(uint8_t motor_number){motor_number_ = motor_number ;}
 void setPwmTestMode(bool pwm_test_flag){pwm_test_flag_ = pwm_test_flag; }

private:

  TIM_HandleTypeDef* pwm_htim1_;
  TIM_HandleTypeDef* pwm_htim2_;

  ros::NodeHandle* nh_;
  ros::Subscriber2<aerial_robot_msgs::RcData2, AttitudeController>* flight_cmd_sub_;
  ros::Subscriber2<std_msgs::Float32, AttitudeController>* pwm_test_sub_;

#if PWM_PUB //for pwm pub
  aerial_robot_msgs/Pwms pwms_msg_;
  ros::Publisher* pwms_pub_;
#endif

//for debug
std_msgs::UInt8 test_msg_;
ros::Publisher* test_pub_;

  StateEstimate* estimator_;

  uint8_t uav_type_;
  uint8_t motor_number_;

//pwm test
  float pwm_test_value_;
  //PID Control
  float p_gain_[3];
  float i_gain_[3];
  float d_gain_[3];
  float p_term_[3];
  float i_term_[3];
  float d_term_[3];
  float pid_value_[3];
  float pwm_value_[8];
  float error_angle_i_[3];

  //Control Input
  float target_angle_[3];
  float target_throttle_;

  //Control flag
  bool start_control_flag_;
  bool pwm_test_flag_;

  void flightConfigCallback(const std_msgs::UInt8& config_msg);
  void flightCmdCallback(const aerial_robot_msgs::RcData2& cmd_msg);
  void pwmTestCallback(const std_msgs::Float32& pwm_msg);

  void pwmsControl(void);

  void attitudeControl(void);

  void reset(void);

  void mixTable(void);

  float pidMix(float x, float y,float z);

  float limit(float input, float limit);
};
#endif
