#ifndef _ROS_aerial_robot_base_YawThrottleGain_h
#define _ROS_aerial_robot_base_YawThrottleGain_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_base
{

  class YawThrottleGain : public ros::Msg
  {
    public:
      int32_t motor_num;
      uint8_t pos_p_gain_throttle_length;
      float st_pos_p_gain_throttle;
      float * pos_p_gain_throttle;
      uint8_t pos_i_gain_throttle_length;
      float st_pos_i_gain_throttle;
      float * pos_i_gain_throttle;
      uint8_t pos_d_gain_throttle_length;
      float st_pos_d_gain_throttle;
      float * pos_d_gain_throttle;
      uint8_t pos_p_gain_yaw_length;
      float st_pos_p_gain_yaw;
      float * pos_p_gain_yaw;
      uint8_t pos_i_gain_yaw_length;
      float st_pos_i_gain_yaw;
      float * pos_i_gain_yaw;
      uint8_t pos_d_gain_yaw_length;
      float st_pos_d_gain_yaw;
      float * pos_d_gain_yaw;
      uint8_t roll_vec_length;
      float st_roll_vec;
      float * roll_vec;
      uint8_t pitch_vec_length;
      float st_pitch_vec;
      float * pitch_vec;
      uint8_t yaw_vec_length;
      float st_yaw_vec;
      float * yaw_vec;

    YawThrottleGain():
      motor_num(0),
      pos_p_gain_throttle_length(0), pos_p_gain_throttle(NULL),
      pos_i_gain_throttle_length(0), pos_i_gain_throttle(NULL),
      pos_d_gain_throttle_length(0), pos_d_gain_throttle(NULL),
      pos_p_gain_yaw_length(0), pos_p_gain_yaw(NULL),
      pos_i_gain_yaw_length(0), pos_i_gain_yaw(NULL),
      pos_d_gain_yaw_length(0), pos_d_gain_yaw(NULL),
      roll_vec_length(0), roll_vec(NULL),
      pitch_vec_length(0), pitch_vec(NULL),
      yaw_vec_length(0), yaw_vec(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_motor_num;
      u_motor_num.real = this->motor_num;
      *(outbuffer + offset + 0) = (u_motor_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_num.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_num);
      *(outbuffer + offset++) = pos_p_gain_throttle_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_p_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_p_gain_throttlei;
      u_pos_p_gain_throttlei.real = this->pos_p_gain_throttle[i];
      *(outbuffer + offset + 0) = (u_pos_p_gain_throttlei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_p_gain_throttlei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_p_gain_throttlei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_p_gain_throttlei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_p_gain_throttle[i]);
      }
      *(outbuffer + offset++) = pos_i_gain_throttle_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_i_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_i_gain_throttlei;
      u_pos_i_gain_throttlei.real = this->pos_i_gain_throttle[i];
      *(outbuffer + offset + 0) = (u_pos_i_gain_throttlei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_i_gain_throttlei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_i_gain_throttlei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_i_gain_throttlei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_i_gain_throttle[i]);
      }
      *(outbuffer + offset++) = pos_d_gain_throttle_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_d_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_d_gain_throttlei;
      u_pos_d_gain_throttlei.real = this->pos_d_gain_throttle[i];
      *(outbuffer + offset + 0) = (u_pos_d_gain_throttlei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_d_gain_throttlei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_d_gain_throttlei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_d_gain_throttlei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_d_gain_throttle[i]);
      }
      *(outbuffer + offset++) = pos_p_gain_yaw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_p_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_p_gain_yawi;
      u_pos_p_gain_yawi.real = this->pos_p_gain_yaw[i];
      *(outbuffer + offset + 0) = (u_pos_p_gain_yawi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_p_gain_yawi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_p_gain_yawi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_p_gain_yawi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_p_gain_yaw[i]);
      }
      *(outbuffer + offset++) = pos_i_gain_yaw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_i_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_i_gain_yawi;
      u_pos_i_gain_yawi.real = this->pos_i_gain_yaw[i];
      *(outbuffer + offset + 0) = (u_pos_i_gain_yawi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_i_gain_yawi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_i_gain_yawi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_i_gain_yawi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_i_gain_yaw[i]);
      }
      *(outbuffer + offset++) = pos_d_gain_yaw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pos_d_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pos_d_gain_yawi;
      u_pos_d_gain_yawi.real = this->pos_d_gain_yaw[i];
      *(outbuffer + offset + 0) = (u_pos_d_gain_yawi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_d_gain_yawi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_d_gain_yawi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_d_gain_yawi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_d_gain_yaw[i]);
      }
      *(outbuffer + offset++) = roll_vec_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < roll_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_roll_veci;
      u_roll_veci.real = this->roll_vec[i];
      *(outbuffer + offset + 0) = (u_roll_veci.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_veci.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_veci.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_veci.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_vec[i]);
      }
      *(outbuffer + offset++) = pitch_vec_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pitch_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_pitch_veci;
      u_pitch_veci.real = this->pitch_vec[i];
      *(outbuffer + offset + 0) = (u_pitch_veci.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_veci.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_veci.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_veci.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_vec[i]);
      }
      *(outbuffer + offset++) = yaw_vec_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < yaw_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_yaw_veci;
      u_yaw_veci.real = this->yaw_vec[i];
      *(outbuffer + offset + 0) = (u_yaw_veci.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_veci.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_veci.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_veci.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_vec[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_motor_num;
      u_motor_num.base = 0;
      u_motor_num.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_num.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_num.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_num.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_num = u_motor_num.real;
      offset += sizeof(this->motor_num);
      uint8_t pos_p_gain_throttle_lengthT = *(inbuffer + offset++);
      if(pos_p_gain_throttle_lengthT > pos_p_gain_throttle_length)
        this->pos_p_gain_throttle = (float*)realloc(this->pos_p_gain_throttle, pos_p_gain_throttle_lengthT * sizeof(float));
      offset += 3;
      pos_p_gain_throttle_length = pos_p_gain_throttle_lengthT;
      for( uint8_t i = 0; i < pos_p_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_p_gain_throttle;
      u_st_pos_p_gain_throttle.base = 0;
      u_st_pos_p_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_p_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_p_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_p_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_p_gain_throttle = u_st_pos_p_gain_throttle.real;
      offset += sizeof(this->st_pos_p_gain_throttle);
        memcpy( &(this->pos_p_gain_throttle[i]), &(this->st_pos_p_gain_throttle), sizeof(float));
      }
      uint8_t pos_i_gain_throttle_lengthT = *(inbuffer + offset++);
      if(pos_i_gain_throttle_lengthT > pos_i_gain_throttle_length)
        this->pos_i_gain_throttle = (float*)realloc(this->pos_i_gain_throttle, pos_i_gain_throttle_lengthT * sizeof(float));
      offset += 3;
      pos_i_gain_throttle_length = pos_i_gain_throttle_lengthT;
      for( uint8_t i = 0; i < pos_i_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_i_gain_throttle;
      u_st_pos_i_gain_throttle.base = 0;
      u_st_pos_i_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_i_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_i_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_i_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_i_gain_throttle = u_st_pos_i_gain_throttle.real;
      offset += sizeof(this->st_pos_i_gain_throttle);
        memcpy( &(this->pos_i_gain_throttle[i]), &(this->st_pos_i_gain_throttle), sizeof(float));
      }
      uint8_t pos_d_gain_throttle_lengthT = *(inbuffer + offset++);
      if(pos_d_gain_throttle_lengthT > pos_d_gain_throttle_length)
        this->pos_d_gain_throttle = (float*)realloc(this->pos_d_gain_throttle, pos_d_gain_throttle_lengthT * sizeof(float));
      offset += 3;
      pos_d_gain_throttle_length = pos_d_gain_throttle_lengthT;
      for( uint8_t i = 0; i < pos_d_gain_throttle_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_d_gain_throttle;
      u_st_pos_d_gain_throttle.base = 0;
      u_st_pos_d_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_d_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_d_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_d_gain_throttle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_d_gain_throttle = u_st_pos_d_gain_throttle.real;
      offset += sizeof(this->st_pos_d_gain_throttle);
        memcpy( &(this->pos_d_gain_throttle[i]), &(this->st_pos_d_gain_throttle), sizeof(float));
      }
      uint8_t pos_p_gain_yaw_lengthT = *(inbuffer + offset++);
      if(pos_p_gain_yaw_lengthT > pos_p_gain_yaw_length)
        this->pos_p_gain_yaw = (float*)realloc(this->pos_p_gain_yaw, pos_p_gain_yaw_lengthT * sizeof(float));
      offset += 3;
      pos_p_gain_yaw_length = pos_p_gain_yaw_lengthT;
      for( uint8_t i = 0; i < pos_p_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_p_gain_yaw;
      u_st_pos_p_gain_yaw.base = 0;
      u_st_pos_p_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_p_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_p_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_p_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_p_gain_yaw = u_st_pos_p_gain_yaw.real;
      offset += sizeof(this->st_pos_p_gain_yaw);
        memcpy( &(this->pos_p_gain_yaw[i]), &(this->st_pos_p_gain_yaw), sizeof(float));
      }
      uint8_t pos_i_gain_yaw_lengthT = *(inbuffer + offset++);
      if(pos_i_gain_yaw_lengthT > pos_i_gain_yaw_length)
        this->pos_i_gain_yaw = (float*)realloc(this->pos_i_gain_yaw, pos_i_gain_yaw_lengthT * sizeof(float));
      offset += 3;
      pos_i_gain_yaw_length = pos_i_gain_yaw_lengthT;
      for( uint8_t i = 0; i < pos_i_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_i_gain_yaw;
      u_st_pos_i_gain_yaw.base = 0;
      u_st_pos_i_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_i_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_i_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_i_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_i_gain_yaw = u_st_pos_i_gain_yaw.real;
      offset += sizeof(this->st_pos_i_gain_yaw);
        memcpy( &(this->pos_i_gain_yaw[i]), &(this->st_pos_i_gain_yaw), sizeof(float));
      }
      uint8_t pos_d_gain_yaw_lengthT = *(inbuffer + offset++);
      if(pos_d_gain_yaw_lengthT > pos_d_gain_yaw_length)
        this->pos_d_gain_yaw = (float*)realloc(this->pos_d_gain_yaw, pos_d_gain_yaw_lengthT * sizeof(float));
      offset += 3;
      pos_d_gain_yaw_length = pos_d_gain_yaw_lengthT;
      for( uint8_t i = 0; i < pos_d_gain_yaw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pos_d_gain_yaw;
      u_st_pos_d_gain_yaw.base = 0;
      u_st_pos_d_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pos_d_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pos_d_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pos_d_gain_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pos_d_gain_yaw = u_st_pos_d_gain_yaw.real;
      offset += sizeof(this->st_pos_d_gain_yaw);
        memcpy( &(this->pos_d_gain_yaw[i]), &(this->st_pos_d_gain_yaw), sizeof(float));
      }
      uint8_t roll_vec_lengthT = *(inbuffer + offset++);
      if(roll_vec_lengthT > roll_vec_length)
        this->roll_vec = (float*)realloc(this->roll_vec, roll_vec_lengthT * sizeof(float));
      offset += 3;
      roll_vec_length = roll_vec_lengthT;
      for( uint8_t i = 0; i < roll_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_roll_vec;
      u_st_roll_vec.base = 0;
      u_st_roll_vec.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_roll_vec.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_roll_vec.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_roll_vec.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_roll_vec = u_st_roll_vec.real;
      offset += sizeof(this->st_roll_vec);
        memcpy( &(this->roll_vec[i]), &(this->st_roll_vec), sizeof(float));
      }
      uint8_t pitch_vec_lengthT = *(inbuffer + offset++);
      if(pitch_vec_lengthT > pitch_vec_length)
        this->pitch_vec = (float*)realloc(this->pitch_vec, pitch_vec_lengthT * sizeof(float));
      offset += 3;
      pitch_vec_length = pitch_vec_lengthT;
      for( uint8_t i = 0; i < pitch_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_pitch_vec;
      u_st_pitch_vec.base = 0;
      u_st_pitch_vec.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_pitch_vec.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_pitch_vec.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_pitch_vec.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_pitch_vec = u_st_pitch_vec.real;
      offset += sizeof(this->st_pitch_vec);
        memcpy( &(this->pitch_vec[i]), &(this->st_pitch_vec), sizeof(float));
      }
      uint8_t yaw_vec_lengthT = *(inbuffer + offset++);
      if(yaw_vec_lengthT > yaw_vec_length)
        this->yaw_vec = (float*)realloc(this->yaw_vec, yaw_vec_lengthT * sizeof(float));
      offset += 3;
      yaw_vec_length = yaw_vec_lengthT;
      for( uint8_t i = 0; i < yaw_vec_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_yaw_vec;
      u_st_yaw_vec.base = 0;
      u_st_yaw_vec.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_yaw_vec.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_yaw_vec.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_yaw_vec.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_yaw_vec = u_st_yaw_vec.real;
      offset += sizeof(this->st_yaw_vec);
        memcpy( &(this->yaw_vec[i]), &(this->st_yaw_vec), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/YawThrottleGain"; };
    const char * getMD5(){ return "4fabfd209e6e59ee85466cff98bab2c8"; };

  };

}
#endif