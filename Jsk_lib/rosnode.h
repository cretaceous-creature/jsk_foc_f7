#ifndef __ROS_NODE_H_
#define __ROS_NODE_H_

/* ros */
#include <ros.h>
/* inlcude ros message types*/
#include <std_msgs/Int8.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
/* inlcude ros related class */
//#include <examples/class.h>
#include <sensors/encoder/encoder.h>
#include <sensors/imu/imu_mpu9250.h>
//define the duty

class RosNode
{
public:
	RosNode(ros::NodeHandle* nh)
{
		/* ros node initialize */
		nh_ = nh;

		/* ros publisher initialize */
//		radioflag_pub_ = new ros::Publisher("radioflag",&radioflag_msg);
//		odom_pub_ = new ros::Publisher("odometry/raw",&odom_msg);
//		//publish the msgs
//		nh_->advertise(*radioflag_pub_);
//		nh_->advertise(*odom_pub_);

		/* ros subscriber initialize */


};
	~RosNode(){};
	/* ros controller */
	/* ros node handle */
	ros::NodeHandle  *nh_;
	/* ros publisher */
	ros::Publisher* radioflag_pub_; //radioflag_pub_
	ros::Publisher* odom_pub_;  //odometry pub: twist message
	/*  ros msgs */
	std_msgs::Int8 radioflag_msg;
	geometry_msgs::Twist odom_msg;

private:
	/* aim linear and angular speed */
	float aim_linear_spd = 0;
	float aim_angular_spd = 0;
	//uint16_t LMotor_duty = NEU_DUTY;
	//uint16_t RMotor_duty = NEU_DUTY;
#define Kp_l 20
#define Kd_l 5000
	float Kp = 20;
	float Kd = 5000;
	/* ros subscibers */
	ros::Subscriber2<geometry_msgs::Twist, RosNode>* cmd_vel_sub_;
	/* ros call back function */
	void Cmd_Vel_Callback(const geometry_msgs::Twist& cmd_vel_msg);

};
#endif

