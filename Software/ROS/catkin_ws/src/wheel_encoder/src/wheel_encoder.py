#!/usr/bin/env python
# license removed for brevity

import rospy
import RPi.GPIO as GPIO
from geometry.msg import TwistWithCovarianceStamped

# Define encoder pins->[enc_1L,enc_2L,enc_3L,enc_1R,enc_2R,enc_3R]
enc_list=[4,5,6,7,8,9] 
GPIO.setmode(GPIO.BCM)
GPIO.setup(enc_list, GPIO.IN)

# @todo -> Create an interrupcion for encoder that read the ticks. After, can be interesting
#	   obtain lineal and angular velocities and publish it of each encoder. (more or less)

def read_encoders():
    pub = rospy.Publisher('wheel_encoder', TwistWithCovarianceStamped, queue_size=10)
    rospy.init_node('wheel_encoder', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    # CODE COPIED FROM ROS TUTORIAL.
    while not rospy.is_shutdown():
        #hello_str = "hello world %s" % rospy.get_time()
        #rospy.loginfo(hello_str)
        #pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        read_encoders()
    except rospy.ROSInterruptException:
        pass

