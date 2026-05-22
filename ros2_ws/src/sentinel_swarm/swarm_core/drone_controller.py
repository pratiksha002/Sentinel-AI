#!/usr/bin/env python3
"""
Individual drone controller node.
Manages single drone telemetry, state machine, and command processing.
One instance per drone.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point, Vector3
from std_msgs.msg import Float32, Bool, String
import numpy as np
from typing import Dict, Any
import yaml
import os
import sys
from ament_index_python.packages import get_package_share_directory
from swarm_core.math_utilities import VelocityController, GeometryUtils
from swarm_core.communication_layer import SwarmCommunicationManager


class DroneState:
    """Enumeration of drone flight states."""
    DISARMED = "DISARMED"
    ARMED = "ARMED"
    TAKEOFF = "TAKEOFF"
    HOVERING = "HOVERING"
    OFFBOARD = "OFFBOARD"
    LANDING = "LANDING"
    LANDED = "LANDED"
    EMERGENCY = "EMERGENCY"


class DroneController(Node):
    """
    Controls a single drone.
    Manages telemetry parsing, state transitions, and health monitoring.
    """
    
    def __init__(self, drone_id: int, config: Dict):
        """
        Initialize drone controller.
        
        Args:
            drone_id: Unique drone ID (1-5)
            config: Configuration dictionary
        """
        super().__init__(f'drone_controller_{drone_id}')
        
        self.drone_id = drone_id
        self.config = config
        self.control_freq = config['swarm']['control_frequency']
        
        # State machine
        self.state = DroneState.DISARMED
        self.state_start_time = self.get_clock().now()
        
        # Telemetry
        self.position = np.array([0.0, 0.0, 0.0])
        self.velocity = np.array([0.0, 0.0, 0.0])
        self.battery_voltage = 12.6  # Nominal 3S LiPo
        self.battery_percentage = 100.0
        self.is_armed = False
        self.is_healthy = True
        self.gps_hdop = 0.5
        self.connected_satellites = 10
        
        # Commands
        self.velocity_command = np.array([0.0, 0.0, 0.0])
        
        # Initialize velocity controller
        pid_gains = config.get('pid_gains', {})
        self.velocity_controller = VelocityController(pid_gains)
        
        # Initialize from config
        drone_cfg = config['drones'].get(f'drone_{drone_id}', {})
        self.position = np.array(drone_cfg.get('start_position', [0.0, 0.0, 1.0]))
        
        # ROS2 Publishers
        self.position_pub = self.create_publisher(Point, f'/drones/drone_{drone_id}/position', 10)
        self.velocity_pub = self.create_publisher(Vector3, f'/drones/drone_{drone_id}/velocity', 10)
        self.battery_pub = self.create_publisher(Float32, f'/drones/drone_{drone_id}/battery', 10)
        self.state_pub = self.create_publisher(String, f'/drones/drone_{drone_id}/state', 10)
        self.health_pub = self.create_publisher(Bool, f'/drones/drone_{drone_id}/health', 10)
        
        # ROS2 Subscribers
        self.velocity_cmd_sub = self.create_subscription(
            Vector3,
            f'/drones/drone_{drone_id}/velocity_cmd',
            self._velocity_command_callback,
            10
        )
        
        self.armed_cmd_sub = self.create_subscription(
            Bool,
            f'/drones/drone_{drone_id}/arm_cmd',
            self._arm_command_callback,
            10
        )
        
        # Main control loop
        dt = 1.0 / self.control_freq
        self.create_timer(dt, self._control_loop)
        
        self.get_logger().info(
            f"DroneController initialized for drone_{drone_id} "
            f"at position {self.position}"
        )
    
    def _velocity_command_callback(self, msg: Vector3):
        """Callback for velocity commands."""
        self.velocity_command = np.array([msg.x, msg.y, msg.z])
    
    def _arm_command_callback(self, msg: Bool):
        """Callback for arming commands."""
        if msg.data and self.state == DroneState.DISARMED:
            self.state = DroneState.ARMED
            self.is_armed = True
            self.get_logger().info(f"Drone {self.drone_id} armed")
        elif not msg.data and self.state != DroneState.DISARMED:
            self.state = DroneState.DISARMED
            self.is_armed = False
            self.get_logger().info(f"Drone {self.drone_id} disarmed")
    
    def _control_loop(self):
        """Main control loop: update state, apply commands, publish telemetry."""
        try:
            dt = 1.0 / self.control_freq
            
            # State machine
            self._update_state_machine(dt)
            
            # Apply velocity commands if armed and in offboard mode
            if self.state == DroneState.OFFBOARD:
                # Simple dynamics: velocity affects position
                self.position += self.velocity_command * dt
                self.velocity = self.velocity_command * 0.95  # Damping
            
            # Battery simulation (discharge during flight)
            if self.is_armed:
                self.battery_percentage -= 0.01  # ~1% per second
                self.battery_voltage = 3.0 + (self.battery_percentage / 100.0) * 1.26  # 3.0V to 4.26V
            
            # Check for critical conditions
            if self.battery_percentage <= 10.0:
                self.state = DroneState.LANDING
                self.get_logger().warn(f"Drone {self.drone_id}: Low battery, landing")
            
            if self.battery_percentage <= 0.0:
                self.battery_percentage = 0.0
                self.state = DroneState.EMERGENCY
            
            # Publish telemetry
            self._publish_telemetry()
        
        except Exception as e:
            self.get_logger().error(f"Error in control loop: {e}")
            self.is_healthy = False
    
    def _update_state_machine(self, dt: float):
        """Update drone state machine."""
        if self.state == DroneState.DISARMED:
            # Nothing to do
            pass
        
        elif self.state == DroneState.ARMED:
            # Wait for takeoff command (check if z > start_z by 0.5m)
            if self.velocity_command[2] > 0.1:
                self.state = DroneState.TAKEOFF
                self.get_logger().info(f"Drone {self.drone_id} starting takeoff")
        
        elif self.state == DroneState.TAKEOFF:
            # Ascend until reaching target altitude
            if self.position[2] >= 2.0:  # 2m hover altitude
                self.state = DroneState.HOVERING
                self.velocity_command = np.array([0.0, 0.0, 0.0])
                self.get_logger().info(f"Drone {self.drone_id} reached hover altitude")
        
        elif self.state == DroneState.HOVERING:
            # Wait for formation command
            if np.linalg.norm(self.velocity_command) > 0.01:
                self.state = DroneState.OFFBOARD
                self.get_logger().info(f"Drone {self.drone_id} entering formation flight")
        
        elif self.state == DroneState.OFFBOARD:
            # Follow velocity commands
            pass
        
        elif self.state == DroneState.LANDING:
            # Descend
            if self.position[2] <= 0.1:
                self.state = DroneState.LANDED
                self.is_armed = False
                self.velocity_command = np.array([0.0, 0.0, 0.0])
                self.get_logger().info(f"Drone {self.drone_id} landed")
        
        elif self.state == DroneState.EMERGENCY:
            # Shut down everything
            self.velocity_command = np.array([0.0, 0.0, 0.0])
            self.is_armed = False
    
    def _publish_telemetry(self):
        """Publish drone telemetry on ROS2 topics."""
        # Position
        pos_msg = Point(x=self.position[0], y=self.position[1], z=self.position[2])
        self.position_pub.publish(pos_msg)
        
        # Velocity
        vel_msg = Vector3(x=self.velocity[0], y=self.velocity[1], z=self.velocity[2])
        self.velocity_pub.publish(vel_msg)
        
        # Battery
        batt_msg = Float32(data=self.battery_percentage)
        self.battery_pub.publish(batt_msg)
        
        # State
        state_msg = String(data=self.state)
        self.state_pub.publish(state_msg)
        
        # Health
        health_msg = Bool(data=self.is_healthy)
        self.health_pub.publish(health_msg)


def main(args=None):
    """Entry point for drone_controller node."""
    rclpy.init(args=args)
    
    # Get drone ID from node arguments
    import sys
    drone_id = 1
    for arg in (args or sys.argv)[1:]:
        if arg.startswith('--drone_id'):
            drone_id = int(arg.split('=')[1])
    
    # Load config
    try:
        config_file = os.path.join(
            get_package_share_directory('sentinel_swarm'),
            'config', 'swarm_config.yaml'
        )
    except:
        config_file = os.path.join(
            os.path.dirname(__file__), '..', '..', 'config', 'swarm_config.yaml'
        )
    
    with open(config_file, 'r') as f:
        config = yaml.safe_load(f)
    
    # Create and run controller
    controller = DroneController(drone_id, config)
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
