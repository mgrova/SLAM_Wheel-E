#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <wheele/pwm6.h>
#include <geometry_msgs/Twist.h>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

#define radius 0.035
#define enc_slits 22
#define pi 3.141592
geometry_msgs::Twist ref_ms;
//std_msgs::float64 ref_ticks;
wheele::pwm6 pwm_msg;
float ticks;
float kp=0.0,ki=0.0,kd=0.0;

void get_ref(const geometry_msgs::Twist::ConstPtr& ref){
  ref_ms.linear.x=ref->linear.x;
  ref_ms.angular.z=ref->angular.z;
}

void get_ticks(const std_msgs::Float64MultiArray::ConstPtr& ticks_read){
  ticks=ticks_read->data[0];
}

void get_pid(const std_msgs::Float64MultiArray::ConstPtr& pid){
  kp=pid->data[0];
  ki=pid->data[1];
  kd=pid->data[2];
}

float ms2ticks(float ms){
  float tickss;
  tickss=ms/radius; // [m/s] to [rad/s] (wheel radius = 0.035)
  tickss=tickss*(enc_slits/2*pi); // [rad/s] to [ticks/s] (encoders have 22 slits)
  return tickss;
}

int main(int argc, char **argv){
  //std::ofstream myfile ("pwm.log",std::ios::app |std::ios::out);
  std::chrono::time_point<std::chrono::system_clock> t_init,t_act,t_lastT;
  t_init = std::chrono::system_clock::now();
  t_act=t_lastT=t_init;
  std::chrono::duration<double> dt;

  ros::init(argc, argv, "control");
  ros::NodeHandle n;
  ros::Subscriber ref_sub = n.subscribe("cmd_vel",100,get_ref);
  ros::Subscriber ticks_sub = n.subscribe("encoders_ticks",100,get_ticks);
  ros::Publisher pwm_pub = n.advertise<wheele::pwm6>("pwm", 100);

  ros::Subscriber pid_sub = n.subscribe("pid",10,get_pid);

  ros::Rate loop_rate(10); //10Hz

  static float sat_err=0,uk1=0,i=0;
  static float ukns,ukreal,sat_err_integrated,ek,ek1;
  float p,d,ueq=0;

while(n.ok()) {
  float lin, ang, left_ref_ms, right_ref_ms, left_ref_ticks, right_ref_ticks;
  lin=ref_ms.linear.x;
  ang=ref_ms.angular.z;
  left_ref_ms =lin - (ang*radius)/2.0;
  right_ref_ms =lin + (ang*radius)/2.0;
  left_ref_ticks = ms2ticks(left_ref_ms);
  right_ref_ticks = ms2ticks(right_ref_ms);

  t_act = std::chrono::system_clock::now();
  dt=t_act-t_lastT;

  ROS_INFO_STREAM("dt:  "<<dt.count() <<"\n");
  ROS_INFO_STREAM("kp:  "<<kp <<"\n");
  ROS_INFO_STREAM("ki:  "<<ki <<"\n");
  ROS_INFO_STREAM("kd:  "<<kd <<"\n");

  sat_err_integrated=sat_err*dt.count();
  ek=left_ref_ticks-ticks;

  p = kp*ek;
  i = ki*(i+ek*dt.count());
  d = kd*((ek-ek1)/dt.count());
  ukns=p+i+d+(sat_err_integrated/0.1)+ueq;
  ROS_INFO_STREAM("ukns:  "<<ukns <<"\n");
  if(ukns<-255) ukreal=-255;
  else if(ukns>255) ukreal=255;
  else ukreal=ukns;
  sat_err=ukreal-ukns;
  ek1=ek;

  ROS_INFO_STREAM("ukreal:  "<<ukreal <<"\n");

  pwm_msg.m1l=ukreal;
  //pwm_msg.m1r=ukreal;
  //pwm_msg.m2l=ukreal;
  //pwm_msg.m2r=ukreal;
  //pwm_msg.m3l=ukreal;
  //pwm_msg.m3r=ukreal;
  pwm_pub.publish(pwm_msg);

  ros::spinOnce();
  loop_rate.sleep();
  t_lastT=t_act;
  }
  return 0;
}
