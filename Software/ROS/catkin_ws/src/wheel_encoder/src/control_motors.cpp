#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

std_msgs::Float32 real_vel;
geometry_msgs::Twist ref_vel;

void velCb(const std_msgs::Float32::ConstPtr& measure)
{


}

void ref_velCb(const geometry_msgs::Twist::ConstPtr& ref)
{



}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "control_motors");
  ros::NodeHandle n;


  //ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("ticks_read", 1000);
  ros::Subscriber sub = n.subscribe("ticks_read", 50, velCb);
  ros::Subscriber sub_ref = n.subscribe("cmd_vel", 50, ref_velCb);


  ros::Rate loop_rate(1000); //1KHz

  while (n.ok()) //can be ros::ok()
  {

  }

return 0;
}
