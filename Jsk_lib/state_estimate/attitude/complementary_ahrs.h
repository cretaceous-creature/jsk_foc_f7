/*
******************************************************************************
* File Name          : complementary_ahrs.h
* Description        : ahrs estimation by complementary filter
******************************************************************************
*/
#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif


#ifndef __COMPLEMENTARY_AHRS_H
#define __COMPLEMENTARY_AHRS_H

#include "state_estimate/attitude/estimator.h"

#define GYR_CMPF_FACTOR 60
#define GYR_CMPFM_FACTOR 25
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))
#define PRESCLAER_ACC 3 // if value=1, it means same rate with gyro, for genral attitude estimation
//* the gyro integaral attitude estiamtion amplification rate
#define GYRO_AMP  1.1395f  //if value= 1, it means normal complementrary filter

#define G_MIN 72
#define G_MAX 133
/*
typedef struct fp_vector {
  float x;
  float y;
  float z;
} t_fp_vector_def;

typedef union {
  float A[3];
  t_fp_vector_def V;
} t_fp_vector;
*/

class ComplementaryAHRS: public EstimatorAlgorithm
{
public:
  ComplementaryAHRS():EstimatorAlgorithm(),
                      est_g_v_(),  est_m_v_(),
                       est_g_b_(), est_m_b_()
  {
    /*
    arm_mat_init_f32(&est_g_v_, 3, 1, (float32_t *)EstGv_.A);
    arm_mat_init_f32(&est_m_v_, 3, 1, (float32_t *)EstMv_.A);
    arm_mat_init_f32(&est_g_b_, 3, 1, (float32_t *)EstGb_.A);
    arm_mat_init_f32(&est_m_b_, 3, 1, (float32_t *)EstMb_.A);
    */
  }


private:
  Vector3f est_g_v_,  est_m_v_;
  Vector3f est_g_b_,  est_m_b_;

  // t_fp_vector EstGb_ ,EstMb_;
  // t_fp_vector EstGv_, EstMv_;

  /*
  void rotateV(struct fp_vector *v,float* delta) {
    t_fp_vector_def v_tmp = *v;
    v->z += -delta[X]  * v_tmp.y + delta[Y] * v_tmp.x;
    v->x += -delta[Y] * v_tmp.z + delta[Z]   * v_tmp.y;
    v->y +=  delta[X]  * v_tmp.z - delta[Z]   * v_tmp.x;
  }
  */

  /* core esitmation process, using body frame */
  virtual void estimation() 
  {
    int  valid_acc = 0;
    static int cnt = 0;

 #if 0 //old
 uint8_t axis;
      float acc_magnitude = 0;
      float* delta_gyro_angle[3];
      for(axis = 0; axis <3; axis ++)
      {
      delta_gyro_angle[axis] = gyro[axis]  * DELTA_T * GYRO_AMP;
      acc_magnitude += acc[axis] * acc[axis] ;
      }

      rotateV(&EstGb_.V,delta_gyro_angle);
      rotateV(&EstMb_.V,delta_gyro_angle);
 #endif

    float acc_magnitude = acc_b_ * acc_b_; //norm?
    Vector3f est_g_b_tmp = est_g_b_;
    Vector3f est_m_b_tmp = est_m_b_;
    est_g_b_ += (est_g_b_tmp % (gyro_b_  * (DELTA_T * GYRO_AMP) )); //rotation by gyro
    est_m_b_ += (est_m_b_tmp % (gyro_b_  * (DELTA_T * GYRO_AMP) )); //rotation by gyro



    if( G_MIN < acc_magnitude && acc_magnitude < G_MAX) valid_acc = 1;
    else valid_acc = 0;

     //*********************************************************************
     //** Apply complimentary filter (Gyro drift correction) 
     //** If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range 
     //**    => we neutralize the effect of accelerometers in the angle estimation. 
     //** To do that, we just skip filter, as EstV already rotated by Gyro 
     //*********************************************************************


#if 0 //old
    for (axis = 0; axis < 3; axis++) {
      if ( valid_acc == 1 && cnt == 0)
        {
          EstGb_.A[axis] = (EstGb_.A[axis] * GYR_CMPF_FACTOR + acc[axis]) * INV_GYR_CMPF_FACTOR;
        }
      EstMb_.A[axis] = (EstMb_.A[axis] * GYR_CMPFM_FACTOR  + mag[axis]) * INV_GYR_CMPFM_FACTOR;
    }

    arm_mat_mult_f32(&desire_attitude_R_, &est_g_b_, &est_g_v_);
    arm_mat_mult_f32(&desire_attitude_R_, &est_m_b_, &est_m_v_);

    // Attitude of the estimated vector
    float sqGX_sqGZ = EstGv_.V.x * EstGv_.V.x + EstGv_.V.z * EstGv_.V.z;
    float sqGY_sqGZ = EstGv_.V.y * EstGv_.V.y + EstGv_.V.z * EstGv_.V.z;
    float invG = invSqrt(sqGX_sqGZ + EstGv_.V.y * EstGv_.V.y);

    rpy_[X] = atan2f(EstGv_.V.y , EstGv_.V.z);
    rpy_[Y] = atan2f(-EstGv_.V.x , invSqrt(sqGY_sqGZ)*sqGY_sqGZ);
    rpy_[Z] = atan2f( EstMv_.V.z * EstGv_.V.y - EstMv_.V.y * EstGv_.V.z,
                      EstMv_.V.x * invG * sqGY_sqGZ  - (EstMv_.V.y * EstGv_.V.y + EstMv_.V.z * EstGv_.V.z) * invG * EstGv_.V.x ) ;//+ MAG_DECLINIATION;
#endif


    est_g_b_tmp = est_g_b_;
    est_m_b_tmp = est_m_b_;

    if ( valid_acc == 1 && cnt == 0)
      est_g_b_ = (est_g_b_tmp * GYR_CMPF_FACTOR + acc_b_) * INV_GYR_CMPF_FACTOR;
    est_m_b_ = (est_m_b_tmp * GYR_CMPFM_FACTOR  + mag_b_) * INV_GYR_CMPFM_FACTOR;

    est_g_v_ = r_ * est_g_b_;
    est_m_v_ = r_ * est_m_b_;

    // Attitude of the estimated vector
    float sq_g_x_sq_g_z = est_g_v_.x * est_g_v_.x + est_g_v_.z * est_g_v_.z;
    float sq_g_y_sq_g_z = est_g_v_.y * est_g_v_.y + est_g_v_.z * est_g_v_.z;
    float invG = inv_sqrt(sq_g_x_sq_g_z + est_g_v_.y * est_g_v_.y);

    rpy_.x = atan2f(est_g_v_.y , est_g_v_.z);
    rpy_.y = atan2f(-est_g_v_.x , inv_sqrt(sq_g_y_sq_g_z)* sq_g_y_sq_g_z);
    rpy_.z = atan2f( est_m_v_.z * est_g_v_.y - est_m_v_.y * est_g_v_.z,
                      est_m_v_.x * invG * sq_g_y_sq_g_z  - (est_m_v_.y * est_g_v_.y + est_m_v_.z * est_g_v_.z) * invG * est_g_v_.x ) ;//+ MAG_DECLINIATION;
     //********************************************************************************:
     //** refrence1: https://sites.google.com/site/myimuestimationexperience/sensors/magnetometer
     //** refrence2: http://uav.xenocross.net/hdg.html
     //********************************************************************************
    /* update */
    if(valid_acc) cnt++;
    if(cnt == PRESCLAER_ACC) cnt = 0;
  }

};


#endif
