#ifndef _ROS_aerial_robot_base_ImuQu_h
#define _ROS_aerial_robot_base_ImuQu_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace aerial_robot_base
{

  class ImuQu : public ros::Msg
  {
    public:
      ros::Time stamp;
      float acc;

    ImuQu():
      stamp(),
      acc(0)
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
      union {
        float real;
        uint32_t base;
      } u_acc;
      u_acc.real = this->acc;
      *(outbuffer + offset + 0) = (u_acc.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acc.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acc.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acc);
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
      union {
        float real;
        uint32_t base;
      } u_acc;
      u_acc.base = 0;
      u_acc.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acc.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acc.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acc = u_acc.real;
      offset += sizeof(this->acc);
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/ImuQu"; };
    const char * getMD5(){ return "d2382f675b79186a5fc4a7f13e8738bc"; };

  };

}
#endif