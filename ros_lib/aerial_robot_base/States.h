#ifndef _ROS_aerial_robot_base_States_h
#define _ROS_aerial_robot_base_States_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "aerial_robot_base/State.h"

namespace aerial_robot_base
{

  class States : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t states_length;
      aerial_robot_base::State st_states;
      aerial_robot_base::State * states;

    States():
      header(),
      states_length(0), states(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = states_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < states_length; i++){
      offset += this->states[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t states_lengthT = *(inbuffer + offset++);
      if(states_lengthT > states_length)
        this->states = (aerial_robot_base::State*)realloc(this->states, states_lengthT * sizeof(aerial_robot_base::State));
      offset += 3;
      states_length = states_lengthT;
      for( uint8_t i = 0; i < states_length; i++){
      offset += this->st_states.deserialize(inbuffer + offset);
        memcpy( &(this->states[i]), &(this->st_states), sizeof(aerial_robot_base::State));
      }
     return offset;
    }

    const char * getType(){ return "aerial_robot_base/States"; };
    const char * getMD5(){ return "e5a21c76f8943f802a32a7d896ec59b9"; };

  };

}
#endif