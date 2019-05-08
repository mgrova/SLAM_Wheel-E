#!/usr/bin/env python

# 03/2019 @MikeMakes
# Delivered as it is, without any warranty
# Serial communication with arduino using CmdMssenger
# Python library: https://github.com/zivlab/PyCmdMessenger
# Arduino library: https://github.com/thijse/Arduino-CmdMessenger

import rospy
import PyCmdMessenger
from std_msgs.msg import Float64
from wheele.msg import pwm6

def send_pwm(pwm): # cmd_vel topic (type Twist) callback
    ##data=float(pwm.m1l)
    rospy.loginfo(pwm.m1l)
    rospy.loginfo(pwm.m1r)
    rospy.loginfo(pwm.m2l)
    rospy.loginfo(pwm.m2r)
    rospy.loginfo(pwm.m3l)
    rospy.loginfo(pwm.m3r)
    cmd.send("change_pwm",pwm.m1l,pwm.m1r,pwm.m2l,pwm.m2r,pwm.m3l,pwm.m3r) # Send pwm of left & right motors to arduino
    ##cmd.send("change_pwm",data,data,data,data,data,data)

if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["change_pwm","dddddd"]]   # Send pwm 2 motors (m1l, m1r, m2l, m2r, m3l, m3r,)
    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("pwm", pwm6, send_pwm)
    rospy.spin()
