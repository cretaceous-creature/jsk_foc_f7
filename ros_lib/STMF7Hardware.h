/* 
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 1) DMA-TX initalization problem
 * 2) DMA-M0AR registration problem => array type[n], not pointer address.
 * 3) DMA-ring_beffur problem: use idle_flag correctly to process the buffer continuously
 */

#ifndef ROS_STMF7_HARDWARE_H_
#define ROS_STMF7_HARDWARE_H_

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_dma.h"

template <typename T,  int SIZE>
class RingBuffer
{
public:
  RingBuffer()
  {
    byte_in_progress_ = 0;
    byte_to_add_ = 0;
    buffer_length_ = (uint16_t)SIZE;
  }
  ~RingBuffer(){  }

  bool pop(T& pop_value)
  {
    if (byte_in_progress_ != byte_to_add_)
      {
        pop_value =  buf_[byte_in_progress_];

        byte_in_progress_++;
        if (byte_in_progress_ == buffer_length_)
          byte_in_progress_ = 0;

        return true;
      }
    return false;
  }

  bool push(T new_value)
  {
    // the process node should have higher priority than the rx it callback
#if 0
    if ((byte_in_progress_ == (byte_to_add_ + 1)) || ( (byte_to_add_ == (buffer_length_ - 1) )&& (byte_in_progress_ == 0)) ) return false;
#endif

    buf_[byte_to_add_] = new_value;

    byte_to_add_++;

    if (byte_to_add_ == buffer_length_)
      {
        byte_to_add_ = 0;
      }

    return true;
  }

  uint16_t length()
  {
    if(byte_to_add_ - byte_in_progress_ >= 0)
      return (byte_to_add_ - byte_in_progress_);
    else 
      return (byte_to_add_ - (buffer_length_ - byte_in_progress_));
  }

private:
  T buf_[SIZE];
  int16_t byte_in_progress_, byte_to_add_;
  uint16_t buffer_length_;
};


template<class Hardware, int RX_SIZE, int RX_BURST_SIZE>
class RxBuffer
{
public:
  RxBuffer(Hardware *huart):huart_(huart)
  {
    ring_buf_ = new RingBuffer<uint8_t, RX_SIZE>();
    //RX
    HAL_UART_Receive_DMA(huart_, rx_value_, RX_BURST_SIZE); //1byte receive protocal
    huart_->hdmarx->XferCpltCallback = ReceiveCplt;
    __HAL_UART_DISABLE_IT(huart_, UART_IT_RXNE);
  }


  void add(uint8_t new_value)
  {
    ring_buf_->push(new_value);
  }

  bool add()
  {
    if(!ring_buf_->push(rx_value_)) 
      return false;

    return true;
  }

  int read()
  {
    if(!available()) return -1;

    uint8_t r_data;
    ring_buf_->pop(r_data);
    return  r_data;
  }

  bool available() { return ring_buf_->length(); }

  inline uint8_t& rxValue() { return rx_value_; }
  inline RingBuffer<uint8_t, RX_SIZE>* ringBuffer() { return ring_buf_; }

  static void ReceiveCplt(DMA_HandleTypeDef *hdma)
  {
    Hardware* huart = ( Hardware* )(hdma)->Parent;

    /* DMA Normal mode */
    if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
      {
        huart->RxXferCount = 0;

        /* Disable the DMA transfer for the receiver request by setting the DMAR bit 
           in the UART CR3 register */
        huart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAR);

        /* Check if a transmit Process is ongoing or not */
        if(huart->gState == HAL_UART_STATE_BUSY_TX_RX)
          huart->gState = HAL_UART_STATE_BUSY_TX;
        else
          huart->gState = HAL_UART_STATE_READY;
      }
    //sepecial process
for(int i = 0; i < RX_BURST_SIZE; i++)
    ring_buf_->push(rx_value_[i]);
  }

  static RingBuffer<uint8_t, RX_SIZE>* ring_buf_; //global 
  static uint8_t rx_value_[RX_BURST_SIZE]; //global

private:
  Hardware *huart_;
};


template<int BUFFER_LENGTH>
struct TxBufferUnit{
  uint8_t tx_data_[BUFFER_LENGTH];//this means each txdata packet should be shorter than 255
  uint8_t tx_len_;
} ;



