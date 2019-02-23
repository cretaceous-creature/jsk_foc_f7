#ifndef _ROS_aerial_robot_msgs_RollPitchYawGain_h
#define _ROS_aerial_robot_msgs_RollPitchYawGain_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class RollPitchYawGain : public ros::Msg
  {
    public:
      int16_t angle_cos;
      int16_t angle_sin;
      int32_t roll_p_gain[4];
      int32_t roll_i_gain[4];
      int32_t roll_d_gain[4];
      int32_t pitch_p_gain[4];
      int32_t pitch_i_gain[4];
      int32_t pitch_d_gain[4];
      int32_t yaw_d_gain[4];

    RollPitchYawGain():
      angle_cos(0),
      angle_sin(0),
      roll_p_gain(),
      roll_i_gain(),
      roll_d_gain(),
      pitch_p_gain(),
      pitch_i_gain(),
      pitch_d_gain(),
      yaw_d_gain()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_angle_cos;
      u_angle_cos.real = this->angle_cos;
      *(outbuffer + offset + 0) = (u_angle_cos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_cos.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle_cos);
      union {
        int16_t real;
        uint16_t base;
      } u_angle_sin;
      u_angle_sin.real = this->angle_sin;
      *(outbuffer + offset + 0) = (u_angle_sin.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_sin.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle_sin);
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_p_gaini;
      u_roll_p_gaini.real = this->roll_p_gain[i];
      *(outbuffer + offset + 0) = (u_roll_p_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_p_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_p_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_p_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_p_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_i_gaini;
      u_roll_i_gaini.real = this->roll_i_gain[i];
      *(outbuffer + offset + 0) = (u_roll_i_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_i_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_i_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_i_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_i_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_d_gaini;
      u_roll_d_gaini.real = this->roll_d_gain[i];
      *(outbuffer + offset + 0) = (u_roll_d_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_d_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_d_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_d_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_d_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_p_gaini;
      u_pitch_p_gaini.real = this->pitch_p_gain[i];
      *(outbuffer + offset + 0) = (u_pitch_p_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_p_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_p_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_p_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_p_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_i_gaini;
      u_pitch_i_gaini.real = this->pitch_i_gain[i];
      *(outbuffer + offset + 0) = (u_pitch_i_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_i_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_i_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_i_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_i_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_d_gaini;
      u_pitch_d_gaini.real = this->pitch_d_gain[i];
      *(outbuffer + offset + 0) = (u_pitch_d_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_d_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_d_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_d_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_d_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_d_gaini;
      u_yaw_d_gaini.real = this->yaw_d_gain[i];
      *(outbuffer + offset + 0) = (u_yaw_d_gaini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_d_gaini.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_d_gaini.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_d_gaini.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_d_gain[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_angle_cos;
      u_angle_cos.base = 0;
      u_angle_cos.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_cos.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle_cos = u_angle_cos.real;
      offset += sizeof(this->angle_cos);
      union {
        int16_t real;
        uint16_t base;
      } u_angle_sin;
      u_angle_sin.base = 0;
      u_angle_sin.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_sin.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle_sin = u_angle_sin.real;
      offset += sizeof(this->angle_sin);
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_p_gaini;
      u_roll_p_gaini.base = 0;
      u_roll_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_p_gain[i] = u_roll_p_gaini.real;
      offset += sizeof(this->roll_p_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_i_gaini;
      u_roll_i_gaini.base = 0;
      u_roll_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_i_gain[i] = u_roll_i_gaini.real;
      offset += sizeof(this->roll_i_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_d_gaini;
      u_roll_d_gaini.base = 0;
      u_roll_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_d_gain[i] = u_roll_d_gaini.real;
      offset += sizeof(this->roll_d_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_p_gaini;
      u_pitch_p_gaini.base = 0;
      u_pitch_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_p_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_p_gain[i] = u_pitch_p_gaini.real;
      offset += sizeof(this->pitch_p_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_i_gaini;
      u_pitch_i_gaini.base = 0;
      u_pitch_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_i_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_i_gain[i] = u_pitch_i_gaini.real;
      offset += sizeof(this->pitch_i_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_d_gaini;
      u_pitch_d_gaini.base = 0;
      u_pitch_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_d_gain[i] = u_pitch_d_gaini.real;
      offset += sizeof(this->pitch_d_gain[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_d_gaini;
      u_yaw_d_gaini.base = 0;
      u_yaw_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_d_gaini.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_d_gain[i] = u_yaw_d_gaini.real;
      offset += sizeof(this->yaw_d_gain[i]);
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/RollPitchYawGain"; };
    const char * getMD5(){ return "5c0e99167edbaf9a73c8718ee4f2f525"; };

  };

}
#endif