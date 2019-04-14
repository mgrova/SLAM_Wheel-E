#!/usr/bin/env python

# 03/2019 @MikeMakes
# Delivered as it is, without any warranty
# Serial communication with arduino using CmdMssenger
# Python library: https://github.com/zivlab/PyCmdMessenger
# Arduino library: https://github.com/thijse/Arduino-CmdMessenger

import rospy
import PyCmdMessenger
from geometry_msgs.msg import Twist


def send_vel(data): # cmd_vel topic (type Twist) callback
    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*0.025)/2 # How much velocity in each side we need for this movement
    right_vel = (linear_vel + (angular_vel*0.025)/2)

    cmd.send("change_vel",left_vel, right_vel) # Send velocites of left & right motors to arduino


if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["change_vel","ff"]]   # Send left & rights motors vel as 2 float arguments (ff)

    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, send_vel)
    rospy.spin()
