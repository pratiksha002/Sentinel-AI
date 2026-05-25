#!/usr/bin/env python3
"""
Two drone coordination: Drone 2 follows Drone 1.
This is the start of swarm behavior.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from px4_msgs.msg import TrajectorySetpoint, OffboardControlMode
from std_msgs.msg import Float32
import math

class TwoDroneControl(Node):
    def __init__(self):
        super().__init__('two_drone_control')
        
        # Drone 1: Get position
        self.drone1_pos_sub = self.create_subscription(
            Point,
            '/drone1/position',
            self.drone1_position_callback,
            10
        )
        
        # Drone 2: Get position
        self.drone2_pos_sub = self.create_subscription(
            Point,
            '/drone2/position',
            self.drone2_position_callback,
            10
        )
        
        # Drone 2: Send commands
        self.drone2_setpoint_pub = self.create_publisher(
            TrajectorySetpoint,
            '/drone2/setpoint',
            10
        )
        
        self.drone2_mode_pub = self.create_publisher(
            OffboardControlMode,
            '/drone2/mode',
            10
        )
        
        # Current positions
        self.drone1_pos = Point(x=0.0, y=0.0, z=0.0)
        self.drone2_pos = Point(x=0.0, y=0.0, z=0.0)
        
        # Control loop at 50Hz
        self.timer = self.create_timer(0.02, self.coordination_loop)
        
        self.get_logger().info('Two Drone Control started')
        
    def drone1_position_callback(self, msg):
        """Update drone 1 position"""
        self.drone1_pos = msg
        
    def drone2_position_callback(self, msg):
        """Update drone 2 position"""
        self.drone2_pos = msg
        
    def coordination_loop(self):
        """Main swarm coordination logic"""
        
        # Desired formation: Drone 2 should be 1 meter to the right of Drone 1
        desired_offset_x = 1.0  # 1 meter to the right
        desired_offset_y = 0.0
        desired_offset_z = 0.0
        
        # Drone 2's desired position
        drone2_desired_x = self.drone1_pos.x + desired_offset_x
        drone2_desired_y = self.drone1_pos.y + desired_offset_y
        drone2_desired_z = self.drone1_pos.z + desired_offset_z
        
        # Error (how far drone 2 is from where it should be)
        error_x = drone2_desired_x - self.drone2_pos.x
        error_y = drone2_desired_y - self.drone2_pos.y
        error_z = drone2_desired_z - self.drone2_pos.z
        
        # PID control (simple proportional gain for now)
        Kp = 0.5  # Proportional gain
        
        velocity_x = Kp * error_x
        velocity_y = Kp * error_y
        velocity_z = Kp * error_z
        
        # Limit velocity for safety
        max_velocity = 1.0  # meters per second
        
        def limit_velocity(v):
            if abs(v) > max_velocity:
                return max_velocity if v > 0 else -max_velocity
            return v
        
        velocity_x = limit_velocity(velocity_x)
        velocity_y = limit_velocity(velocity_y)
        velocity_z = limit_velocity(velocity_z)
        
        # Send offboard mode (keep telling PX4 we're in control)
        mode = OffboardControlMode()
        mode.velocity = True
        self.drone2_mode_pub.publish(mode)
        
        # Send velocity command
        setpoint = TrajectorySetpoint()
        setpoint.velocity[0] = velocity_x
        setpoint.velocity[1] = velocity_y
        setpoint.velocity[2] = velocity_z
        self.drone2_setpoint_pub.publish(setpoint)
        
        # Log every 1 second
        if int(self.get_clock().now().nanoseconds / 1e9) % 1 == 0:
            self.get_logger().info(
                f'D1 pos: ({self.drone1_pos.x:.2f}, {self.drone1_pos.y:.2f}, {self.drone1_pos.z:.2f}) | '
                f'D2 pos: ({self.drone2_pos.x:.2f}, {self.drone2_pos.y:.2f}, {self.drone2_pos.z:.2f}) | '
                f'Error: ({error_x:.2f}, {error_y:.2f}, {error_z:.2f})'
            )

def main(args=None):
    rclpy.init(args=args)
    controller = TwoDroneControl()
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

# Terminal 1: Start Gazebo with 2 drones
#cd ~/PX4-Autopilot
#make px4_sitl gazebo-classic

# Terminal 2: Run two-drone coordinator
#python3 two_drone_simple.py