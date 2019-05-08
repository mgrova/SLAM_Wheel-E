
#include "ros/ros.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>

#include <encoder.hpp>
#include <pigpio.h>

#include <chrono>
#include <ctime>

#define pin_e1L 16
#define pin_e2L 20
#define pin_e3L 21

#define pin_e1R 13
#define pin_e2R 19
#define pin_e3R 26

#define def_gpio_value {pin_e1L,pin_e2L,pin_e3L,pin_e1R,pin_e2R,pin_e3R}

#define Tsample_enc 0.1



int main(int argc, char **argv)
{

  std::ofstream myfile ("ticks.txt",std::ios::app |std::ios::out);
  std::chrono::time_point<std::chrono::system_clock> t_init,t_act,t_lastT;
  t_init = std::chrono::system_clock::now();
<<<<<<< HEAD
  t_act=t_lastT=t_init;  
=======
  t_act=t_lastT=t_init;
  std::chrono::duration<double> dt,time;
>>>>>>> 498f023ae31f5d180d4713107b4dd6bc430759ee

  std::chrono::duration<double> dt,time;
  std::vector<int> GPIO_vect;
  std::cout <<"tamaño de GPIO_vect antes de inicializar: " << GPIO_vect.size() << '\n';
<<<<<<< HEAD
  std_msgs::Float32MultiArray encoder_msg;
=======
  std_msgs::Float64MultiArray encoder_msg;
  std_msgs::Float64MultiArray encoder_msg_test;
>>>>>>> 498f023ae31f5d180d4713107b4dd6bc430759ee

  re_decoder::no_encoders=0;
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


<<<<<<< HEAD
  ros::Publisher pub_encoder = n.advertise<std_msgs::Float32MultiArray>("encoders_ticks",100);
=======
  ros::Publisher pub_encoder = n.advertise<std_msgs::Float64MultiArray>("encoders_ticks",100);
  // ros::Publisher pub_2_encoder = n.advertise<std_msgs::Float32MultiArray>("encoder_test",100);
>>>>>>> 498f023ae31f5d180d4713107b4dd6bc430759ee

  ros::Rate loop_rate(50); //10Hz

  while (n.ok())
  {

    encoder_msg.data[0]=enc_r1L.getVel();
    encoder_msg.data[1]=enc_r2L.getVel();
    encoder_msg.data[2]=enc_r3L.getVel();

    encoder_msg.data[3]=enc_r1R.getVel();
    encoder_msg.data[4]=enc_r2R.getVel();
    encoder_msg.data[5]=enc_r3R.getVel();

    t_act = std::chrono::system_clock::now();

    dt=t_act-t_lastT;
    time=(t_act-t_init);

    if (dt.count() > Tsample_enc){
      ROS_INFO_STREAM("Muestreo: " << dt.count()<<"\n" );
      myfile << time.count()<< " ";
      for (int i=0;i<no_encd;i++){
        myfile << encoder_msg.data[i] << " ";
        if(i==no_encd-1) myfile << std::endl;
      }
      t_lastT=t_act;

   }
    pub_encoder.publish(encoder_msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  myfile.close();
  gpioTerminate();

return 0;
}