template<class Hardware, int TX_SIZE, int BUFFER_LENGTH>
class TxBuffer
{
public:
  TxBuffer(Hardware *huart): huart_(huart)
  {
    idle_flag_ = true;
    subscript_in_progress_ = 0;
    subscript_to_add_ = 0;

    for(int i = 0; i < TX_SIZE; i++) 
      {
        tx_buffer_unit_[i].tx_len_ = 1;
        for(int j = 0; j < BUFFER_LENGTH; j++)
          tx_buffer_unit_[i].tx_data_[j]  = 1;
      }

    //TX
    HAL_UART_Transmit_DMA(huart_, (uint8_t*)tx_buffer_unit_[0].tx_data_, tx_buffer_unit_[0].tx_len_);

    huart_->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);
    huart_->hdmatx->XferCpltCallback = TransmitCplt;
  }

  ~TxBuffer(){}


  static void TransmitCplt(DMA_HandleTypeDef *hdma)
  {
    Hardware* huart = ( Hardware* )(hdma)->Parent;
    /* DMA Normal mode*/
    if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
      {
        huart->TxXferCount = 0;

        /* Disable the DMA transfer for transmit request by setting the DMAT bit
           in the UART CR3 register */
        huart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);
 /* Enable the UART Transmit Complete Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
      
      }
    /* DMA Circular mode */
    else
      {
        /* Disable the peripheral */
        huart->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAT);

        if(!idle_flag_)
          {
            subscript_in_progress_++;

            if (subscript_in_progress_ == TX_SIZE)
                subscript_in_progress_ = 0;

            if (subscript_in_progress_ != subscript_to_add_)
              {
                __HAL_DMA_DISABLE(huart->hdmatx);
                uint8_t* tmp8 = tx_buffer_unit_[subscript_in_progress_].tx_data_;
                uint32_t * tmp32 = (uint32_t*)&tmp8;
                huart->hdmatx->Instance->NDTR = (uint32_t)tx_buffer_unit_[subscript_in_progress_].tx_len_;

                huart->hdmatx->Instance->M0AR = *(uint32_t*)tmp32;
                /* Enable USARTy DMA TX Channel */
                huart->Instance->CR3 |= USART_CR3_DMAT; //enable dma request in hsuart side
                __HAL_DMA_ENABLE(huart->hdmatx);
              }	
            else
              {
                idle_flag_ = true;
              }

          }
        __HAL_DMA_CLEAR_FLAG(huart->hdmatx, __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmatx));
      }
  }

  void write(uint8_t * new_data, uint8_t new_size)
  {
    //if (subscript_in_progress_ == subscript_to_add_) idle_flag_= false;

    //if subscript comes around and get to one in progress_, then wait.
    if (subscript_in_progress_ == subscript_to_add_ + 1 || ( subscript_to_add_ == TX_SIZE - 1 && subscript_in_progress_ == 0) )
      {
        //TODO: address the overflow
		while(subscript_in_progress_ == subscript_to_add_ + 1 || ( subscript_to_add_ == TX_SIZE - 1 && subscript_in_progress_ == 0)){}
      //  return;
      }


    tx_buffer_unit_[subscript_to_add_].tx_len_ = new_size;
    memcpy(tx_buffer_unit_[subscript_to_add_].tx_data_, new_data, new_size);

    //speed slows down?
    //memcpy(tx_data_[subscript_to_add_], new_data, new_size);

    subscript_to_add_++;

    //if subscript reaches end make to go back to front
    if (subscript_to_add_ == TX_SIZE)
      subscript_to_add_ = 0;

    // enable and start DMA transfer
    if (idle_flag_ )
      {
        // check the needs to enable and start DMA transfer
        if ((subscript_in_progress_ == (subscript_to_add_-1)) || (subscript_in_progress_ == TX_SIZE -1 && subscript_to_add_ == 0)) idle_flag_= false;

        huart_->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAT);
        __HAL_DMA_DISABLE(huart_->hdmatx);
        uint8_t* tmp8 = tx_buffer_unit_[subscript_in_progress_].tx_data_;
        uint32_t *tmp32 = (uint32_t*)&tmp8;
        huart_->hdmatx->Instance->NDTR = (uint32_t)tx_buffer_unit_[subscript_in_progress_].tx_len_;

        huart_->hdmatx->Instance->M0AR = *(uint32_t*)tmp32;
        /* Enable USARTy DMA TX Channel */
        huart_->Instance->CR3 |= USART_CR3_DMAT;
        __HAL_DMA_ENABLE(huart_->hdmatx);
        __HAL_DMA_CLEAR_FLAG(huart_->hdmatx, __HAL_DMA_GET_TC_FLAG_INDEX(huart_->hdmatx));

      }
  }

  uint8_t subscriptInProgress(){return subscript_in_progress_;}
  uint8_t subscriptToAdd(){return subscript_to_add_;}
  bool idleFlag(){return idle_flag_;}

 uint8_t  getCurrentTransmitBufferLen()
{
return tx_buffer_unit_[subscript_in_progress_].tx_len_;
}

