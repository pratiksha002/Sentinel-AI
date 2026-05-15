#!/usr/bin/env python3
"""
Simple drone control: takeoff, hover, land.
This is the minimal code to actually control a drone via PX4.
Works with real drones or PX4 SITL simulation.
"""

import rclpy
from rclpy.node import Node
from px4_msgs.msg import (
    VehicleCommand,
    OffboardControlMode,
    TrajectorySetpoint
)
from std_msgs.msg import String
import time

class SimpleDroneControl(Node):
    def __init__(self):
        super().__init__('simple_drone_control')
        
        # Publishers (send commands to drone)
        self.vehicle_command_pub = self.create_publisher(
            VehicleCommand,
            '/fmu/in/vehicle_command',
            10
        )
        
        self.offboard_control_mode_pub = self.create_publisher(
            OffboardControlMode,
            '/fmu/in/offboard_control_mode',
            10
        )
        
        self.trajectory_setpoint_pub = self.create_publisher(
            TrajectorySetpoint,
            '/fmu/in/trajectory_setpoint',
            10
        )
        
        # Control loop timer (50 Hz)
        self.timer = self.create_timer(0.02, self.control_loop)
        
        # State tracking
        self.state = "IDLE"  # IDLE, ARMING, TAKING_OFF, HOVERING, LANDING
        self.state_time = 0.0  # How long in current state
        self.arm_command_sent = False
        self.offboard_command_sent = False
        
        self.get_logger().info('Simple Drone Control started')
        
    def send_vehicle_command(self, command_type, param1=0.0, param2=0.0):
        """Send a vehicle command to PX4"""
        cmd = VehicleCommand()
        cmd.command = command_type
        cmd.param1 = param1
        cmd.param2 = param2
        self.vehicle_command_pub.publish(cmd)
        
    def send_offboard_control_mode(self):
        """Tell PX4 we're sending offboard control commands"""
        mode = OffboardControlMode()
        mode.position = False  # We're sending velocity, not position
        mode.velocity = True   # Send velocity commands
        mode.acceleration = False
        mode.attitude = False
        mode.body_rate = False
        self.offboard_control_mode_pub.publish(mode)
        
    def send_trajectory_setpoint(self, vx=0.0, vy=0.0, vz=0.0):
        """Send velocity command to drone"""
        setpoint = TrajectorySetpoint()
        setpoint.velocity[0] = vx  # Forward velocity
        setpoint.velocity[1] = vy  # Right velocity
        setpoint.velocity[2] = vz  # Down velocity (negative = up)
        self.trajectory_setpoint_pub.publish(setpoint)
        
    def control_loop(self):
        """Main control loop, runs 50 times per second"""
        
        if self.state == "IDLE":
            # Start mission: arm the drone
            if not self.arm_command_sent:
                self.get_logger().info('Sending ARM command')
                self.send_vehicle_command(
                    command_type=400,  # MAV_CMD_COMPONENT_ARM_DISARM
                    param1=1.0         # 1.0 = arm
                )
                self.arm_command_sent = True
                self.state_time = 0.0
            
            self.state_time += 0.02
            if self.state_time > 2.0:  # Wait 2 seconds for arm to complete
                self.state = "TAKING_OFF"
                self.state_time = 0.0
                self.get_logger().info('State: TAKING_OFF')
        
        elif self.state == "TAKING_OFF":
            # Send offboard control mode
            self.send_offboard_control_mode()
            
            # Send takeoff command: upward velocity (negative vz = up)
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=-1.0)
            
            self.state_time += 0.02
            if self.state_time > 3.0:  # Takeoff for 3 seconds
                self.state = "HOVERING"
                self.state_time = 0.0
                self.get_logger().info('State: HOVERING')
        
        elif self.state == "HOVERING":
            # Send offboard control mode (keep sending)
            self.send_offboard_control_mode()
            
            # Send hover command: zero velocity
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=0.0)
            
            self.state_time += 0.02
            if self.state_time > 5.0:  # Hover for 5 seconds
                self.state = "LANDING"
                self.state_time = 0.0
                self.get_logger().info('State: LANDING')
        
        elif self.state == "LANDING":
            # Send offboard control mode
            self.send_offboard_control_mode()
            
            # Send downward velocity to land
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=0.5)
            
            self.state_time += 0.02
            if self.state_time > 5.0:  # Land for 5 seconds
                self.get_logger().info('Mission complete! Shutting down.')
                self.state = "IDLE"
                # Exit program
                rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    controller = SimpleDroneControl()
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

# Terminal 1: Start Gazebo with PX4
#cd ~/PX4-Autopilot
#make px4_sitl gazebo-classic

# Terminal 2: Run drone control
#python3 simple_drone_control.py