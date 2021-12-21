import rclpy
import logging
import copy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
from std_msgs.msg import String

import random
from time import sleep

from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy, QoSDurabilityPolicy

class MinimalSubscriber(Node):


    def __init__(self):
        super().__init__('minimal_subscriber')
        self.x = 0
        self.count = 0
        qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT,
            history=QoSHistoryPolicy.RMW_QOS_POLICY_HISTORY_KEEP_LAST,
            depth=1
        )

            #durability=QoSDurabilityPolicy.RMW_QOS_POLICY_DURABILITY_VOLATILE

        self.subscription1 = self.create_subscription(
            PointCloud2,
            '/rslidar_points_41',
            self.listener_callback1, 
            qos_profile)

    def listener_callback1(self, msg):
        if self.x == msg.header.stamp.sec:
            self.count = self.count + 1
            print( str(msg.header.stamp.sec) + "." + str(msg.header.stamp.nanosec))
        else:
            self.x = msg.header.stamp.sec
            print("===========")
            print(self.count)
            print( str(msg.header.stamp.sec) + "." + str(msg.header.stamp.nanosec))
            self.count = 1


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

