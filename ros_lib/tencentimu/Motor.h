#ifndef _ROS_tencentimu_Motor_h
#define _ROS_tencentimu_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace tencentimu
{

  class Motor : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int16_t zcount;
      uint16_t count;
      int16_t w;
      int16_t c_q;
      int16_t c_d;

    Motor():
      header(),
      zcount(0),
      count(0),
      w(0),
      c_q(0),
      c_d(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_zcount;
      u_zcount.real = this->zcount;
      *(outbuffer + offset + 0) = (u_zcount.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_zcount.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->zcount);
      *(outbuffer + offset + 0) = (this->count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->count >> (8 * 1)) & 0xFF;
      offset += sizeof(this->count);
      union {
        int16_t real;
        uint16_t base;
      } u_w;
      u_w.real = this->w;
      *(outbuffer + offset + 0) = (u_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_w.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->w);
      union {
        int16_t real;
        uint16_t base;
      } u_c_q;
      u_c_q.real = this->c_q;
      *(outbuffer + offset + 0) = (u_c_q.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_c_q.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->c_q);
      union {
        int16_t real;
        uint16_t base;
      } u_c_d;
      u_c_d.real = this->c_d;
      *(outbuffer + offset + 0) = (u_c_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_c_d.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->c_d);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_zcount;
      u_zcount.base = 0;
      u_zcount.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_zcount.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->zcount = u_zcount.real;
      offset += sizeof(this->zcount);
      this->count =  ((uint16_t) (*(inbuffer + offset)));
      this->count |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->count);
      union {
        int16_t real;
        uint16_t base;
      } u_w;
      u_w.base = 0;
      u_w.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_w.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->w = u_w.real;
      offset += sizeof(this->w);
      union {
        int16_t real;
        uint16_t base;
      } u_c_q;
      u_c_q.base = 0;
      u_c_q.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_c_q.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->c_q = u_c_q.real;
      offset += sizeof(this->c_q);
      union {
        int16_t real;
        uint16_t base;
      } u_c_d;
      u_c_d.base = 0;
      u_c_d.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_c_d.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->c_d = u_c_d.real;
      offset += sizeof(this->c_d);
     return offset;
    }

    const char * getType(){ return "tencentimu/Motor"; };
    const char * getMD5(){ return "c316d26089bdb55282e6acdec54486d6"; };

  };

}
#endif