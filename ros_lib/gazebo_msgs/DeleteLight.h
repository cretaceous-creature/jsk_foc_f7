#ifndef _ROS_SERVICE_DeleteLight_h
#define _ROS_SERVICE_DeleteLight_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gazebo_msgs
{

static const char DELETELIGHT[] = "gazebo_msgs/DeleteLight";

  class DeleteLightRequest : public ros::Msg
  {
    public:
      const char* light_name;

    DeleteLightRequest():
      light_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_light_name = strlen(this->light_name);
      memcpy(outbuffer + offset, &length_light_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->light_name, length_light_name);
      offset += length_light_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_light_name;
      memcpy(&length_light_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_light_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_light_name-1]=0;
      this->light_name = (char *)(inbuffer + offset-1);
      offset += length_light_name;
     return offset;
    }

    const char * getType(){ return DELETELIGHT; };
    const char * getMD5(){ return "4fb676dfb4741fc866365702a859441c"; };

  };

  class DeleteLightResponse : public ros::Msg
  {
    public:
      bool success;
      const char* status_message;

    DeleteLightResponse():
      success(0),
      status_message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_status_message = strlen(this->status_message);
      memcpy(outbuffer + offset, &length_status_message, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->status_message, length_status_message);
      offset += length_status_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_status_message;
      memcpy(&length_status_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status_message-1]=0;
      this->status_message = (char *)(inbuffer + offset-1);
      offset += length_status_message;
     return offset;
    }

    const char * getType(){ return DELETELIGHT; };
    const char * getMD5(){ return "2ec6f3eff0161f4257b808b12bc830c2"; };

  };

  class DeleteLight {
    public:
    typedef DeleteLightRequest Request;
    typedef DeleteLightResponse Response;
  };

}
#endif
