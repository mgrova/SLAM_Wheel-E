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
from geometry_msgs.msg import Twist

def send_pwm(data): # cmd_vel topic (type Twist) callback
    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*0.25)/2 # How much velocity in each side we need for this movement
    right_vel = (linear_vel + (angular_vel*0.25)/2)

    cmd.send("change_pwm",left_vel, right_vel,left_vel, right_vel,left_vel, 0) # Send velocites of left & right motors to arduino

<<<<<<< HEAD
def send_pwm(data): # cmd_vel topic (type Twist) callback
    linear_vel = data.linear.x   # Retrieve the linear velocity (foward or backwards) that Whelee should have
    angular_vel = data.angular.z  # Same with angular velocity (clockwise turn is negative)

    left_vel = linear_vel - (angular_vel*0.25)/2 # How much velocity in each side we need for this movement
    right_vel = (linear_vel + (angular_vel*0.25)/2)

    cmd.send("change_pwm",left_vel, right_vel,left_vel, right_vel,left_vel, right_vel) # Send velocites of left & right motors to arduino

=======
>>>>>>> 79d6c8754ae41d5a2952e2e4181796c59e240c98
    ##data=float(pwm.m1l)
    #print "PWM-> m1L: " + str(pwm.m1l) 
    #print "m2L: " + str(pwm.m2l) 
    #print "m3L: " + str(pwm.m3l)
    #print "PWM-> m1R: " + str(pwm.m1r) 
    #print "m2R: " + str(pwm.m2r) 
    #print "m3R: " + str(pwm.m3r)
    #cmd.send("change_pwm",pwm.m1l,pwm.m1r,pwm.m2l,pwm.m2r,pwm.m3l,pwm.m3r) # Send pwm of left & right motors to arduino
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
    rospy.Subscriber("cmd_vel", Twist, send_pwm)
    rospy.spin()
