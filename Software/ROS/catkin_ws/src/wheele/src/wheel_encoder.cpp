
#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <std_msgs/Float32.h>
#include <encoder.hpp>
#include <pigpio.h>




int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;
  std::vector<re_decoder> encoders;
  std::vector<int> GPIO_vect;

  // n.param("/e1",e1 ,13);

  if (gpioInitialise() < 0) return 1;

  for(int i=1;i<=argc;i++){
    GPIO_vect.push_back(atoi(argv[i]));
  }

  for(int i=0;i<argc;i++){
    re_decoder tmp_enc = re_decoder(GPIO_vect[i]);
    encoders.push_back(tmp_enc);
  }

  ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("ticks_read", 1000);
  ros::Rate loop_rate(10); //10Hz

  while (n.ok()) //can be ros::ok()
  {
    std_msgs::Float32 data_vel;

    data_vel.data=encoders[0].send_vel();

    encoder_pub.publish(data_vel);

    ROS_INFO_STREAM("data send in deg/sec: " << data_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  gpioTerminate();

return 0;
}
