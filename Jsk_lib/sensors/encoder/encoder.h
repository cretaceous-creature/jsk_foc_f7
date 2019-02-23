/******************
 *
 * JSK MBZIRC
 */
#ifndef __ENCODER_H
#define __ENCODER_H

/* Includes --------------------*/
#include <sensors/sensor.h>
typedef int Enctype ;
/* encoder related */
namespace encoder
{
  class ENCODER_ : public SENSOR_<Enctype>  //the data is uint16_t
  {
  public:
    ENCODER_(){};
    ~ENCODER_(){};
    const uint16_t ENC_OVE = 30000;  //overflow
    const float ENC_UNI_LEN = 0.000125;
    std::vector<Enctype> velo_queue;
    std::vector<Enctype> acc_queue;
#define SYSFREQ 1000
    //average velo and acc
    float ave_velo = 0;
    float ave_acc = 0;
    uint16_t update(Enctype new_data, uint16_t queue_size = DEFAULT_DATA_SIZE) //update data queue
    {
      //acc data
      if(data_queue.size())
        {
          Enctype tmpvelo = new_data - data_queue.back();
          tmpvelo = tmpvelo>(ENC_OVE/2)?tmpvelo-ENC_OVE:tmpvelo;
          tmpvelo = tmpvelo<(-ENC_OVE/2)?tmpvelo+ENC_OVE:tmpvelo;
          //push in acc data
          if(velo_queue.size())
            acc_queue.push_back(tmpvelo-velo_queue.back());
          //push in velo data
          velo_queue.push_back(tmpvelo);
        }
      //push in sensor data.
      data_queue.push_back(new_data);
      if(data_queue.size() > queue_size)
        data_queue.erase(data_queue.begin());
      if(velo_queue.size() > queue_size)
        {
          velo_queue.erase(velo_queue.begin());
          ave_velo = Average_vec(&velo_queue);
        }
      if(acc_queue.size() > queue_size)
        {
          acc_queue.erase(acc_queue.begin());
          ave_acc = Average_vec(&acc_queue);
        }

      return data_queue.size();
    };


  private:
    float Average_vec(std::vector<Enctype> *data)
    {
    	float sum = 0;
    	for(int i = 0; i < data->size(); i++)
    		sum += data->at(i);

    	return SYSFREQ*ENC_UNI_LEN*sum/data->size();

    };
    /*
     * Tyre radius 0.16, circumference 1.00m,
     * 8000 pulse(2000*4)
     */
    //return data size
  };

}
#endif /*__encoder_H */
