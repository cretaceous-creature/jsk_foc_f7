#ifndef _ROS_aerial_robot_base_Pid_h
#define _ROS_aerial_robot_base_Pid_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_base
{

  class Pid : public ros::Msg
  {
    public:
      uint8_t total_length;
      float st_total;
      float * total;
      uint8_t p_term_length;
      float st_p_term;
      float * p_term;
      uint8_t i_term_length;
      float st_i_term;
      float * i_term;
      uint8_t d_term_length;
      float st_d_term;
      float * d_term;
      float pos_err_transform;
      float pos_err_no_transform;
      float vel_err_transform;
      float vel_err_no_transform;

    Pid():
      total_length(0), total(NULL),
      p_term_length(0), p_term(NULL),
      i_term_length(0), i_term(NULL),
      d_term_length(0), d_term(NULL),
      pos_err_transform(0),
      pos_err_no_transform(0),
      vel_err_transform(0),
      vel_err_no_transform(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = total_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < total_length; i++){
      union {
        float real;
        uint32_t base;
      } u_totali;
      u_totali.real = this->total[i];
      *(outbuffer + offset + 0) = (u_totali.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_totali.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_totali.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_totali.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->total[i]);
      }
      *(outbuffer + offset++) = p_term_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < p_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_p_termi;
      u_p_termi.real = this->p_term[i];
      *(outbuffer + offset + 0) = (u_p_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_p_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_p_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_p_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->p_term[i]);
      }
      *(outbuffer + offset++) = i_term_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < i_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_i_termi;
      u_i_termi.real = this->i_term[i];
      *(outbuffer + offset + 0) = (u_i_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i_term[i]);
      }
      *(outbuffer + offset++) = d_term_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < d_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_d_termi;
      u_d_termi.real = this->d_term[i];
      *(outbuffer + offset + 0) = (u_d_termi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_d_termi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_d_termi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_d_termi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d_term[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_pos_err_transform;
      u_pos_err_transform.real = this->pos_err_transform;
      *(outbuffer + offset + 0) = (u_pos_err_transform.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_err_transform.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_err_transform.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_err_transform.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_err_transform);
      union {
        float real;
        uint32_t base;
      } u_pos_err_no_transform;
      u_pos_err_no_transform.real = this->pos_err_no_transform;
      *(outbuffer + offset + 0) = (u_pos_err_no_transform.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_err_no_transform.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_err_no_transform.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_err_no_transform.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_err_no_transform);
      union {
        float real;
        uint32_t base;
      } u_vel_err_transform;
      u_vel_err_transform.real = this->vel_err_transform;
      *(outbuffer + offset + 0) = (u_vel_err_transform.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel_err_transform.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vel_err_transform.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vel_err_transform.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel_err_transform);
      union {
        float real;
        uint32_t base;
      } u_vel_err_no_transform;
      u_vel_err_no_transform.real = this->vel_err_no_transform;
      *(outbuffer + offset + 0) = (u_vel_err_no_transform.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel_err_no_transform.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vel_err_no_transform.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vel_err_no_transform.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel_err_no_transform);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t total_lengthT = *(inbuffer + offset++);
      if(total_lengthT > total_length)
        this->total = (float*)realloc(this->total, total_lengthT * sizeof(float));
      offset += 3;
      total_length = total_lengthT;
      for( uint8_t i = 0; i < total_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_total;
      u_st_total.base = 0;
      u_st_total.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_total.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_total.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_total.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_total = u_st_total.real;
      offset += sizeof(this->st_total);
        memcpy( &(this->total[i]), &(this->st_total), sizeof(float));
      }
      uint8_t p_term_lengthT = *(inbuffer + offset++);
      if(p_term_lengthT > p_term_length)
        this->p_term = (float*)realloc(this->p_term, p_term_lengthT * sizeof(float));
      offset += 3;
      p_term_length = p_term_lengthT;
      for( uint8_t i = 0; i < p_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_p_term;
      u_st_p_term.base = 0;
      u_st_p_term.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_p_term.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_p_term.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_p_term.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_p_term = u_st_p_term.real;
      offset += sizeof(this->st_p_term);
        memcpy( &(this->p_term[i]), &(this->st_p_term), sizeof(float));
      }
      uint8_t i_term_lengthT = *(inbuffer + offset++);
      if(i_term_lengthT > i_term_length)
        this->i_term = (float*)realloc(this->i_term, i_term_lengthT * sizeof(float));
      offset += 3;
      i_term_length = i_term_lengthT;
      for( uint8_t i = 0; i < i_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_i_term;
      u_st_i_term.base = 0;
      u_st_i_term.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_i_term.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_i_term.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_i_term.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_i_term = u_st_i_term.real;
      offset += sizeof(this->st_i_term);
        memcpy( &(this->i_term[i]), &(this->st_i_term), sizeof(float));
      }
      uint8_t d_term_lengthT = *(inbuffer + offset++);
      if(d_term_lengthT > d_term_length)
        this->d_term = (float*)realloc(this->d_term, d_term_lengthT * sizeof(float));
      offset += 3;
      d_term_length = d_term_lengthT;
      for( uint8_t i = 0; i < d_term_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_d_term;
      u_st_d_term.base = 0;
      u_st_d_term.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_d_term.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_d_term.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_d_term.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_d_term = u_st_d_term.real;
      offset += sizeof(this->st_d_term);
        memcpy( &(this->d_term[i]), &(this->st_d_term), sizeof(float));
      }
      union {
        float real;
        uint32_t base;
      } u_pos_err_transform;
      u_pos_err_transform.base = 0;
      u_pos_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos_err_transform = u_pos_err_transform.real;
      offset += sizeof(this->pos_err_transform);
      union {
        float real;
        uint32_t base;
      } u_pos_err_no_transform;
      u_pos_err_no_transform.base = 0;
      u_pos_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos_err_no_transform = u_pos_err_no_transform.real;
      offset += sizeof(this->pos_err_no_transform);
      union {
        float real;
        uint32_t base;
      } u_vel_err_transform;
      u_vel_err_transform.base = 0;
      u_vel_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vel_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vel_err_transform.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vel_err_transform = u_vel_err_transform.real;
      offset += sizeof(this->vel_err_transform);
      union {
        float real;
        uint32_t base;
      } u_vel_err_no_transform;
      u_vel_err_no_transform.base = 0;
      u_vel_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vel_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vel_err_no_transform.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vel_err_no_transform = u_vel_err_no_transform.real;
      offset += sizeof(this->vel_err_no_transform);
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/Pid"; };
    const char * getMD5(){ return "b7a7d16748316cbded44d5e489e4a5ea"; };

  };

}
#endif