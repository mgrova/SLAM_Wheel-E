#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <wheele/pwm6.h>
#include <geometry_msgs/Twist.h>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

#include <dynamic_reconfigure/server.h>
#include <wheele/controlParamsConfig.h>

#define radius 0.035  // Radius of your wheels
#define enc_slits 22  // nº of slits in your encoders
#define pi 3.141592   // un arco de circunferencia entre su radio o algo asi
#define d_wheels 0.250    // distance between wheels

float kp=0.0,ki=0.0,kd=0.0; // pid gains

float p,d,sat_err_integrated,ek,ukns,ukreal,ueq=0;
//static float ek1_m1l, sat_err=0,i=0;
static float ek1_m1l=0,sat_err_m1l=0,i_m1l=0;
static float ek1_m1r=0,sat_err_m1r=0,i_m1r=0;
static float ek1_m2l=0,sat_err_m2l=0,i_m2l=0;
static float ek1_m2r=0,sat_err_m2r=0,i_m2r=0;
static float ek1_m3l=0,sat_err_m3l=0,i_m3l=0;
static float ek1_m3r=0,sat_err_m3r=0,i_m3r=0;

static float kp_m1L,kp_m2L,kp_m3L,kp_m1R,kp_m2R,kp_m3R;
static float ki_m1L,ki_m2L,ki_m3L,ki_m1R,ki_m2R,ki_m3R;


//kp_m1L=kp_m2L=kp_m3L=kp_m1R=kp_m2R=kp_m3R=0.0;
//ki_m1L=ki_m2L=ki_m3L=ki_m1R=ki_m2R=ki_m3R=0.0;

geometry_msgs::Twist ref_ms;
wheele::pwm6 pwm_msg;
std_msgs::Float64 error_m1L;
wheele::pwm6 ticks;

/* ROS CALLBACKS */
void refCb(const geometry_msgs::Twist::ConstPtr& ref){
  ref_ms.linear.x=ref->linear.x;
  ref_ms.angular.z=ref->angular.z;
}

void ticksCb(const std_msgs::Float64MultiArray::ConstPtr& ticks_read){
  ticks.m1l=ticks_read->data[0];
  ticks.m2l=ticks_read->data[1];
  ticks.m3l=ticks_read->data[2];
  ticks.m1r=ticks_read->data[3];
  ticks.m2r=ticks_read->data[4];
  ticks.m3r=ticks_read->data[5];

}

void dynCb(wheele::controlParamsConfig &config, uint32_t level)
{
  kp_m1L=config.Kp_m1L;
  ki_m1L=config.Ki_m1L;

  kp_m1R=config.Kp_m1R;
  ki_m1R=config.Ki_m1R;

  kp_m2L=config.Kp_m2L;
  ki_m2L=config.Ki_m2L;

  kp_m2R=config.Kp_m2R;
  ki_m2R=config.Ki_m2R;

  kp_m3L=config.Kp_m3L;
  ki_m3L=config.Ki_m3L;

  kp_m3R=config.Kp_m3R;
  ki_m3R=config.Ki_m3R;

  //std::cout << "Params control m1L->  Kp:" << kp_m1L <<" Ki:" << ki_m1L <<"\n";
  //std::cout << "Params control m2L->  Kp:" << kp_m2L <<" Ki:" << ki_m2L <<"\n";
  //std::cout << "Params control m3L->  Kp:" << kp_m3L <<" Ki:" << ki_m3L <<"\n";
  //std::cout << "Params control m1R->  Kp:" << kp_m1R <<" Ki:" << ki_m1R <<"\n";
  //std::cout << "Params control m2R->  Kp:" << kp_m2R <<" Ki:" << ki_m2R <<"\n";
  //std::cout << "Params control m3R->  Kp:" << kp_m3R <<" Ki:" << ki_m3R <<"\n";
}

/* FUNCTIONS */
float ms2ticks(float ms){
  float tickss;
  tickss=ms/radius; // [m/s] to [rad/s] (wheel radius = 0.035)
  tickss=tickss*(enc_slits/(2*pi)); // [rad/s] to [ticks/s] (encoders have 22 slits)
  return tickss;
}

