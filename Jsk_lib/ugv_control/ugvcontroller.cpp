/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <rosnode.h>

#define SetRMotor(duty) htim4.Instance->CCR1 = NEU_DUTY - (duty - NEU_DUTY)
#define SetLMotor(duty) htim4.Instance->CCR2 = duty
//radio controll flag
extern uint8_t radio_flag;

void RosNode::Ros_Pid_controller(encoder::ENCODER_ *enc_l,
		encoder::ENCODER_ *enc_r,
		IMU *imu)
{
	//get the linear err
	float err_linear_l = aim_linear_spd - enc_l->ave_velo;
	float err_linear_r = aim_linear_spd - enc_r->ave_velo;
	float d_err_linear_l = enc_l->ave_acc;
	float d_err_linear_r = enc_r->ave_acc;
	//get the angular err
	float err_angular = aim_angular_spd - imu->ave_gyro.z;
	float d_err_angular = imu->ave_gyroacc.z;

	//test  using the cmd_vel_msg.linear.y as Kp using angular.y as Kd
	LMotor_duty += (int)(Kp_l*err_linear_l - Kd_l*d_err_linear_l);
	RMotor_duty += (int)(Kp_l*err_linear_r - Kd_l*d_err_linear_r);
	//turning left imu output positive..  R forward L backward..
    LMotor_duty -= (int)(Kp*err_angular - Kd*d_err_angular);
    RMotor_duty += (int)(Kp*err_angular - Kd*d_err_angular);

	// next we need to control the angular....
    odom_msg.angular.x = LMotor_duty;
    odom_msg.angular.y = RMotor_duty;
	this->radioflag_msg.data = radio_flag;
	/* if automatic control */
	if(!radio_flag)
	{
		LMotor_duty = LMotor_duty>MAX_DUTY?MAX_DUTY:LMotor_duty;
		LMotor_duty = LMotor_duty<MIN_DUTY?MIN_DUTY:LMotor_duty;
		RMotor_duty = RMotor_duty>MAX_DUTY?MAX_DUTY:RMotor_duty;
		RMotor_duty = RMotor_duty<MIN_DUTY?MIN_DUTY:RMotor_duty;
		SetLMotor(LMotor_duty);
		SetRMotor(RMotor_duty);
	}
	else // or manual control, the control will not accumulate..
	{
		LMotor_duty = NEU_DUTY;
		RMotor_duty = NEU_DUTY;
	}

}
