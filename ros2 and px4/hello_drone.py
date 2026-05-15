#!/usr/bin/env python3
"""
Simple ROS 2 node that publishes and subscribes to test messages.
This verifies ROS 2 is working before touching drones.
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Point

class HelloDrone(Node):
    def __init__(self):
        super().__init__('hello_drone')
        
        # Publisher: publish a simple message
        self.publisher = self.create_publisher(String, 'drone_status', 10)
        
        # Subscriber: listen for messages
        self.subscriber = self.create_subscription(
            Point,
            'test_position',
            self.position_callback,
            10
        )
        
        # Timer: publish every 1 second
        self.timer = self.create_timer(1.0, self.publish_status)
        
        self.get_logger().info('HelloDrone node started!')
        
    def publish_status(self):
        """Publish status message every second"""
        msg = String()
        msg.data = 'Drone system is running!'
        self.publisher.publish(msg)
        self.get_logger().info(f'Published: {msg.data}')
        
    def position_callback(self, msg):
        """Receive position updates"""
        self.get_logger().info(f'Received position: x={msg.x}, y={msg.y}, z={msg.z}')

def main(args=None):
    rclpy.init(args=args)
    node = HelloDrone()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

# Terminal 1
#python3 hello_drone.py

# Terminal 2
#ros2 topic pub /test_position geometry_msgs/Point "{x: 1.0, y: 2.0, z: 3.0}" --once