#ifndef _ROS_aerial_robot_msgs_DynamicReconfigureLevels_h
#define _ROS_aerial_robot_msgs_DynamicReconfigureLevels_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aerial_robot_msgs
{

  class DynamicReconfigureLevels : public ros::Msg
  {
    public:
      enum { RECONFIGURE_KALMAN_FILTER_FLAG =  0 };
      enum { RECONFIGURE_INPUT_SIGMA =  1 };
      enum { RECONFIGURE_BIAS_SIGMA =  2 };
      enum { RECONFIGURE_MEASURE_SIGMA =  3 };
      enum { RECONFIGURE_CONTROL_FLAG =  0 };
      enum { RECONFIGURE_CONTROL_LOOP_RATE =  1 };
      enum { RECONFIGURE_POS_P_GAIN =  2 };
      enum { RECONFIGURE_POS_I_GAIN =  3 };
      enum { RECONFIGURE_POS_D_GAIN =  4 };
      enum { RECONFIGURE_POS_P_GAIN_LAND =  5 };
      enum { RECONFIGURE_POS_I_GAIN_LAND =  6 };
      enum { RECONFIGURE_POS_I_GAIN_HOVER =  7 };
      enum { RECONFIGURE_POS_D_GAIN_LAND =  8 };
      enum { RECONFIGURE_CONST_P_CONTROL_THRESHOLD_LAND =  9 };
      enum { RECONFIGURE_CONST_P_TERM_LEVEL1_VALUE_LAND =  10 };
      enum { RECONFIGURE_CONST_P_TERM_LEVEL2_VALUE_LAND =  11 };
      enum { RECONFIGURE_CONST_I_CONTROL_THRESHOLD_LAND =  12 };
      enum { RECONFIGURE_CONST_I_TERM_VALUE_LAND =  13 };
      enum { RECONFIGURE_OFFSET =  14 };
      enum { RECONFIGURE_POS_LIMIT =  15 };
      enum { RECONFIGURE_POS_P_LIMIT =  16 };
      enum { RECONFIGURE_POS_P_LIMIT_HOVER =  17 };
      enum { RECONFIGURE_POS_I_LIMIT =  18 };
      enum { RECONFIGURE_POS_D_LIMIT =  19 };
      enum { RECONFIGURE_VEL_VALUE_LIMIT_HOVER =  20 };
      enum { RECONFIGURE_I_ENABLE_LIMIT_HOVER =  21 };
      enum { RECONFIGURE_VEL_P_GAIN =  22 };
      enum { RECONFIGURE_VEL_I_GAIN =  23 };

    DynamicReconfigureLevels()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/DynamicReconfigureLevels"; };
    const char * getMD5(){ return "de9327a663b3ba9bfb4159bf27296bdb"; };

  };

}
#endif