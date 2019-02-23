#ifndef _ROS_jsk_imu_mini_msgs_Potentio_h
#define _ROS_jsk_imu_mini_msgs_Potentio_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace jsk_imu_mini_msgs
{

  class Potentio : public ros::Msg
  {
    public:
      ros::Time stamp;
      uint8_t potentio_length;
      uint16_t st_potentio;
      uint16_t * potentio;

    Potentio():
      stamp(),
      potentio_length(0), potentio(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->stamp.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->stamp.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->stamp.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->stamp.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->stamp.sec);
      *(outbuffer + offset + 0) = (this->stamp.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->stamp.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->stamp.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->stamp.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->stamp.nsec);
      *(outbuffer + offset++) = potentio_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < potentio_length; i++){
      *(outbuffer + offset + 0) = (this->potentio[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->potentio[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->potentio[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->stamp.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->stamp.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->stamp.sec);
      this->stamp.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->stamp.nsec);
      uint8_t potentio_lengthT = *(inbuffer + offset++);
      if(potentio_lengthT > potentio_length)
        this->potentio = (uint16_t*)realloc(this->potentio, potentio_lengthT * sizeof(uint16_t));
      offset += 3;
      potentio_length = potentio_lengthT;
      for( uint8_t i = 0; i < potentio_length; i++){
      this->st_potentio =  ((uint16_t) (*(inbuffer + offset)));
      this->st_potentio |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_potentio);
        memcpy( &(this->potentio[i]), &(this->st_potentio), sizeof(uint16_t));
      }
     return offset;
    }

    const char * getType(){ return "jsk_imu_mini_msgs/Potentio"; };
    const char * getMD5(){ return "3c38bfc62efc8af1fef221b81830300a"; };

  };

}
#endif