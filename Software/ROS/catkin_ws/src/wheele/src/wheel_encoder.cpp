
#include "ros/ros.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <std_msgs/Float32.h>
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

#define Tsample_enc 0.1



int main(int argc, char **argv)
{

  std::ofstream myfile ("ticks.txt",std::ios::app |std::ios::out);
  std::chrono::time_point<std::chrono::system_clock> t_init,t_act,t_lastT;
  t_init = std::chrono::system_clock::now();
  t_act=t_lastT=t_init;  
  std::chrono::duration<double> dt,time;

/*
   std::vector<re_decoder> encoders;
   std::vector<int> GPIO_vect;

   n.param("/e1",e1 ,13);
*/
/*
  for(int i=1;i<=argc;i++){
    GPIO_vect.push_back(atoi(argv[i]));
  }

 for(int i=0;i<argc;i++){
   re_decoder tmp_enc = re_decoder(GPIO_vect[i]);
   encoders.push_back(tmp_enc);
  }
*/

  if (gpioInitialise() < 0) return 1;

  re_decoder enc_r1L=re_decoder(pin_e1L);
  re_decoder enc_r2L=re_decoder(pin_e2L);
  re_decoder enc_r3L=re_decoder(pin_e3L);
  re_decoder enc_r1R=re_decoder(pin_e1R);
  re_decoder enc_r2R=re_decoder(pin_e2R);
  re_decoder enc_r3R=re_decoder(pin_e3R);

  ros::init(argc, argv, "wheel_encoder");
  ros::NodeHandle n;

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




    t_act = std::chrono::system_clock::now();

    dt=t_act-t_lastT;
    time=(t_act-t_init);

    if (dt.count() > Tsample_enc){
      ROS_INFO_STREAM("Muestreo: " << dt.count()<<"\n" );
      myfile << time.count() <<" "<< data_vel_r1L.data <<" "<< data_vel_r2L.data <<" "<< data_vel_r3L.data <<" "<< data_vel_r1R.data <<" "<< data_vel_r2R.data <<" "<< data_vel_r3R.data << "\n"; 

      t_lastT=t_act;
   }

    ros::spinOnce();
    loop_rate.sleep();
  }

  /* If something dont work, close. */
  myfile.close();
  gpioTerminate();

return 0;
}
