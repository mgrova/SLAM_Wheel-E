#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16
from sensor_msgs.msg import Imu
from i2c import ini2c
import mpu6050

scaImu = rawImu = Imu() # Imu.msg from sensor_msgs.msg

if __name__ == '__main__':
    try:
        rawseq = scaseq = 0 # Sequential counter used in sensor_msgs/Imu.msg
        rospy.init_node('imu', anonymous=True)
        #rospy.init_node('pca', anonymous=True)
        rate = rospy.Rate(10) # 10hz rate = rospy.Rate(8000) # 8khz

        i2c=ini2c()
        imu1=mpu6050.mpu6050(i2c)
        imu1.wakeup()

        imu1_rawImu_pub = rospy.Publisher('imu1_rawImu', Imu, queue_size=10)  # Topic 2 publish raw Imu msg of mpu1
        imu1_scaImu_pub = rospy.Publisher('imu1_scaImu', Imu, queue_size=10)  # Topic 2 publish scaled Imu msg of mpu1
        #rospy.Subscriber("imu_cmds", Int16, mpu1.rcv_cmd) # Topic 2 watch for commands relatives to mpu1
        while not rospy.is_shutdown():
	    #imu1.wakeup()

            raw_accel = imu1.raw_accel()
            raw_gyro = imu1.raw_gyro()
            rawImu.header.stamp = rospy.Time.now()
            rawImu.header.frame_id = 'base_link'#'imu_link'
            rawImu.header.seq = rawseq
            rawImu.orientation_covariance[0] = -1
            rawImu.linear_acceleration.x = raw_accel[0]
            rawImu.linear_acceleration.y = raw_accel[1]
            rawImu.linear_acceleration.z = raw_accel[2]
            rawImu.linear_acceleration_covariance[0] = -1
            rawImu.angular_velocity.x = raw_gyro[0]
            rawImu.angular_velocity.y = raw_gyro[1]
            rawImu.angular_velocity.z = raw_gyro[2]
            rawImu.angular_velocity_covariance[0] = -1
            imu1_rawImu_pub.publish(rawImu)
            rawseq = rawseq + 1

            sca_accel = imu1.accel()
            sca_gyro = imu1.gyro()
            scaImu.header.stamp = rospy.Time.now()
            scaImu.header.frame_id = 'base_link'#'imu_link'
            scaImu.header.seq = scaseq
            scaImu.orientation_covariance[0] = -1
            scaImu.linear_acceleration.x = sca_accel[0]
            scaImu.linear_acceleration.y = sca_accel[1]
            scaImu.linear_acceleration.z = sca_accel[2]
            scaImu.linear_acceleration_covariance[0] = -1
            scaImu.angular_velocity.x = sca_gyro[0]
            scaImu.angular_velocity.y = sca_gyro[1]
            scaImu.angular_velocity.z = sca_gyro[2]
            scaImu.angular_velocity_covariance[0] = -1
            imu1_scaImu_pub.publish(scaImu)
            scaseq = scaseq + 1

            rate.sleep()

    except rospy.ROSInterruptException:
        pass
