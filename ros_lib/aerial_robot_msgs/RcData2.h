#ifndef _ROS_aerial_robot_msgs_RcData2_h
#define _ROS_aerial_robot_msgs_RcData2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class RcData2 : public ros::Msg
  {
    public:
      float roll;
      float pitch;
      int16_t yaw;
      int16_t throttle;

    RcData2():
      roll(0),
      pitch(0),
      yaw(0),
      throttle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_roll;
      u_roll.real = this->roll;
      *(outbuffer + offset + 0) = (u_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll);
      union {
        float real;
        uint32_t base;
      } u_pitch;
      u_pitch.real = this->pitch;
      *(outbuffer + offset + 0) = (u_pitch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch);
      union {
        int16_t real;
        uint16_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_throttle;
      u_throttle.real = this->throttle;
      *(outbuffer + offset + 0) = (u_throttle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_throttle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->throttle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_roll;
      u_roll.base = 0;
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll = u_roll.real;
      offset += sizeof(this->roll);
      union {
        float real;
        uint32_t base;
      } u_pitch;
      u_pitch.base = 0;
      u_pitch.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch = u_pitch.real;
      offset += sizeof(this->pitch);
      union {
        int16_t real;
        uint16_t base;
      } u_yaw;
      u_yaw.base = 0;
      u_yaw.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->yaw = u_yaw.real;
      offset += sizeof(this->yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_throttle;
      u_throttle.base = 0;
      u_throttle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_throttle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->throttle = u_throttle.real;
      offset += sizeof(this->throttle);
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/RcData2"; };
    const char * getMD5(){ return "18ff9bb588cb17e2ae8713f0d79ec99f"; };

  };

}
#endif