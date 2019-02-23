/*
******************************************************************************
* File Name          : pos_estimate.h
* Description        : pos estimate interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __POS_ESTIMATE_H
#define __POS_ESTIMATE_H

#include "stm32f7xx_hal.h"
#include "config.h"
/* #include "arm_math.h" */
#include <ros.h>
#include <aerial_robot_msgs/Gps.h>

/* sensors */
////////////////////////////////////////
//TODO: should include the super class//
////////////////////////////////////////
#include "sensors/imu/imu_mpu9250.h"
#include "sensors/gps/gps_ublox.h"

class PosEstimate
{
public:
  PosEstimate(){}
  ~PosEstimate(){}

  void  init(IMU* imu, GPS* gps, ros::NodeHandle* nh)
  {
    nh_ = nh;
   gps_pub_  = new ros::Publisher("gps", &gps_msg_);
    nh_->advertise(*gps_pub_);

    imu_ = imu;
    gps_ = gps;
  }

  void update()
  {
    if(gps_->getUpdate())
      {
        /* altitude estimation */
        //nav-ekf2

        /* send message */
        publish();
        gps_->setUpdate(false);
      }
  }

private:
  ros::NodeHandle* nh_;
  ros::Publisher* gps_pub_;
  aerial_robot_msgs::Gps gps_msg_;

  IMU* imu_;
  GPS* gps_;
  //nav-ekf2

  void publish()
  {
    gps_msg_.stamp = nh_->now();

    gps_msg_.location[0] = gps_->getGosState().location.lat; // lat
    gps_msg_.location[1] = gps_->getGosState().location.lng; // lng

    gps_msg_.velocity[0] = gps_->getGosState().velocity.x;
    gps_msg_.velocity[1] = gps_->getGosState().velocity.y;

    gps_msg_.sat_num = gps_->getGosState().num_sats;

    gps_pub_->publish(&gps_msg_);
  }
};

#endif
