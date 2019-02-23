#ifndef _ROS_tencentimu_Motorcmd_h
#define _ROS_tencentimu_Motorcmd_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace tencentimu
{

  class Motorcmd : public ros::Msg
  {
    public:
      uint8_t Kp;
      uint8_t Ki;
      int16_t target_current;
      uint8_t rotor_offset;
      uint8_t max_vel;
      float angle_d;

    Motorcmd():
      Kp(0),
      Ki(0),
      target_current(0),
      rotor_offset(0),
      max_vel(0),
      angle_d(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->Kp >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Kp);
      *(outbuffer + offset + 0) = (this->Ki >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Ki);
      union {
        int16_t real;
        uint16_t base;
      } u_target_current;
      u_target_current.real = this->target_current;
      *(outbuffer + offset + 0) = (u_target_current.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_target_current.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->target_current);
      *(outbuffer + offset + 0) = (this->rotor_offset >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rotor_offset);
      *(outbuffer + offset + 0) = (this->max_vel >> (8 * 0)) & 0xFF;
      offset += sizeof(this->max_vel);
      union {
        float real;
        uint32_t base;
      } u_angle_d;
      u_angle_d.real = this->angle_d;
      *(outbuffer + offset + 0) = (u_angle_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_d);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->Kp =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->Kp);
      this->Ki =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->Ki);
      union {
        int16_t real;
        uint16_t base;
      } u_target_current;
      u_target_current.base = 0;
      u_target_current.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_target_current.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->target_current = u_target_current.real;
      offset += sizeof(this->target_current);
      this->rotor_offset =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->rotor_offset);
      this->max_vel =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->max_vel);
      union {
        float real;
        uint32_t base;
      } u_angle_d;
      u_angle_d.base = 0;
      u_angle_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_d = u_angle_d.real;
      offset += sizeof(this->angle_d);
     return offset;
    }

    const char * getType(){ return "tencentimu/Motorcmd"; };
    const char * getMD5(){ return "1691d66cf3b6a56998e8bfd0a2f4e1c3"; };

  };

}
#endif