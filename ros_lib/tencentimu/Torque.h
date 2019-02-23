#ifndef _ROS_tencentimu_Torque_h
#define _ROS_tencentimu_Torque_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace tencentimu
{

  class Torque : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float torque;
      float speed;
      float w;
      float target_cur;
      float cq;
      float cd;
      uint16_t count;

    Torque():
      header(),
      torque(0),
      speed(0),
      w(0),
      target_cur(0),
      cq(0),
      cd(0),
      count(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_torque;
      u_torque.real = this->torque;
      *(outbuffer + offset + 0) = (u_torque.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_torque.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_torque.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_torque.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->torque);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.real = this->speed;
      *(outbuffer + offset + 0) = (u_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_w;
      u_w.real = this->w;
      *(outbuffer + offset + 0) = (u_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_w.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_w.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_w.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->w);
      union {
        float real;
        uint32_t base;
      } u_target_cur;
      u_target_cur.real = this->target_cur;
      *(outbuffer + offset + 0) = (u_target_cur.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_target_cur.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_target_cur.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_target_cur.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->target_cur);
      union {
        float real;
        uint32_t base;
      } u_cq;
      u_cq.real = this->cq;
      *(outbuffer + offset + 0) = (u_cq.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cq.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cq.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cq.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cq);
      union {
        float real;
        uint32_t base;
      } u_cd;
      u_cd.real = this->cd;
      *(outbuffer + offset + 0) = (u_cd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cd);
      *(outbuffer + offset + 0) = (this->count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->count >> (8 * 1)) & 0xFF;
      offset += sizeof(this->count);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_torque;
      u_torque.base = 0;
      u_torque.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_torque.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_torque.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_torque.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->torque = u_torque.real;
      offset += sizeof(this->torque);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.base = 0;
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed = u_speed.real;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_w;
      u_w.base = 0;
      u_w.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_w.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_w.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_w.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->w = u_w.real;
      offset += sizeof(this->w);
      union {
        float real;
        uint32_t base;
      } u_target_cur;
      u_target_cur.base = 0;
      u_target_cur.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_target_cur.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_target_cur.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_target_cur.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->target_cur = u_target_cur.real;
      offset += sizeof(this->target_cur);
      union {
        float real;
        uint32_t base;
      } u_cq;
      u_cq.base = 0;
      u_cq.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cq.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cq.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cq.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cq = u_cq.real;
      offset += sizeof(this->cq);
      union {
        float real;
        uint32_t base;
      } u_cd;
      u_cd.base = 0;
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cd = u_cd.real;
      offset += sizeof(this->cd);
      this->count =  ((uint16_t) (*(inbuffer + offset)));
      this->count |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->count);
     return offset;
    }

    const char * getType(){ return "tencentimu/Torque"; };
    const char * getMD5(){ return "6375affef890f85b257a3c4bf813b7fd"; };

  };

}
#endif