/* Control Law */
float claw(int m, std::chrono::duration<double> dt, float ref, float out, float ek1, float sat_err, float i){ // Control law with conditional integration antiwindup
  sat_err_integrated=sat_err*dt.count();  // Integration of how much we satured
  ek=ref-out;  // Error = Desired - Actual  (output)
  switch(m) {
    case 1: kp=kp_m1L;
            ki=ki_m1L;
            kd=.0;
            break;
    case 2: kp=kp_m1R;
            ki=ki_m1R;
            kd=.0;
            break;
    case 3: kp=kp_m2L;
            ki=ki_m2L;
            kd=0.0;
            break;
    case 4: kp=kp_m2R;
            ki=ki_m2R;
            kd=.0;
            break;
    case 5: kp=kp_m3L;
            ki=ki_m3L;
            kd=.0;
            break;
    case 6: kp=kp_m3R;
            ki=ki_m3R;
            kd=.0;
            break;
  }
  //std::cout << "kp: " << kp << "ki: " << ki << "kd: " << kd << std::endl;
  p = kp*ek;
  i = ki*(i+ek*dt.count());
  d = kd*((ek-ek1)/dt.count());
  //std::cout << "p: " << p << "i: " << i << "d: " << d << std::endl;
  ukns=p+i+d+(sat_err_integrated/0.01)+ueq;  // PID + antiwindup + offset'

  if(ukns<-255) ukreal=-255;  // Saturation
  else if(ukns>255) ukreal=255;
  else ukreal=ukns;
  sat_err=ukreal-ukns;  // Saturation error
  ek1=ek; // Error update
  switch(m) {
    case 1: sat_err_m1l=sat_err;
            i_m1l=i;
            ek1_m1l=ek1;

            std::cout << "ref " << ref << "\n";
            std::cout << "out " << out << "\n";
            std::cout << "ek " << ek << "\n";
            std::cout << "p " << p << "\n";
            std::cout << "i " << i << "\n";
            std::cout << "ukns " << ukns << "\n";
            std::cout << "\n";

            break;
    case 2: sat_err_m1r=sat_err;
            i_m1r=i;
            ek1_m1l=ek1;
            break;
    case 3: sat_err_m2l=sat_err;
            i_m2l=i;
            ek1_m2l=ek1;
            break;
    case 4: sat_err_m2r=sat_err;
            i_m2r=i;
            ek1_m2r=ek1;
            break;
    case 5: sat_err_m3l=sat_err;
            i_m3l=i;
            ek1_m3l=ek1;
            break;
    case 6: sat_err_m3r=sat_err;
            i_m3r=i;
            ek1_m3r=ek1;
            break;
  }
  return ukreal;
}


int main(int argc, char **argv){

  std::chrono::time_point<std::chrono::system_clock> t_act,t_lastT;
  t_act=t_lastT;
  std::chrono::duration<double> dt;

  ros::init(argc, argv, "control");
  ros::NodeHandle n;
  ros::Subscriber ref_sub = n.subscribe("cmd_vel",10,refCb);
  ros::Subscriber ticks_sub = n.subscribe("encoders_ticks",10,ticksCb);
  ros::Publisher pwm_pub = n.advertise<wheele::pwm6>("pwm", 10);

  ros::Publisher pub_err = n.advertise<std_msgs::Float64>("error_m1L", 10);

  dynamic_reconfigure::Server<wheele::controlParamsConfig> srv;
  dynamic_reconfigure::Server<wheele::controlParamsConfig>::CallbackType f;
  f = boost::bind(&dynCb, _1, _2);
  srv.setCallback(f);

  ros::Rate loop_rate(50); //10Hz

while(n.ok()) {
  float lin, ang, left_ref_ms, right_ref_ms, left_ref_ticks, right_ref_ticks;
  lin=ref_ms.linear.x;
  ang=ref_ms.angular.z;
  left_ref_ms =lin - (ang*d_wheels)/2.0;
  right_ref_ms =lin + (ang*d_wheels)/2.0;
  left_ref_ticks = ms2ticks(left_ref_ms);
  right_ref_ticks = ms2ticks(right_ref_ms);


  t_act = std::chrono::system_clock::now();
  dt=t_act-t_lastT;
  t_lastT=t_act;

  pwm_msg.m1l=claw(1 ,dt, left_ref_ticks, ticks.m1l, ek1_m1l, sat_err_m1l, i_m1l);
//  ROS_INFO_STREAM("pwm m1l:  "<<pwm_msg.m1l <<"\n");
  pwm_msg.m1r=claw(2 ,dt, right_ref_ticks, ticks.m1r, ek1_m1r, sat_err_m1r, i_m1r);
 // ROS_INFO_STREAM("pwm m1r:  "<<pwm_msg.m1r <<"\n");
  pwm_msg.m2l=claw(3 ,dt, left_ref_ticks, ticks.m2l, ek1_m2l, sat_err_m2l, i_m2l);
  //ROS_INFO_STREAM("pwm m2l:  "<<pwm_msg.m2l <<"\n");
  //pwm_msg.m2r=claw(4 ,dt, right_ref_ticks, ticks.m2r, ek1_m2r, sat_err_m2r, i_m2r);
  pwm_msg.m2r=pwm_msg.m1r;
  //ROS_INFO_STREAM("pwm m2r:  "<<pwm_msg.m2r <<"\n");
  pwm_msg.m3l=claw(5 ,dt, left_ref_ticks, ticks.m3l, ek1_m3l, sat_err_m3l, i_m3l);
  pwm_msg.m3r=pwm_msg.m1r;
  //ROS_INFO_STREAM("pwm m3l:  "<<pwm_msg.m3l <<"\n");
  //pwm_msg.m3r=claw(6 ,dt, right_ref_ticks, ticks.m3r, ek1_m3r, sat_err_m3r, i_m3r);
  //ROS_INFO_STREAM("pwm m3r:  "<<pwm_msg.m3r <<"\n");
  error_m1L.data=ek1_m1l;
  pub_err.publish(error_m1L);
  pwm_pub.publish(pwm_msg);

  ros::spinOnce();
  loop_rate.sleep();
  }
  return 0;
}
