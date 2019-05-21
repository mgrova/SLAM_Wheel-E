#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Float64MultiArray.h>
#include <wheele/pwm6.h>


#define ticks_per_rev 2626
#define pi 3.14159265
#define TwoPI 6.28318531

wheele::pwm6 ticks;

ros::Time current_time, last_time;

long _PreviousLeftEncoderCounts = 0;
long _PreviousRightEncoderCounts = 0;

double x = 0.0;
double y = 0.0;
double th = 0.0;

double deltaRight,deltaLeft; // nº of ticks since last update
double v_left,v_right,vx,vy,vth;
double vMean_L,vMean_R;

double r_wheel=0.0325;
double lenght_btw_wheels=0.25;

double dt;
double delta_distance; //distance moved by robot since last update
double delta_th;       //corresponging change in heading
double delta_x;        //corresponding change in x direction
double delta_y;        //corresponding change in y direction

double DistancePerCount = (pi * (2.0*r_wheel)) / ticks_per_rev;

void ticksCb(const std_msgs::Float64MultiArray::ConstPtr& ticks_read){

  current_time = ros::Time::now();

  /* Obtain encoders vel [rad/s] */
  ticks.m1l=ticks_read->data[0];
  ticks.m2l=ticks_read->data[1];
  ticks.m3l=ticks_read->data[2];
  ticks.m1r=ticks_read->data[3];
  ticks.m2r=ticks_read->data[4];
  ticks.m3r=ticks_read->data[5];

  vMean_L=ticks.m1l; //vMean_L=(ticks.m1l+ticks.m2l+ticks.m3l)/3.0;
  vMean_R=ticks.m1r; //vMean_R=(ticks.m1r+ticks.m2r+ticks.m2r)/3.0;
  /* Convert rad/s->m/s*/
  vMean_L=vMean_L*r_wheel;
  vMean_R=vMean_R*r_wheel;

  vx = ((vMean_R + vMean_L) / 2.0); // Can be necessary a scale factor due friccions
  vy = 0;
  /* To avoid errors in measure of th */
  if ((int(vMean_R) - int(vMean_L)) > 10 ){
    vth = ((vMean_R - vMean_L) / lenght_btw_wheels);
  }else{
    vth=0;
  }
  
  std::cout << "vmean R "<< vMean_R << "  vmean L "<< vMean_L << "\n";
  std::cout << "vx:  "<< vx << "  vth:  "<< vth <<"\n";

  /* Apply differential model */
  dt = (current_time - last_time).toSec();
  delta_x = (vx * cos(th)) * dt;
  delta_y = (vx * sin(th)) * dt;
  delta_th = vth * dt;

  /* Increase absolute robot position */
  x += delta_x;
  y += delta_y;
  th += delta_th;

  /* Check rotation limits */
  if (th > pi) {th -= TwoPI;}
  else if( th <= -pi) {th += TwoPI;}

  last_time = current_time;
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "wheele_odom");

  ros::NodeHandle n;

  ros::Subscriber ticks_sub = n.subscribe("encoders_ticks",10,ticksCb);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  
  tf::TransformBroadcaster odom_broadcaster;
  
  ros::Rate r(1.0); // 1Hz

  while (n.ok()) {

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    geometry_msgs::TransformStamped odom_trans;
    
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    // send the transform
    odom_broadcaster.sendTransform(odom_trans);

    // Odometry message
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    // set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    // set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    // publish the message
    odom_pub.publish(odom);

    ros::spinOnce(); // check for incoming messages
    r.sleep();


  }
}

