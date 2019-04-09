#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>

#define r_wheel 0.00325         // [m]
#define ticks_per_rev 2626
#define pi 3.14159265
#define lenght_btw_wheels 0.025 // [m]

std_msgs::Float32 ticks_x,ticks_y;

void ticksCb(const std_msgs::Float32::ConstPtr& tick_data)
{
  ticks_x.data=tick_data->data;
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "wheele_odom");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  double vx = 0.1;
  double vy = 0;
  double vth = 0.1;

  double v_left,v_right,omega_left,omega_right,deltaRight,deltaLeft;
  double _PreviousLeftEncoderCounts,_PreviousRightEncoderCounts;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Subscriber sub = n.subscribe("ticks_read", 1000, ticksCb);

  ros::Rate r(1.0); // 1Hz

  while (n.ok()) {

    ros::spinOnce(); // check for incoming messages
    current_time = ros::Time::now();
    double DistancePerCount = (pi * r_wheel) / ticks_per_rev;

    // extract the wheel velocities from the tick signals count
    //deltaLeft = ticks_x - _PreviousLeftEncoderCounts;
    //deltaRight = ticks_y - _PreviousRightEncoderCounts;

    omega_left = (deltaLeft * DistancePerCount) / (current_time - last_time).toSec();
    omega_right = (deltaRight * DistancePerCount) / (current_time - last_time).toSec();

    v_left = omega_left;   //*r_wheel
    v_right = omega_right; //*r_wheel

    vx = ((v_right + v_left) / 2) * 10; //*10 is a scale factor
    vy = 0;
    vth = ((v_right - v_left) / lenght_btw_wheels) * 10;

    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th)) * dt;
    double delta_y = (vx * sin(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

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
    //_PreviousLeftEncoderCounts = ticks_x;
    //_PreviousRightEncoderCounts = ticks_y;

    last_time = current_time;
  }
}
