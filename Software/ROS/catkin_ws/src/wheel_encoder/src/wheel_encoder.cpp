
#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <std_msgs/Float32.h>
#include <encoder.hpp>
#include <pigpio.h>
#include <cstdlib>

/* Thread function */
void read_encoderTh(int inc)
{
  static int pos = 0;
  pos += inc;
  std::cout << "pos=" << pos << std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;

  int *GPIO_vect;
  re_decoder *encoders;

  GPIO_vect = (int*) malloc((argc-1)*sizeof(int));
  encoders= (re_decoder*) malloc((argc-1)*sizeof(re_decoder::re_decoder))

  ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("ticks_read", 1000);


  /*Data type conversion and encoder init*/
  for (int i=1;i<=argc;i++){
    sscanf(argv[i],"%i",&GPIO_vect[i-1]);
  }
  for(int i=0;i;i++){
    encoders[i]=re_decoder(GPIO_vect[i],encoCb) ;
  }

  //sleep(3000);
  ros::Rate loop_rate(10); //10Hz

  while (n.ok()) //can be ros::ok()
  {
    std_msgs::Float32 data_vel;

    data_vel.data=dec.send_vel();

    encoder_pub.publish(data_vel);

    ROS_INFO_STREAM("data sent in deg/sec: " << data_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  dec.re_cancel();
  gpioTerminate();

return 0;
}
