#ifndef _ROS_aerial_robot_base_State_h
#define _ROS_aerial_robot_base_State_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_base
{

  class State : public ros::Msg
  {
    public:
      const char* id;
      float pos;
      float raw_pos;
      float vel;
      float raw_vel;
      float kf_pos;
      float kf_vel;
      float kfb_pos;
      float kfb_vel;
      float kfb_bias;
      uint8_t reserves_length;
      float st_reserves;
      float * reserves;

    State():
      id(""),
      pos(0),
      raw_pos(0),
      vel(0),
      raw_vel(0),
      kf_pos(0),
      kf_vel(0),
      kfb_pos(0),
      kfb_vel(0),
      kfb_bias(0),
      reserves_length(0), reserves(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      memcpy(outbuffer + offset, &length_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_pos;
      u_pos.real = this->pos;
      *(outbuffer + offset + 0) = (u_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos);
      union {
        float real;
        uint32_t base;
      } u_raw_pos;
      u_raw_pos.real = this->raw_pos;
      *(outbuffer + offset + 0) = (u_raw_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_raw_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_raw_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_raw_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->raw_pos);
      union {
        float real;
        uint32_t base;
      } u_vel;
      u_vel.real = this->vel;
      *(outbuffer + offset + 0) = (u_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel);
      union {
        float real;
        uint32_t base;
      } u_raw_vel;
      u_raw_vel.real = this->raw_vel;
      *(outbuffer + offset + 0) = (u_raw_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_raw_vel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_raw_vel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_raw_vel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->raw_vel);
      union {
        float real;
        uint32_t base;
      } u_kf_pos;
      u_kf_pos.real = this->kf_pos;
      *(outbuffer + offset + 0) = (u_kf_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kf_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kf_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kf_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kf_pos);
      union {
        float real;
        uint32_t base;
      } u_kf_vel;
      u_kf_vel.real = this->kf_vel;
      *(outbuffer + offset + 0) = (u_kf_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kf_vel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kf_vel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kf_vel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kf_vel);
      union {
        float real;
        uint32_t base;
      } u_kfb_pos;
      u_kfb_pos.real = this->kfb_pos;
      *(outbuffer + offset + 0) = (u_kfb_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kfb_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kfb_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kfb_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kfb_pos);
      union {
        float real;
        uint32_t base;
      } u_kfb_vel;
      u_kfb_vel.real = this->kfb_vel;
      *(outbuffer + offset + 0) = (u_kfb_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kfb_vel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kfb_vel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kfb_vel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kfb_vel);
      union {
        float real;
        uint32_t base;
      } u_kfb_bias;
      u_kfb_bias.real = this->kfb_bias;
      *(outbuffer + offset + 0) = (u_kfb_bias.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kfb_bias.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kfb_bias.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kfb_bias.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kfb_bias);
      *(outbuffer + offset++) = reserves_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < reserves_length; i++){
      union {
        float real;
        uint32_t base;
      } u_reservesi;
      u_reservesi.real = this->reserves[i];
      *(outbuffer + offset + 0) = (u_reservesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_reservesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_reservesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_reservesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->reserves[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      memcpy(&length_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_pos;
      u_pos.base = 0;
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos = u_pos.real;
      offset += sizeof(this->pos);
      union {
        float real;
        uint32_t base;
      } u_raw_pos;
      u_raw_pos.base = 0;
      u_raw_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_raw_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_raw_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_raw_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->raw_pos = u_raw_pos.real;
      offset += sizeof(this->raw_pos);
      union {
        float real;
        uint32_t base;
      } u_vel;
      u_vel.base = 0;
      u_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vel = u_vel.real;
      offset += sizeof(this->vel);
      union {
        float real;
        uint32_t base;
      } u_raw_vel;
      u_raw_vel.base = 0;
      u_raw_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_raw_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_raw_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_raw_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->raw_vel = u_raw_vel.real;
      offset += sizeof(this->raw_vel);
      union {
        float real;
        uint32_t base;
      } u_kf_pos;
      u_kf_pos.base = 0;
      u_kf_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kf_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kf_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kf_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kf_pos = u_kf_pos.real;
      offset += sizeof(this->kf_pos);
      union {
        float real;
        uint32_t base;
      } u_kf_vel;
      u_kf_vel.base = 0;
      u_kf_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kf_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kf_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kf_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kf_vel = u_kf_vel.real;
      offset += sizeof(this->kf_vel);
      union {
        float real;
        uint32_t base;
      } u_kfb_pos;
      u_kfb_pos.base = 0;
      u_kfb_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kfb_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kfb_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kfb_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kfb_pos = u_kfb_pos.real;
      offset += sizeof(this->kfb_pos);
      union {
        float real;
        uint32_t base;
      } u_kfb_vel;
      u_kfb_vel.base = 0;
      u_kfb_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kfb_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kfb_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kfb_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kfb_vel = u_kfb_vel.real;
      offset += sizeof(this->kfb_vel);
      union {
        float real;
        uint32_t base;
      } u_kfb_bias;
      u_kfb_bias.base = 0;
      u_kfb_bias.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kfb_bias.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kfb_bias.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kfb_bias.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kfb_bias = u_kfb_bias.real;
      offset += sizeof(this->kfb_bias);
      uint8_t reserves_lengthT = *(inbuffer + offset++);
      if(reserves_lengthT > reserves_length)
        this->reserves = (float*)realloc(this->reserves, reserves_lengthT * sizeof(float));
      offset += 3;
      reserves_length = reserves_lengthT;
      for( uint8_t i = 0; i < reserves_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_reserves;
      u_st_reserves.base = 0;
      u_st_reserves.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_reserves.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_reserves.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_reserves.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_reserves = u_st_reserves.real;
      offset += sizeof(this->st_reserves);
        memcpy( &(this->reserves[i]), &(this->st_reserves), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/State"; };
    const char * getMD5(){ return "69076ce2eab1d2c40b5c4dceeae53394"; };

  };

}
#endif