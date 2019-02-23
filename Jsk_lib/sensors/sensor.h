/******************
 *
 * JSK MBZIRC
 */
#ifndef __SENSOR_H
#define __SENSOR_H

/* Includes -----------------------*/
#include "stm32f7xx_hal.h"
#include <vector>
/* SENSOR BASE CLASS
 *
 **/
template<typename T>
class SENSOR_
{
public:
  SENSOR_(){};
  ~SENSOR_(){};
  std::vector<T> data_queue;
  static const uint16_t DEFAULT_DATA_SIZE = 10;  //11 data
  uint16_t update(T new_data, uint16_t queue_size = DEFAULT_DATA_SIZE) //update data queue
  {
    data_queue.push_back(new_data);
    if(data_queue.size() > queue_size)
      data_queue.erase(data_queue.begin());
    return data_queue.size();
  };
  T Average_vec(std::vector<T> *data)
  {
	  T sum = data->at(0);
	  for(int i = 1; i < data->size(); i++)
		  sum += data->at(i);

	  return sum/data->size();

  };
private:


};

#endif /*__sensor_H */
