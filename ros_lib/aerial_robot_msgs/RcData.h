#ifndef _ROS_aerial_robot_msgs_RcData_h
#define _ROS_aerial_robot_msgs_RcData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class RcData : public ros::Msg
  {
    public:
      int16_t roll;
      int16_t pitch;
      int16_t yaw;
      int16_t throttle;

    RcData():
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
        int16_t real;
        uint16_t base;
      } u_roll;
      u_roll.real = this->roll;
      *(outbuffer + offset + 0) = (u_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->roll);
      union {
        int16_t real;
        uint16_t base;
      } u_pitch;
      u_pitch.real = this->pitch;
      *(outbuffer + offset + 0) = (u_pitch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch.base >> (8 * 1)) & 0xFF;
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
        int16_t real;
        uint16_t base;
      } u_roll;
      u_roll.base = 0;
      u_roll.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->roll = u_roll.real;
      offset += sizeof(this->roll);
      union {
        int16_t real;
        uint16_t base;
      } u_pitch;
      u_pitch.base = 0;
      u_pitch.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
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

    const char * getType(){ return "aerial_robot_msgs/RcData"; };
    const char * getMD5(){ return "575c8a2d3e94b794917a9e2b3c8a5413"; };

  };

}
#endif