#ifndef _ROS_aerial_robot_msgs_AttGains_h
#define _ROS_aerial_robot_msgs_AttGains_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class AttGains : public ros::Msg
  {
    public:
      uint8_t roll_pitch_p_gain;
      uint8_t roll_d_gain;
      uint8_t pitch_d_gain;

    AttGains():
      roll_pitch_p_gain(0),
      roll_d_gain(0),
      pitch_d_gain(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->roll_pitch_p_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->roll_pitch_p_gain);
      *(outbuffer + offset + 0) = (this->roll_d_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->roll_d_gain);
      *(outbuffer + offset + 0) = (this->pitch_d_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pitch_d_gain);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->roll_pitch_p_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->roll_pitch_p_gain);
      this->roll_d_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->roll_d_gain);
      this->pitch_d_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pitch_d_gain);
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/AttGains"; };
    const char * getMD5(){ return "89c1c5bf3fa6de708a0d3d632e6b142f"; };

  };

}
#endif