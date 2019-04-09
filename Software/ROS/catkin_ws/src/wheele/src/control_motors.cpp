#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

std_msgs::Float32 real_vel;
geometry_msgs::Twist ref_vel;

void velCb(const std_msgs::Float32::ConstPtr& measure)
{
  real_vel.data=measure->data;

}

void ref_velCb(const geometry_msgs::Twist::ConstPtr& ref)
{
  ref_vel.linear=ref->linear;
  ref_vel.angular=ref->angular;
}

int main(int argc, char **argv)
{
  float lin_x_ref,ang_z_ref;
  ros::init(argc, argv, "control_motors");
  ros::NodeHandle n;

  /*  ***** LO DE LOS TIPOS DE CONTROLADORES *****
   * LOW-LEVEL CONTROL  -> SE ASEGURA QUE SIGA LA REFERENCIA DE REV/SEG DE LA RUEDA (control en PWM)
   * MID-LEVEL CONTROL  -> CONTROL DE REFERENCIA CON CMD_VEL Y LA ODOMETRIA DEL ROBOT (control en vel lin/ang)
   * HIGH-LEVEL CONTROL -> PATH PLANNING. GENERA MENSAJES TIPO CMD_VEL.
   */

  //ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("ticks_read", 1000);
  ros::Subscriber sub = n.subscribe("ticks_read", 50, velCb);
  ros::Subscriber sub_ref = n.subscribe("cmd_vel", 50, ref_velCb);


  ros::Rate loop_rate(1000); //1KHz

  while (n.ok()) //can be ros::ok()
  {
    lin_x_ref=ref_vel.linear.x;
    ang_z_ref=ref_vel.angular.z;


  }

return 0;
}
