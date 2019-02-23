#ifndef _ROS_aerial_robot_base_ImuData_h
#define _ROS_aerial_robot_base_ImuData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace aerial_robot_base
{

  class ImuData : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Vector3 accelerometer;
      geometry_msgs::Vector3 gyrometer;
      geometry_msgs::Vector3 magnetometer;
      geometry_msgs::Vector3 acc_body_frame;
      geometry_msgs::Vector3 acc_world_frame;
      geometry_msgs::Vector3 acc_non_bias_world_frame;
      geometry_msgs::Vector3 angles;
      float height;
      geometry_msgs::Vector3 position;
      geometry_msgs::Vector3 velocity;

    ImuData():
      header(),
      accelerometer(),
      gyrometer(),
      magnetometer(),
      acc_body_frame(),
      acc_world_frame(),
      acc_non_bias_world_frame(),
      angles(),
      height(0),
      position(),
      velocity()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->accelerometer.serialize(outbuffer + offset);
      offset += this->gyrometer.serialize(outbuffer + offset);
      offset += this->magnetometer.serialize(outbuffer + offset);
      offset += this->acc_body_frame.serialize(outbuffer + offset);
      offset += this->acc_world_frame.serialize(outbuffer + offset);
      offset += this->acc_non_bias_world_frame.serialize(outbuffer + offset);
      offset += this->angles.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_height;
      u_height.real = this->height;
      *(outbuffer + offset + 0) = (u_height.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      offset += this->position.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->accelerometer.deserialize(inbuffer + offset);
      offset += this->gyrometer.deserialize(inbuffer + offset);
      offset += this->magnetometer.deserialize(inbuffer + offset);
      offset += this->acc_body_frame.deserialize(inbuffer + offset);
      offset += this->acc_world_frame.deserialize(inbuffer + offset);
      offset += this->acc_non_bias_world_frame.deserialize(inbuffer + offset);
      offset += this->angles.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_height;
      u_height.base = 0;
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height = u_height.real;
      offset += sizeof(this->height);
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/ImuData"; };
    const char * getMD5(){ return "931f8d31e7dc9f15c3524da9cfd5ddbd"; };

  };

}
#endif