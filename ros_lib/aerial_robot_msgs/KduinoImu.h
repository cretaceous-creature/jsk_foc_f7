#ifndef _ROS_aerial_robot_msgs_KduinoImu_h
#define _ROS_aerial_robot_msgs_KduinoImu_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace aerial_robot_msgs
{

  class KduinoImu : public ros::Msg
  {
    public:
      ros::Time stamp;
      int16_t accData[3];
      int16_t gyroData[3];
      int16_t magData[3];
      int16_t angle[3];
      uint16_t altitude;

    KduinoImu():
      stamp(),
      accData(),
      gyroData(),
      magData(),
      angle(),
      altitude(0)
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
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_accDatai;
      u_accDatai.real = this->accData[i];
      *(outbuffer + offset + 0) = (u_accDatai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_accDatai.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->accData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_gyroDatai;
      u_gyroDatai.real = this->gyroData[i];
      *(outbuffer + offset + 0) = (u_gyroDatai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gyroDatai.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->gyroData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_magDatai;
      u_magDatai.real = this->magData[i];
      *(outbuffer + offset + 0) = (u_magDatai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_magDatai.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->magData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_anglei;
      u_anglei.real = this->angle[i];
      *(outbuffer + offset + 0) = (u_anglei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_anglei.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle[i]);
      }
      *(outbuffer + offset + 0) = (this->altitude >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->altitude >> (8 * 1)) & 0xFF;
      offset += sizeof(this->altitude);
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
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_accDatai;
      u_accDatai.base = 0;
      u_accDatai.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_accDatai.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->accData[i] = u_accDatai.real;
      offset += sizeof(this->accData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_gyroDatai;
      u_gyroDatai.base = 0;
      u_gyroDatai.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_gyroDatai.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->gyroData[i] = u_gyroDatai.real;
      offset += sizeof(this->gyroData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_magDatai;
      u_magDatai.base = 0;
      u_magDatai.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_magDatai.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->magData[i] = u_magDatai.real;
      offset += sizeof(this->magData[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_anglei;
      u_anglei.base = 0;
      u_anglei.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_anglei.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle[i] = u_anglei.real;
      offset += sizeof(this->angle[i]);
      }
      this->altitude =  ((uint16_t) (*(inbuffer + offset)));
      this->altitude |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->altitude);
     return offset;
    }

    const char * getType(){ return "aerial_robot_msgs/KduinoImu"; };
    const char * getMD5(){ return "26c86350c7d7c21066119d88ee91a7fd"; };

  };

}
#endif