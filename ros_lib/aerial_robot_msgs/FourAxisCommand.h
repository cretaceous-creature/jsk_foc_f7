#ifndef _ROS_aerial_robot_msgs_FourAxisCommand_h
#define _ROS_aerial_robot_msgs_FourAxisCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class FourAxisCommand : public ros::Msg
  {
    public:
      int16_t angles[2];
      int32_t yaw_pi_term[4];
      uint16_t throttle_pid_term[4];

    FourAxisCommand():
      angles(),
      yaw_pi_term(),
      throttle_pid_term()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint8_t i = 0; i < 2; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_anglesi;
      u_anglesi.real = this->angles[i];
      *(outbuffer + offset + 0) = (u_anglesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_anglesi.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angles[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_pi_termi;
      u_yaw_pi_termi.real = this->yaw_pi_term[i];
      *(outbuffer + offset + 0) = (u_yaw_pi_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_pi_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_pi_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_pi_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_pi_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      *(outbuffer + offset + 0) = (this->throttle_pid_term[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->throttle_pid_term[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->throttle_pid_term[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint8_t i = 0; i < 2; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_anglesi;
      u_anglesi.base = 0;
      u_anglesi.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_anglesi.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angles[i] = u_anglesi.real;
      offset += sizeof(this->angles[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yaw_pi_termi;
      u_yaw_pi_termi.base = 0;
      u_yaw_pi_termi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_pi_termi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_pi_termi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_pi_termi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_pi_term[i] = u_yaw_pi_termi.real;
      offset += sizeof(this->yaw_pi_term[i]);
      }
      for( uint8_t i = 0; i < 4; i++){
      this->throttle_pid_term[i] =  ((uint16_t) (*(inbuffer + offset)));
      this->throttle_pid_term[i] |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->throttle_pid_term[i]);
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/FourAxisCommand"; };
    const char * getMD5(){ return "941924200cdaa55f4a83697b66744f42"; };

  };

}
#endif