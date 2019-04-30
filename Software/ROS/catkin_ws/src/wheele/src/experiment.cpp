#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <chrono>
#include <ctime>
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

  ros::Publisher pwm_pub = n.advertise<std_msgs::Float64>("pwm", 100);

  ros::Rate loop_rate(5); //10Hz

  std_msgs::Float64 pwm=-481;

  while (n.ok()) {
    pwm=pwm+1

    if (pwm<481) pwm_pub.publish(pwm);

    t_act = std::chrono::system_clock::now();
    dt=t_act-t_lastT;
    time=(t_act-t_init);
    if (dt.count() > Tsample_enc){
      ROS_INFO_STREAM("Muestreo: " << dt.count()<<"\n" );
      myfile << time.count() <<" "<< pwm <<"\n";
      t_lastT=t_act;
   }

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  myfile.close();
  return 0;}
