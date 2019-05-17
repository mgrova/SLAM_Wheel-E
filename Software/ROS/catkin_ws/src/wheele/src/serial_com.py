#!/usr/bin/env python

# 03/2019 @MikeMakes
# Delivered as it is, without any warranty
# Serial communication with arduino using CmdMssenger
# Python library: https://github.com/zivlab/PyCmdMessenger
# Arduino library: https://github.com/thijse/Arduino-CmdMessenger

import rospy
import PyCmdMessenger
from std_msgs.msg import Float64
from std_msgs.msg import Float32MultiArray
from wheele.msg import pwm6
from geometry_msgs.msg import Twist

def send_pwm(data): # cmd_vel topic (type Twist) callback
    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*0.25)/2 # How much velocity in each side we need for this movement
    right_vel = (linear_vel + (angular_vel*0.25)/2)

    cmd.send("receive_ref",left_vel,right_vel) # Send velocites of left & right motors to arduino
    print left_vel    


if __name__ == '__main__':
    # Initialize an ArduinoBoard instance.  This is where you specify baud rate and
    # serial timeout.  If you are using a non ATmega328 board, you might also need
    # to set the data sizes (bytes for integers, longs, floats, and doubles).
    arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=115200)

    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["cmd_off",""],
                ["receive_ref","ff"]]
                #["send_encoder","ffffff"],
                #["send_control_sig","ffffff"]]   # Send pwm 2 motors (m1l, m1r, m2l, m2r, m3l, m3r,)

    # Initialize the messenger
    cmd = PyCmdMessenger.CmdMessenger(arduino,commands)

    rospy.init_node('serial_com', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, send_pwm)
    
    encPub=rospy.Publisher("encoders_ticks",Float32MultiArray,queue_size=10)
    ctrolPub=rospy.Publisher("control_signals",Float32MultiArray, queue_size=10)
#    ardMsg=cmd.receive()

#    if ardMsg(0)=="send_encoder":
#        pubMsg=Float32MultiArray(data=ardMsg(1))
#       encPub.publish(pubMsg)

#    if ardMsg(0)=="send_control_sig":
#        pubMsg=Float32MultiArray(data=ardMsg(1))
#        ctrolPub.publish(pubMsg)
     
    rospy.spin()
