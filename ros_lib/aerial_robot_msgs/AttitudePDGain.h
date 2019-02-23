#ifndef _ROS_aerial_robot_msgs_AttitudePDGain_h
#define _ROS_aerial_robot_msgs_AttitudePDGain_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class AttitudePDGain : public ros::Msg
  {
    public:
      uint8_t roll_pitch_p;
      uint8_t roll_d;
      uint8_t pitch_d;
      uint8_t yaw_d;

    AttitudePDGain():
      roll_pitch_p(0),
      roll_d(0),
      pitch_d(0),
      yaw_d(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->roll_pitch_p >> (8 * 0)) & 0xFF;
      offset += sizeof(this->roll_pitch_p);
      *(outbuffer + offset + 0) = (this->roll_d >> (8 * 0)) & 0xFF;
      offset += sizeof(this->roll_d);
      *(outbuffer + offset + 0) = (this->pitch_d >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pitch_d);
      *(outbuffer + offset + 0) = (this->yaw_d >> (8 * 0)) & 0xFF;
      offset += sizeof(this->yaw_d);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->roll_pitch_p =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->roll_pitch_p);
      this->roll_d =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->roll_d);
      this->pitch_d =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pitch_d);
      this->yaw_d =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->yaw_d);
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/AttitudePDGain"; };
    const char * getMD5(){ return "5ff784db798470c9dd3edf2924521fb3"; };

  };

}
#endif