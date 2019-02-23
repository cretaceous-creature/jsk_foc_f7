/*
******************************************************************************
* File Name          : estimator.h
* Description        : super  class for attitude estiamte algorithm
******************************************************************************
*/
#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#ifndef __ATTITUDE_ESTIMATOR_H
#define __ATTITUDE_ESTIMATOR_H

#include <stdint.h>
#include <math.h>
/* #include "arm_math.h" */

#define DELTA_T 0.01f

class EstimatorAlgorithm
{
public:
  EstimatorAlgorithm():
    acc_b_(), acc_v_(), gyro_b_(), gyro_v_(), mag_b_(), mag_v_(),q_(),
    desire_attitude_roll_(0), desire_attitude_pitch_(0),
    abs_rel_(ABSOLUTE_COORD)
  {
    r_.identity();;
  };

  ~EstimatorAlgorithm(){}

  /* coodrinate change  */
  void coordinateUpdate(float desire_attitude_roll, float desire_attitude_pitch)
  {
    desire_attitude_roll_ = desire_attitude_roll; 
    desire_attitude_pitch_ = desire_attitude_pitch; 

    r_.from_euler(desire_attitude_roll_, desire_attitude_pitch_, 0);

    /*
    float32_t cos_roll = arm_cos_f32(desire_attitude_roll_);
    float32_t sin_roll = arm_sin_f32(desire_attitude_roll_);
    float32_t cos_pitch = arm_cos_f32(desire_attitude_pitch_);
    float32_t sin_pitch = arm_sin_f32(desire_attitude_pitch_);

    desire_attitude_r_[0] = cos_pitch;
    desire_attitude_r_[1] = sin_pitch * sin_roll;
    desire_attitude_r_[2] = sin_pitch * cos_roll;
    desire_attitude_r_[3] = 0;
    desire_attitude_r_[4] = cos_roll;
    desire_attitude_r_[5] = -sin_roll;
    desire_attitude_r_[6] = -sin_pitch;
    desire_attitude_r_[7] = cos_pitch * sin_roll;
    desire_attitude_r_[8] = cos_pitch * cos_roll;
    */
  }


  void update(const Vector3f& gyro, const Vector3f& acc, const Vector3f& mag)
  {
    /* the sensor data in body frame */
    acc_b_ = acc;
    gyro_b_ = gyro;
    mag_b_ = mag;

    /* the sensor data in virtual frame */
    acc_v_ = r_* acc_b_;
    gyro_v_ = r_*  gyro_b_;
    mag_v_ = r_ * mag_b_;

    /*
    arm_mat_mult_f32(&desire_attitude_R_, &acc_b_vec_, &acc_v_vec_);
    arm_mat_mult_f32(&desire_attitude_R_, &gyro_b_vec_, &gyro_v_vec_);
    arm_mat_mult_f32(&desire_attitude_R_, &mag_b_vec_, &mag_v_vec_);
    */

    estimation();
  }

  virtual void estimation(){}; //please implementation!

  static const uint8_t ABSOLUTE_COORD = 0;
  static const uint8_t RELATIVE_COORD = 1;
  static const uint8_t X = 0;
  static const uint8_t Y = 1;
  static const uint8_t Z = 2;

  Vector3f getAngles(){return rpy_;}
  Vector3f getVels(){return gyro_v_;} // should be the virtual frame

  Vector3f getAccB(){return acc_b_;}
  Vector3f getGyroB(){return gyro_b_;}
  Vector3f getMagB(){return mag_b_;}

  Vector3f getAccV(){return acc_v_;}
  Vector3f getGyroV(){return gyro_v_;}
  Vector3f getMagV(){return mag_v_;} 

protected:
#if 0
  arm_matrix_instance_f32 acc_b_vec_, gyro_b_vec_, mag_b_vec_; //sensor data in body frame
  arm_matrix_instance_f32 acc_v_vec_, gyro_v_vec_, mag_v_vec_; //sensor data in virtual frame
  float acc_b_[3], gyro_b_[3],  mag_b_[3];
  float acc_v_[3], gyro_v_[3],  mag_v_[3]; //sensors data in virtual frame
  arm_matrix_instance_f32 angle_vec_;
  float angles_[3];
  float rpy_[3];
#endif
  Vector3f acc_b_, acc_v_;  
  Vector3f gyro_b_, gyro_v_;
  Vector3f mag_b_, mag_v_;

  Matrix3f r_;
  Vector3f rpy_;
  Quaternion q_; //TODO => change to AP_Math

  float desire_attitude_roll_, desire_attitude_pitch_;
  uint8_t abs_rel_;
  uint8_t update_desire_attitude_;

};

#endif
