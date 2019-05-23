
#include "ros/ros.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <geometry_msgs/Twist.h>

#include <encoder.hpp>
#include <pigpio.h>

#define pin_e1L 16
#define pin_e2L 20
#define pin_e3L 21

#define pin_e1R 13
#define pin_e2R 19
#define pin_e3R 26  

#define def_gpio_value {pin_e1L,pin_e2L,pin_e3L,pin_e1R,pin_e2R,pin_e3R}


bool rotL,rotR,bckwrd;
int re_decoder::no_encoders=0;


void fixVel(std_msgs::Float64MultiArray &msg);

void cbCmdVel(const geometry_msgs::TwistConstPtr& data){
      bckwrd=(data->linear.x<0);
      rotL=(data->angular.z>0);
      rotR=(data->angular.z<0);
    }


int main(int argc, char **argv)
{

  std::vector<int> GPIO_vect;
  std_msgs::Float64MultiArray encoder_msg;

  encoder_msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
  encoder_msg.layout.dim[0].label="encoders";
  encoder_msg.layout.dim[0].stride=1;



  if (gpioInitialise() < 0) return 1;

  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;

  n.param<std::vector<int>>("gpio",GPIO_vect,def_gpio_value);

  int no_encd=GPIO_vect.size();

  encoder_msg.data.resize(no_encd);


  re_decoder enc_r1L=re_decoder(GPIO_vect[0]);
  re_decoder enc_r2L=re_decoder(GPIO_vect[1]);
  re_decoder enc_r3L=re_decoder(GPIO_vect[2]);
  re_decoder enc_r1R=re_decoder(GPIO_vect[3]);
  re_decoder enc_r2R=re_decoder(GPIO_vect[4]);
  re_decoder enc_r3R=re_decoder(GPIO_vect[5]);


  ros::Publisher pub_encoder = n.advertise<std_msgs::Float64MultiArray>("encoders",100);
  ros::Subscriber sub_cmdVel = n.subscribe<geometry_msgs::Twist>("cmd_vel",10,cbCmdVel);
  ros::Rate loop_rate(50); //50Hz

  while (n.ok())
  {

    encoder_msg.data[0]=enc_r1L.getVel();
    encoder_msg.data[1]=enc_r2L.getVel();
    encoder_msg.data[2]=enc_r3L.getVel();

    encoder_msg.data[3]=enc_r1R.getVel();
    encoder_msg.data[4]=enc_r2R.getVel();
    encoder_msg.data[5]=enc_r3R.getVel();
    fixVel(encoder_msg);
    pub_encoder.publish(encoder_msg);

    ros::spinOnce();
    loop_rate.sleep();
  }

  gpioTerminate();

return 0;
}



void fixVel(std_msgs::Float64MultiArray &msg){
  ///Case robot is going backwards
  if(bckwrd){      
    for(int i=0;i<6;i++){
      msg.data[i]*=-1;
    }
  }
  ///Case robot is rotating c-clock wise
  if(rotL){      
    for(int i=0;i<3;i++){
      msg.data[i]*=-1;
    }
  }
  ///Case robot is rotating clock wise
  if(rotR){      
    for(int i=3;i<6;i++){
      msg.data[i]*=-1;
    }
  }
}