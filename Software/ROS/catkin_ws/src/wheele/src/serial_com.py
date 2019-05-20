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
    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*0.25)/2 # How much velocity in each side we need for this movement
    right_vel = linear_vel + (angular_vel*0.25)/2

    left_vel = left_vel / 0.035;
    right_vel = right_vel / 0.035;

    cmd.send("receive_ref",left_vel,right_vel) # Send velocites of left & right motors to arduino
    print left_vel
    print right_vel

def send_kp(data):
    cmd.send("change_kp", data.data)
    print data.data

def send_ki(data):
    cmd.send("change_ki", data.data)
    print data.data

if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["receive_ref","ff"],
                ["send_encoder","ffffff"],
                ["send_control_sig","ffffff"],
                ["change_kp","f"],
                ["change_ki","f"],
                ["request_ticks",""],
                ["request_control_signal",""]
                ]   # Send pwm 2 motors (m1l, m1r, m2l, m2r, m3l, m3r,)

    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, send_pwm)
    rospy.Subscriber("kp", Float32, send_kp)
    rospy.Subscriber("ki", Float32, send_ki)

    encPub=rospy.Publisher("encoders_ticks",Float32MultiArray,queue_size=10)
    ctrolPub=rospy.Publisher("control_signals",Float32MultiArray, queue_size=10)

    rate = rospy.Rate(120)
    while not rospy.is_shutdown():
        #cmd.send("request_ticks")
        ardMsg=cmd.receive()
        print "msg from arduino: %s" % (ardMsg,)
        if ardMsg is not None:
            cmd_name = ardMsg[0]
            args = ardMsg[1]
            time = ardMsg[2]
            if cmd_name=="send_encoder":
                pubMsg=Float32MultiArray(data=args)
                encPub.publish(pubMsg)
        #cmd.send("request_control_signal")
        if ardMsg is not None:
            ardMsg=cmd.receive()
            print "msg from arduino %s" % (ardMsg,)
            cmd_name = ardMsg[0]
            args = ardMsg[1]
            time = ardMsg[2]
            if cmd_name=="send_control_sig":
                pubMsg=Float32MultiArray(data=args)
                ctrolPub.publish(pubMsg)
        rate.sleep()
