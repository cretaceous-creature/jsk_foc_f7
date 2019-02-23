/*
******************************************************************************
* File Name          : state_estimate.h
* Description        : state(attitude, altitude, pos) estimate interface
******************************************************************************
*/

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __STATE_ESTIMATE_H
#define __STATE_ESTIMATE_H

#include "stm32f7xx_hal.h"
#include "config.h"
/* #include "arm_math.h" */
#include <ros.h>

/* sensors */
////////////////////////////////////////
//TODO: should include the super class//
////////////////////////////////////////
#include "sensors/imu/imu_mpu9250.h"
#include "sensors/baro/baro_ms5611.h"
#include "sensors/gps/gps_ublox.h"

/* */
#include "state_estimate/attitude/attitude_estimate.h"
#include "state_estimate/altitude/altitude_estimate.h"
#include "state_estimate/pos/pos_estimate.h"

class StateEstimate
{
public:
  StateEstimate()
  {
  }
  ~StateEstimate(){}

void  init(IMU* imu, Baro* baro, GPS* gps, ros::NodeHandle* nh)
  {
    nh_ = nh;

    if(imu == NULL) 
      {
        attitude_estimate_flag_ = false;
      }
    else
      {
        attitude_estimate_flag_ = true;
        imu_ = imu;
        attitude_estimator_.init(imu_, nh_);
      }

    if(baro == NULL)
      {
        altitude_estimate_flag_ = false;
      }
    else
      {
        altitude_estimate_flag_ = true;
        baro_ = baro;
        altitude_estimator_.init(imu_, baro_, nh_);
      }

    if(gps == NULL)
      {
        pos_estimate_flag_ = false;
      }
    else
      {
        pos_estimate_flag_ = true;
        gps_ = gps;
        pos_estimator_.init(imu_, gps_, nh_);
      }
  }

  void update()
  {
    if(attitude_estimate_flag_) attitude_estimator_.update();
    if(altitude_estimate_flag_) altitude_estimator_.update();
    if(pos_estimate_flag_) pos_estimator_.update();
  }

  AttitudeEstimate* getAttEstimator(){ return &attitude_estimator_;}
  AltitudeEstimate* getAltEstimator(){ return &altitude_estimator_;}
  PosEstimate* getPosEstimator(){ return &pos_estimator_;}

private:
  ros::NodeHandle* nh_;

  IMU* imu_;
  Baro* baro_;
  GPS* gps_;

  AttitudeEstimate attitude_estimator_;
  AltitudeEstimate altitude_estimator_;
  PosEstimate pos_estimator_;

  bool attitude_estimate_flag_;
  bool altitude_estimate_flag_;
  bool pos_estimate_flag_;
};

#endif
