/*
******************************************************************************
* File Name          : attitude_control.h
* Description        : attitude control interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#include "flight_control/attitude/attitude_control.h"

void AttitudeController::init(TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim2, StateEstimate* estimator, ros::NodeHandle* nh)
{

 pwm_htim1_ = htim1;
pwm_htim2_ = htim2;
 nh_ = nh;
estimator_ = estimator;

  HAL_TIM_PWM_Start(pwm_htim1_,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(pwm_htim1_,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(pwm_htim1_,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(pwm_htim1_,TIM_CHANNEL_4);

  HAL_TIM_PWM_Start(pwm_htim2_,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(pwm_htim2_,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(pwm_htim2_,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(pwm_htim2_,TIM_CHANNEL_4);


  flight_cmd_sub_= new ros::Subscriber2<aerial_robot_msgs::RcData2, AttitudeController> ("/aerial_robot_control", &AttitudeController::flightCmdCallback, this );

  pwm_test_sub_ = new ros::Subscriber2<std_msgs::Float32, AttitudeController> ("/pwm_test", &AttitudeController::pwmTestCallback, this );

#if PWM_PUB //for pwm pub
  pwms_pub_  = new ros::Publisher("motor_pwms", &pwms_msg);
  nh_->advertise(*pwms_pub_);
#endif

  nh_->subscribe<aerial_robot_msgs::RcData2, AttitudeController>(*flight_cmd_sub_);
  nh_->subscribe<std_msgs::Float32, AttitudeController>(*pwm_test_sub_);

//test
  test_pub_  = new ros::Publisher("control_feedback_test", &test_msg_);
  nh_->advertise(*test_pub_);

  start_control_flag_ = false;
  pwm_test_flag_ = false;

  reset();
  //gain init
  for(int i = 0; i < 3; i++)
    {
      p_gain_[i]= LEVEL_P_GAIN;
      i_gain_[i]= LEVEL_I_GAIN;
      d_gain_[i]= LEVEL_D_GAIN;

      if(i == 2)
        {//yaw
          p_gain_[i]= YAW_P_GAIN;
          i_gain_[i]= YAW_I_GAIN;
          d_gain_[i]= YAW_D_GAIN;
        }
    }
}


void AttitudeController::pwmsControl(void)
{
  for(int i = 0; i < motor_number_; i++)
    {
      if(start_control_flag_)
        {
          if(pwm_value_[i] < MIN_DUTY) pwm_value_[i]  = MIN_DUTY;
          else if(pwm_value_[i]  > MAX_DUTY) pwm_value_[i]  = MAX_DUTY;
        }

#if PWM_PUB //for pwm pub
      pwms_msg_[i] = pwm_value_[i];
#endif

      if(pwm_test_flag_)
        {
          //pwm_value_[0] = (pwm_test_value_ < MIN_DUTY)?MIN_DUTY:((pwm_test_value_ > MAX_DUTY)? MAX_DUTY:pwm_test_value_;
          pwm_value_[0] = pwm_test_value_;
        }
    }
#if PWM_PUB //for pwm pub
  pwms_pub_->publish(&pwms_msgs_);
#endif

  pwm_htim1_->Instance->CCR1 = (uint32_t)(pwm_value_[0] * MAX_PWM);
  pwm_htim1_->Instance->CCR2 = (uint32_t)(pwm_value_[1] * MAX_PWM);
  pwm_htim1_->Instance->CCR3 = (uint32_t)(pwm_value_[2] * MAX_PWM);
  pwm_htim1_->Instance->CCR4 = (uint32_t)(pwm_value_[3] * MAX_PWM);

  if(motor_number_ > 4)
    {
      pwm_htim2_->Instance->CCR1 =   (uint32_t)(pwm_value_[4] * MAX_PWM);
      pwm_htim2_->Instance->CCR2 =  (uint32_t)(pwm_value_[5] * MAX_PWM);
    }
  if(motor_number_ > 6)
    {
      pwm_htim2_->Instance->CCR3 = (uint32_t)(pwm_value_[6] * MAX_PWM);
      pwm_htim2_->Instance->CCR4 =  (uint32_t)(pwm_value_[7] * MAX_PWM);
    }
}

void AttitudeController::update(void)
{
  if(start_control_flag_)
    {
      Vector3f angles = estimator_->getAttEstimator()->getAngles(); //should be virutal coord
      Vector3f vel = estimator_->getAttEstimator()->getVels(); //should be virutal coord

      //PID
      for(int axis = 0; axis < 3; axis++)
        {
          float error_angle = 0;
          //P term 
          if( axis < 2)
            {//roll and pitch
              error_angle = target_angle_[axis] - angles[axis];
              p_term_[axis] = error_angle * p_gain_[axis];
              p_term_[axis] = limit(p_term_[axis], P_TERM_LEVEL_LIMIT);

              //I term
              error_angle_i_[axis] += (error_angle * DELTA_T);
              i_term_[axis] = (error_angle_i_[axis] * i_gain_[axis]);
              i_term_[axis] = limit(i_term_[axis], I_TERM_LEVEL_LIMIT);

            }
          else //yaw
            {
              p_term_[axis]  = target_angle_[axis];
              if(target_angle_[axis] == 0)
                {//this part have problem!!!!
                  error_angle_i_[axis] = limit(error_angle_i_[axis] - vel[axis] * DELTA_T,  I_TERM_YAW_LIMIT / i_gain_[axis]);
                  //I term
                  i_term_[axis] = (error_angle_i_[axis] * i_gain_[axis]);
                  i_term_[axis] = limit(i_term_[axis], I_TERM_YAW_LIMIT);
                }
              else
                {
                  //error_angle_i[axis] = 0;
                  i_term_[axis]  = 0;
                }
            }

          //D term
          d_term_[axis] = -vel[axis] * d_gain_[axis];
          //total
        }

      //test
      //test.f_data[0] = i_term[2];
      //test.f_data[1] = d_term[2];

      mixTable();

    }
  //pwm
  pwmsControl();
}

//this is pwm
float AttitudeController::pidMix(float x, float y,float z)
{
  float temp = (target_throttle_ + pid_value_[0] * x + pid_value_[1] * y + pid_value_[2] * z) * FORCE_TO_PWM - FORCE_TO_PWM_OFFSET;

  if(temp > MIN_DUTY)
    {
      return temp;
    }
  return MIN_DUTY;
}

void AttitudeController::mixTable(void)
{

  switch (uav_type_)
    { 
    case QUADP:
      {
        pwm_value_[0] = pidMix( 0,+1,+1); //REAR
        pwm_value_[1] = pidMix(-1, 0,-1); //RIGHT
        pwm_value_[2] = pidMix( 0,-1,+1); //FRONT
        pwm_value_[3] = pidMix(+1, 0,-1); //LEFT
        break;
      }
    case QUADX:
      {
        pwm_value_[0] = pidMix(-1,+1,+1); //REAR_R => T4C1
        pwm_value_[1] = pidMix(-1,-1,-1); //FRONT_R => T4C2
        pwm_value_[2] = pidMix(+1,-1,+1); //FRONT_L => T4C3
        pwm_value_[3] = pidMix(+1,+1,-1); //REAR_L => T4C4
        break;
      }
    case HEXP:
      {
        pwm_value_[0] = pidMix(-0.5 ,0.866, +1);   //REAR_R => T4C1
        pwm_value_[1] = pidMix(-1, 0, -1);           //MIDDLE_R => T4C2
        pwm_value_[2] = pidMix(-0.5, -0.866, +1); //FRONT_R => T4C3
        pwm_value_[3] = pidMix(+0.5 ,-0.866, -1); //FRONT_L => T4C4
        pwm_value_[4] = pidMix(+1, 0, +1);           //MIDDLE_L => T8C1
        pwm_value_[5] = pidMix(+0.5, 0.866,-1);    //REAR_L => T8C2
        break;
      }
    }
}

void AttitudeController::reset(void)
 {
   for(int i = 0; i < 3; i++)
     {
       pid_value_[i] = 0;
       error_angle_i_[i] = 0;
       target_angle_[i] = 0;
     }
   target_throttle_ = 0;

   for(int i = 0; i < motor_number_; i++)
     pwm_value_[i] = IDLE_DUTY;

#if PWM_PUB //for pwm pub
   for(int i = 0; i < MAX_MOTOR_NUMBER; i++)
     pwms_msg_[i] = 0;
#endif
 }


float AttitudeController::limit(float input, float limit)
{
  if (input > limit) return limit;
  else if(input < -limit) return -limit;
  else return input;
}


void AttitudeController::flightCmdCallback(const aerial_robot_msgs::RcData2& cmd_msg)
{
  target_angle_[ROLL] = cmd_msg.roll;
  target_angle_[PITCH] = cmd_msg.pitch;
  target_angle_[YAW] = cmd_msg.yaw;
  target_throttle_ = cmd_msg.throttle;

 //test
  test_msg_.data = 1;
  test_pub_->publish(&test_msg_);
}

void AttitudeController::pwmTestCallback(const std_msgs::Float32& pwm_msg)
{
  pwm_test_value_ = pwm_msg.data; //2000ms
}