uint8_t*  getCurrentTransmitBufferP()
{
return tx_buffer_unit_[subscript_in_progress_].tx_data_;
}

  static  struct TxBufferUnit<BUFFER_LENGTH> tx_buffer_unit_[TX_SIZE];
  static uint8_t subscript_in_progress_;
  static uint8_t subscript_to_add_;
  static bool idle_flag_;


private:
  Hardware *huart_;
};

#define RX_BURST_MODE 8

template<class Hardware,
         int MAX_TX_BUFFER=50,
         int MAX_TX_BUFFER_LENGTH=250,
         int MAX_RX_BUFFER=400,
			int RX_BURST_SIZE=RX_BURST_MODE>
class UartDriver{
public:

  UartDriver(Hardware *huart): huart_(huart)
  {
    rx_ = new RxBuffer<Hardware, MAX_RX_BUFFER, RX_BURST_SIZE>(huart_);
    tx_ = new TxBuffer<Hardware, MAX_TX_BUFFER, MAX_TX_BUFFER_LENGTH>(huart_);
  }
  ~UartDriver(){}

  void begin(uint32_t baud_rate)
  {
    huart_->Init.BaudRate = baud_rate;
    HAL_UART_Init(huart_);
  }

  void write(uint8_t data_byte)
  {
    write(&data_byte, 1);
  }

  void write(uint8_t * data_byte, uint8_t size)
  {
    tx_->write(data_byte, size);
  }


  int read()
  {
    return rx_->read();
  }

  Hardware* getHuart()
  {
    return huart_;
  }

  TxBuffer<Hardware, MAX_TX_BUFFER, MAX_TX_BUFFER_LENGTH>* getTx() 
 {
	return tx_;
 }

private:
  Hardware *huart_;

  /* TX */
  RxBuffer<Hardware, MAX_RX_BUFFER, RX_BURST_SIZE>* rx_;
  /* RX */
  TxBuffer<Hardware, MAX_TX_BUFFER, MAX_TX_BUFFER_LENGTH>* tx_;
};


template<class Hardware, int TX_SIZE, int BUFFER_LENGTH>
struct TxBufferUnit<BUFFER_LENGTH> TxBuffer<Hardware, TX_SIZE, BUFFER_LENGTH>::tx_buffer_unit_[TX_SIZE];

template<class Hardware, int TX_SIZE, int BUFFER_LENGTH>
uint8_t TxBuffer<Hardware, TX_SIZE, BUFFER_LENGTH>::subscript_in_progress_;

template<class Hardware, int TX_SIZE, int BUFFER_LENGTH>
uint8_t TxBuffer<Hardware, TX_SIZE, BUFFER_LENGTH>::subscript_to_add_;

template<class Hardware, int TX_SIZE, int BUFFER_LENGTH>
bool TxBuffer<Hardware, TX_SIZE, BUFFER_LENGTH>::idle_flag_;

template<class Hardware, int RX_SIZE, int RX_BURST_SIZE>
uint8_t RxBuffer<Hardware, RX_SIZE, RX_BURST_SIZE>::rx_value_[RX_BURST_SIZE];

template<class Hardware, int RX_SIZE, int RX_BURST_SIZE>
RingBuffer<uint8_t, RX_SIZE>*  RxBuffer<Hardware, RX_SIZE,RX_BURST_SIZE>::ring_buf_;


class STMF7Hardware {
public:
  typedef UART_HandleTypeDef serial_class;


  STMF7Hardware(){ // hard coding
    baud_ = 921600;
  }

  STMF7Hardware(serial_class* io, uint32_t baud= 921600){
    iostream_ = new UartDriver<UART_HandleTypeDef>(io);	
    baud_ = baud;
  }


  void setBaud(long baud){
    this->baud_= baud;
  }

  int getBaud(){return baud_;}

  void init(serial_class* huart){
    iostream_ = new UartDriver<serial_class>(huart);
    iostream_->begin(baud_);
  }

  void init(){
    iostream_ = NULL;
  }

  int read()
  {
    return iostream_->read();
  };

  void write(uint8_t* data, int length){
    iostream_->write(data, length);
  }

  uint32_t time(){return HAL_GetTick();}

UartDriver<serial_class>* getUartDriver() {return  iostream_;}

protected:
  serial_class*  io_;
  UartDriver<serial_class>* iostream_;
  uint32_t baud_;
};




#endif
