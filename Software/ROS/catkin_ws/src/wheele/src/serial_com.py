#!/usr/bin/env python

# 03/2019 @MikeMakes
# Delivered as it is, without any warranty
# Serial communication with arduino using CmdMssenger
# Python library: https://github.com/zivlab/PyCmdMessenger
# Arduino library: https://github.com/thijse/Arduino-CmdMessenger

import rospy
import PyCmdMessenger
from std_msgs.msg import Float64

def send_pwm(data): # cmd_vel topic (type Twist) callback
    data = data.data
    #linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    #angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    #left_vel = linear_vel - (angular_vel*0.025)/2 # How much velocity in each side we need for this movement
    #right_vel = (linear_vel + (angular_vel*0.025)/2)
    if data > 255:
        data = 255
    elif data < -255:
        data = -255

    cmd.send("change_pwm",data,data,data,data,data,data) # Send velocites of left & right motors to arduino


if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["change_pwm","ffffff"]]   # Send pwm 2 motors (m1l, m1r, m2l, m2r, m3l, m3r,)
    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("pwm", Float64, send_pwm)
    rospy.spin()
