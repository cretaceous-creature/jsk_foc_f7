#ifndef _ROS_aerial_robot_msgs_Gps_h
#define _ROS_aerial_robot_msgs_Gps_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace aerial_robot_msgs
{

  class Gps : public ros::Msg
  {
    public:
      ros::Time stamp;
      float location[2];
      float velocity[2];
      uint8_t sat_num;

    Gps():
      stamp(),
      location(),
      velocity(),
      sat_num(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->stamp.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->stamp.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->stamp.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->stamp.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->stamp.sec);
      *(outbuffer + offset + 0) = (this->stamp.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->stamp.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->stamp.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->stamp.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->stamp.nsec);
      for( uint8_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_locationi;
      u_locationi.real = this->location[i];
      *(outbuffer + offset + 0) = (u_locationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_locationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_locationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_locationi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->location[i]);
      }
      for( uint8_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_velocityi;
      u_velocityi.real = this->velocity[i];
      *(outbuffer + offset + 0) = (u_velocityi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocityi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocityi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocityi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity[i]);
      }
      *(outbuffer + offset + 0) = (this->sat_num >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sat_num);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->stamp.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->stamp.sec);
      this->stamp.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->stamp.nsec);
      for( uint8_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_locationi;
      u_locationi.base = 0;
      u_locationi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_locationi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_locationi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_locationi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->location[i] = u_locationi.real;
      offset += sizeof(this->location[i]);
      }
      for( uint8_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_velocityi;
      u_velocityi.base = 0;
      u_velocityi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocityi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocityi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocityi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity[i] = u_velocityi.real;
      offset += sizeof(this->velocity[i]);
      }
      this->sat_num =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sat_num);
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/Gps"; };
    const char * getMD5(){ return "b9b55701ff5240f76ada29af2827853c"; };

  };

}
#endif