#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <wheele/pwm6.h>
#include <geometry_msgs/Twist.h>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

#define Ts_control 0.2


std_msgs::Float32 real_vel_r2L,real_vel_r2R;
std_msgs::Float32 real_velR,real_velL;
geometry_msgs::Twist ref_vel,sc_vel;


void velCb_r2L(const std_msgs::Float32::ConstPtr& measure2){
  real_vel_r2L.data=measure2->data;
}
void velCb_r2R(const std_msgs::Float32::ConstPtr& measure5){
  real_vel_r2R.data=measure5->data;

}


void ref_velCb(const geometry_msgs::Twist::ConstPtr& ref){
  ref_vel.linear.x=ref->linear.x;
  ref_vel.angular.z=ref->angular.z;
}

int main(int argc, char **argv){
  float lin_x_ref,ang_z_ref,velL_ref,velR_ref,sc_vL,sc_vR,sc_lin_x,sc_ang_z;
  static float err_vR,Int_e_vR,err_vL,Int_e_vL;
  float Kp=2.05;
  float Ti=0.5;

  std::chrono::time_point<std::chrono::system_clock> t_init,t_act,t_lastC;
  t_init = std::chrono::system_clock::now();
  t_act=t_lastC=t_init;
  std::chrono::duration<double> dt,time;


  ros::init(argc, argv, "control_motors");
  ros::NodeHandle n;

  ros::Publisher motorVel_pub = n.advertise<geometry_msgs::Twist>("motor_vel", 50);

  ros::Subscriber sub_r2L = n.subscribe("ticks_read_r2L", 100, velCb_r2L); // rad/s
  ros::Subscriber sub_r2R = n.subscribe("ticks_read_r2R", 100, velCb_r2R); // rad/s
  ros::Subscriber sub_ref = n.subscribe("cmd_vel", 50, ref_velCb);

  ros::Rate loop_rate(50); //10Hz

  while (n.ok()) {//can be ros::ok()
    lin_x_ref=ref_vel.linear.x;
    ang_z_ref=ref_vel.angular.z;

    //ROS_INFO_STREAM("ref "<< lin_x_ref <<"\n");
    /* Se desmonta el mensaje, se controla en la relacion PWM-rad/s y se reconstruye el twist */
    velL_ref =lin_x_ref - (ang_z_ref*0.025)/2.0;
    velR_ref =lin_x_ref + (ang_z_ref*0.025)/2.0;

    t_act = std::chrono::system_clock::now();

    dt=t_act-t_lastC;
   // ROS_INFO_STREAM("dt "<< dt.count()<<"\n");
    ROS_INFO_STREAM("error  "<<err_vR <<"\n");
    if (dt.count() > Ts_control){
	real_velR.data=real_vel_r2R.data;
  	real_velL.data=real_vel_r2L.data;

	/*Apply control ONLY for 1 motor in the right! */

	err_vR=velR_ref-real_velR.data;

	Int_e_vR += err_vR*dt.count();

	sc_vR=Kp*(err_vR + Int_e_vR/Ti);

        err_vL=velL_ref-real_velL.data;
	Int_e_vL += err_vL*dt.count();

	sc_vL=Kp*(err_vL + Int_e_vL/Ti);

        t_lastC=t_act;
  }

  sc_lin_x=(sc_vR+sc_vL)/2.0;
  sc_ang_z=0;//=(sc_vR+sc_vL)/0.025;

  /* Rebuild twist msg */
  if (sc_lin_x > 250.0) sc_lin_x=250.0;
  else if (sc_lin_x < -250.0) sc_lin_x=-250.0;
  sc_vel.linear.x=sc_lin_x;
  sc_vel.linear.y=0.0;
  sc_vel.linear.z=0.0;
  sc_vel.angular.x=0.0;
  sc_vel.angular.y=0.0;
  sc_vel.angular.z=sc_ang_z;

  motorVel_pub.publish(sc_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
