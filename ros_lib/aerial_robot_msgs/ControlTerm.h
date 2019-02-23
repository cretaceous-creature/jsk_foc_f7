#ifndef _ROS_aerial_robot_msgs_ControlTerm_h
#define _ROS_aerial_robot_msgs_ControlTerm_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class ControlTerm : public ros::Msg
  {
    public:
      int32_t roll_p_term[4];
      int32_t roll_i_term[4];
      int32_t roll_d_term[4];
      int32_t pitch_p_term[4];
      int32_t pitch_i_term[4];
      int32_t pitch_d_term[4];
      int32_t yaw_d_term[4];

    ControlTerm():
      roll_p_term(),
      roll_i_term(),
      roll_d_term(),
      pitch_p_term(),
      pitch_i_term(),
      pitch_d_term(),
      yaw_d_term()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_p_termi;
      u_roll_p_termi.real = this->roll_p_term[i];
      *(outbuffer + offset + 0) = (u_roll_p_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_p_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_p_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_p_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_p_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_i_termi;
      u_roll_i_termi.real = this->roll_i_term[i];
      *(outbuffer + offset + 0) = (u_roll_i_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_i_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_i_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_i_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_i_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_d_termi;
      u_roll_d_termi.real = this->roll_d_term[i];
      *(outbuffer + offset + 0) = (u_roll_d_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_d_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_d_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_d_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_d_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_p_termi;
      u_pitch_p_termi.real = this->pitch_p_term[i];
      *(outbuffer + offset + 0) = (u_pitch_p_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_p_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_p_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_p_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_p_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_i_termi;
      u_pitch_i_termi.real = this->pitch_i_term[i];
      *(outbuffer + offset + 0) = (u_pitch_i_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_i_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_i_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_i_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_i_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_d_termi;
      u_pitch_d_termi.real = this->pitch_d_term[i];
      *(outbuffer + offset + 0) = (u_pitch_d_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_d_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_d_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_d_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_d_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_d_termi;
      u_yaw_d_termi.real = this->yaw_d_term[i];
      *(outbuffer + offset + 0) = (u_yaw_d_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_d_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_d_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_d_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_d_term[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_p_termi;
      u_roll_p_termi.base = 0;
      u_roll_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_p_term[i] = u_roll_p_termi.real;
      offset += sizeof(this->roll_p_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_i_termi;
      u_roll_i_termi.base = 0;
      u_roll_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_i_term[i] = u_roll_i_termi.real;
      offset += sizeof(this->roll_i_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_roll_d_termi;
      u_roll_d_termi.base = 0;
      u_roll_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_d_term[i] = u_roll_d_termi.real;
      offset += sizeof(this->roll_d_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_p_termi;
      u_pitch_p_termi.base = 0;
      u_pitch_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_p_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_p_term[i] = u_pitch_p_termi.real;
      offset += sizeof(this->pitch_p_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_i_termi;
      u_pitch_i_termi.base = 0;
      u_pitch_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_i_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_i_term[i] = u_pitch_i_termi.real;
      offset += sizeof(this->pitch_i_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pitch_d_termi;
      u_pitch_d_termi.base = 0;
      u_pitch_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_d_term[i] = u_pitch_d_termi.real;
      offset += sizeof(this->pitch_d_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_d_termi;
      u_yaw_d_termi.base = 0;
      u_yaw_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_d_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_d_term[i] = u_yaw_d_termi.real;
      offset += sizeof(this->yaw_d_term[i]);
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/ControlTerm"; };
    const char * getMD5(){ return "d42317ebb11aab8fca9674992a86c258"; };

  };

}
#endif