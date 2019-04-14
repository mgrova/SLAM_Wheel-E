
#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <std_msgs/Float32.h>
#include <encoder.hpp>
#include <pigpio.h>

#define pin_e1L 13
#define pin_e2L 19
#define pin_e3L 26
#define pin_e1R 16
#define pin_e2R 20
#define pin_e3R 21


int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;
/*
   std::vector<re_decoder> encoders;
   std::vector<int> GPIO_vect;

   n.param("/e1",e1 ,13);
*/
  if (gpioInitialise() < 0) return 1;
/*
  for(int i=1;i<=argc;i++){
    GPIO_vect.push_back(atoi(argv[i]));
  }

 for(int i=0;i<argc;i++){
   re_decoder tmp_enc = re_decoder(GPIO_vect[i]);
   encoders.push_back(tmp_enc);
  }
*/

  re_decoder enc_r1L=re_decoder(pin_e1L);
  re_decoder enc_r2L=re_decoder(pin_e2L);
  re_decoder enc_r3L=re_decoder(pin_e3L);
  re_decoder enc_r1R=re_decoder(pin_e1R);
  re_decoder enc_r2R=re_decoder(pin_e2R);
  re_decoder enc_r3R=re_decoder(pin_e3R);

  ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("ticks_read", 1000);
  ros::Rate loop_rate(10); //10Hz

  while (n.ok()) //can be ros::ok()
  {
    std_msgs::Float32 data_vel_r1L,data_vel_r2L,data_vel_r3L;
    std_msgs::Float32 data_vel_r1R,data_vel_r2R,data_vel_r3R;

    data_vel_r1L.data=enc_r1L.send_vel();
    data_vel_r2L.data=enc_r2L.send_vel();
    data_vel_r3L.data=enc_r3L.send_vel();

    data_vel_r1R.data=enc_r1R.send_vel();
    data_vel_r2R.data=enc_r2R.send_vel();
    data_vel_r3R.data=enc_r3R.send_vel();

   // PODER PUBLICAR ESTE VECTOR DE DATOS
   //    encoder_pub.publish(data_vel);

    ROS_INFO_STREAM("IZQUIEDA-> r1:" << data_vel_r1L << " r2:"<< data_vel_r2L << " r3:"<< data_vel_r3L <<"\n");
    ROS_INFO_STREAM("DERECHA-> r1:" << data_vel_r1R << " r2:"<< data_vel_r2R << " r3:"<< data_vel_r3R <<"\n");

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  gpioTerminate();

return 0;
}
