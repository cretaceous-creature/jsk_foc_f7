/*
******************************************************************************
* File Name          : altitude_estimate.h
* Description        : attitude estimate interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __ALTITUDE_ESTIMATE_H
#define __ALTITUDE_ESTIMATE_H

#include "stm32f7xx_hal.h"
#include "config.h"
/*  #include "arm_math.h" */
#include <ros.h>
#include <aerial_robot_msgs/Barometer.h>

/* sensors */
////////////////////////////////////////
//TODO: should include the super class//
////////////////////////////////////////
#include "sensors/imu/imu_mpu9250.h"
#include "sensors/baro/baro_ms5611.h"


class AltitudeEstimate
{
public:
  AltitudeEstimate(){}
  ~AltitudeEstimate(){}

  void  init(IMU* imu, Baro* baro, ros::NodeHandle* nh)
  {
    nh_ = nh;
    baro_pub_  = new ros::Publisher("baro", &baro_msg_);
    nh_->advertise(*baro_pub_);

    imu_ = imu;
    baro_= baro;
  }

  void update()
  {
    if(baro_->getUpdate())
      {
        /* altitude estimation */
        //nav-ekf

        /* send message */
       publish();

        baro_->setUpdate(false);
      }
  }

private:
  ros::NodeHandle* nh_;
  ros::Publisher* baro_pub_;
  aerial_robot_msgs::Barometer baro_msg_;

  IMU* imu_;
  Baro* baro_;
  //nav-ekf


  void publish()
  {
    baro_msg_.stamp = nh_->now();
    baro_msg_.pressure = baro_->getPressure();
    baro_msg_.temperature = baro_->getTemperature();
    baro_msg_.altitude = baro_->getAltitude();
    baro_pub_->publish(&baro_msg_);
  }

};

#endif
