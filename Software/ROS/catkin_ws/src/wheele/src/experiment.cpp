#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <wheele/pwm6.h>

#include <chrono>
#include <ctime>

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>

#define Tsample_enc 0.1

int main(int argc, char **argv) {
  std::ofstream myfile ("pwm.log",std::ios::app |std::ios::out);
  std::chrono::time_point<std::chrono::system_clock> t_init,t_act,t_lastT;
  t_init = std::chrono::system_clock::now();
  t_act=t_lastT=t_init;
  std::chrono::duration<double> dt,time;

  ros::init(argc, argv, "experiment");
  ros::NodeHandle n;

  ros::Publisher pwm_pub = n.advertise<wheele::pwm6>("pwm", 100);

  ros::Rate loop_rate(5); //10Hz

  std_msgs::Float64 pwm;
  pwm.data=-481.0;
  wheele::pwm6 pwm_msg;

  while (n.ok()) {
    pwm_msg.m1l=pwm.data;
    pwm_msg.m1r=pwm.data;
    pwm_msg.m2l=pwm.data;
    pwm_msg.m2r=pwm.data;
    pwm_msg.m3l=pwm.data;
    pwm_msg.m3r=pwm.data;

    if (pwm.data<481) pwm_pub.publish(pwm_msg);

    t_act = std::chrono::system_clock::now();
    dt=t_act-t_lastT;
    time=(t_act-t_init);
    if (dt.count() > Tsample_enc){
      ROS_INFO_STREAM("pwm: " << pwm.data <<"\n" );
      myfile << time.count() <<" "<< pwm.data <<"\n";
      t_lastT=t_act;

    pwm.data++;
   }

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  myfile.close();
  return 0;}
