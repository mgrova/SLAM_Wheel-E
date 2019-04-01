
#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <std_msgs/Float32.h>
#include <encoder.hpp>
#include <pigpio.h>



void read_encoderTh(int inc)
{
  static int pos = 0;
  pos += inc;
  std::cout << "pos=" << pos << std::endl;
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;

  if (gpioInitialise() < 0) return 1;

  re_decoder dec(7, read_encoderTh);

  ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("encoder_read", 1000);

  //sleep(3000);
  ros::Rate loop_rate(10); //10Hz

  while (n.ok()) //can be ros::ok()
  {
    std_msgs::Float32 data_vel;

    data_vel.data=dec.send_vel();

    encoder_pub.publish(data_vel);

    ROS_INFO_STREAM("data send in deg/sec: " << data_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  dec.re_cancel();
  gpioTerminate();

return 0;
}
