#ifndef __ROS_TEST_H_
#define __ROS_TEST_H_

#include "ros.h"
#include "std_msgs/Empty.h"
#include "std_msgs/UInt8.h"

//for gpio debug
#define TEST_H      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)
#define TEST_L      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)

#define LED0_L       HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET)
#define LED0_H      HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET)
#define LED1_L       HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET)
#define LED1_H      HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET)

class RosClass{
public:
  RosClass(ros::NodeHandle* nh):
    nh_(nh),  pub_("test1_from_ros_class", &test_msg_), 
    sub_("toggle_led_from_ros_class", &RosClass::testCallback, this )
  {
    nh_->advertise(pub_); 
    nh_->subscribe<std_msgs::Empty, RosClass>(sub_);
  }
  ~RosClass(){}

  void update()
  {
    test_msg_.data = 136;
    pub_.publish(&test_msg_);
  }

private:

  void testCallback(const std_msgs::Empty& toggle_msg)
  {
    static int i = 0;
    if(i == 0) 
      {
        LED1_L;
        i = 1;
      }
    else
      {
        LED1_H;
        i = 0;
      }
  }

  ros::NodeHandle*  nh_;
  std_msgs::UInt8 test_msg_;
  ros::Publisher pub_;
  ros::Subscriber2<std_msgs::Empty, RosClass> sub_;

};
#endif

