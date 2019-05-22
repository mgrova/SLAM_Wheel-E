#!/usr/bin/env python

# 03/2019
# Delivered as it is, without any warranty
# Serial communication with arduino using CmdMssenger
# Python library: https://github.com/zivlab/PyCmdMessenger
# Arduino library: https://github.com/thijse/Arduino-CmdMessenger

import rospy
import PyCmdMessenger
from std_msgs.msg import Float32
from std_msgs.msg import Float32MultiArray
from wheele.msg import pwm6
from geometry_msgs.msg import Twist

def send_pwm(data): # cmd_vel topic (type Twist) callback
    
    # ref comes in m/s but v_wheels must be in rad/s

    d_wheels= 0.25 # [m]
    r_wheel=0.0325 # [m]

    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*d_wheels)/2 # How much velocity in each side we need for this movement
    right_vel = linear_vel + (angular_vel*d_wheels)/2

    # Convert linear to angular velocity [v=wr -> w=v/r]
    left_vel = left_vel / r_wheel 
    right_vel = right_vel / r_wheel

    cmd.send("change_pwm",left_vel, right_vel,left_vel, right_vel,left_vel, 0) # Send velocites of left & right motors to arduino

if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM1",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["change_pwm","dddddd"]] # Send pwm 2 motors (m1l, m1r, m2l, m2r, m3l, m3r,)

    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, send_pwm)
    rospy.spin()
