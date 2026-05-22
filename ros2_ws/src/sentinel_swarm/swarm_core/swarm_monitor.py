#!/usr/bin/env python3
"""
Swarm monitor node.
Real-time telemetry visualization, logging, and diagnostics.
Displays drone positions, formation error, battery status, and mission progress.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point, Vector3
from std_msgs.msg import Float32, String, Bool
import numpy as np
from typing import Dict, List
import yaml
import os
import sys
import csv
from ament_index_python.packages import get_package_share_directory
import time
from datetime import datetime


class SwarmMonitor(Node):
    """
    Monitors and logs swarm telemetry in real-time.
    """
    
    def __init__(self, config: Dict):
        """
        Initialize swarm monitor.
        
        Args:
            config: Configuration dictionary
        """
        super().__init__('swarm_monitor')
        
        self.config = config
        self.num_drones = config['swarm']['num_drones']
        
        # Telemetry storage
        self.drone_positions = {i: np.array([0.0, 0.0, 0.0]) for i in range(1, self.num_drones + 1)}
        self.drone_velocities = {i: np.array([0.0, 0.0, 0.0]) for i in range(1, self.num_drones + 1)}
        self.drone_batteries = {i: 100.0 for i in range(1, self.num_drones + 1)}
        self.drone_states = {i: "UNKNOWN" for i in range(1, self.num_drones + 1)}
        self.drone_health = {i: True for i in range(1, self.num_drones + 1)}
        
        self.formation_error = 0.0
        self.mission_state = "IDLE"
        self.mission_progress = 0.0
        
        # Logging
        self.log_file = None
        self.csv_writer = None
        self._init_logging()
        
        # ROS2 Subscribers
        for i in range(1, self.num_drones + 1):
            self.create_subscription(
                Point,
                f'/drones/drone_{i}/position',
                lambda msg, drone_id=i: self._position_callback(msg, drone_id),
                10
            )
            
            self.create_subscription(
                Vector3,
                f'/drones/drone_{i}/velocity',
                lambda msg, drone_id=i: self._velocity_callback(msg, drone_id),
                10
            )
            
            self.create_subscription(
                Float32,
                f'/drones/drone_{i}/battery',
                lambda msg, drone_id=i: self._battery_callback(msg, drone_id),
                10
            )
            
            self.create_subscription(
                String,
                f'/drones/drone_{i}/state',
                lambda msg, drone_id=i: self._state_callback(msg, drone_id),
                10
            )
            
            self.create_subscription(
                Bool,
                f'/drones/drone_{i}/health',
                lambda msg, drone_id=i: self._health_callback(msg, drone_id),
                10
            )
        
        # Swarm-level subscribers
        self.create_subscription(
            Float32,
            '/swarm/formation_error',
            self._formation_error_callback,
            10
        )
        
        self.create_subscription(
            String,
            '/swarm/mission_state',
            self._mission_state_callback,
            10
        )
        
        self.create_subscription(
            Float32,
            '/swarm/mission_progress',
            self._mission_progress_callback,
            10
        )
        
        # Display timer (1 Hz)
        self.create_timer(1.0, self._display_status)
        
        # Logging timer (10 Hz for detailed logging)
        self.create_timer(0.1, self._log_telemetry)
        
        self.get_logger().info("SwarmMonitor initialized")
    
    def _init_logging(self):
        """Initialize CSV logging."""
        try:
            log_dir = os.path.join(os.path.dirname(__file__), '..', 'logs')
            os.makedirs(log_dir, exist_ok=True)
            
            timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
            log_file = os.path.join(log_dir, f'mission_{timestamp}.csv')
            
            self.log_file = open(log_file, 'w', newline='')
            
            # CSV header
            header = ['timestamp']
            for i in range(1, self.num_drones + 1):
                header.extend([
                    f'drone_{i}_x', f'drone_{i}_y', f'drone_{i}_z',
                    f'drone_{i}_vx', f'drone_{i}_vy', f'drone_{i}_vz',
                    f'drone_{i}_battery', f'drone_{i}_state', f'drone_{i}_health'
                ])
            header.extend(['formation_error', 'mission_state', 'mission_progress'])
            
            self.csv_writer = csv.DictWriter(self.log_file, fieldnames=header)
            self.csv_writer.writeheader()
            
            self.get_logger().info(f"Logging to {log_file}")
        except Exception as e:
            self.get_logger().error(f"Failed to initialize logging: {e}")
    
    def _position_callback(self, msg: Point, drone_id: int):
        """Callback for drone position."""
        self.drone_positions[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def _velocity_callback(self, msg: Vector3, drone_id: int):
        """Callback for drone velocity."""
        self.drone_velocities[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def _battery_callback(self, msg: Float32, drone_id: int):
        """Callback for battery level."""
        self.drone_batteries[drone_id] = msg.data
    
    def _state_callback(self, msg: String, drone_id: int):
        """Callback for drone state."""
        self.drone_states[drone_id] = msg.data
    
    def _health_callback(self, msg: Bool, drone_id: int):
        """Callback for drone health."""
        self.drone_health[drone_id] = msg.data
    
    def _formation_error_callback(self, msg: Float32):
        """Callback for formation error."""
        self.formation_error = msg.data
    
    def _mission_state_callback(self, msg: String):
        """Callback for mission state."""
        self.mission_state = msg.data
    
    def _mission_progress_callback(self, msg: Float32):
        """Callback for mission progress."""
        self.mission_progress = msg.data
    
    def _display_status(self):
        """Display current status in terminal."""
        try:
            # Clear screen (Unix only)
            os.system('clear') if os.name == 'posix' else os.system('cls')
            
            print("=" * 80)
            print(f"SENTINEL-AI SWARM MONITOR - {datetime.now().strftime('%H:%M:%S')}")
            print("=" * 80)
            
            # Mission status
            print(f"\nMission State: {self.mission_state:15} | Progress: {self.mission_progress*100:5.1f}%")
            print(f"Formation Error: {self.formation_error:6.2f}m")
            
            # Drone status table
            print("\n" + "-" * 80)
            print(f"{'Drone':^6} | {'Position (x,y,z)':^24} | {'Vel (m/s)':^10} | {'Batt%':>6} | State | Health")
            print("-" * 80)
            
            healthy_count = 0
            for i in range(1, self.num_drones + 1):
                pos = self.drone_positions[i]
                vel = self.drone_velocities[i]
                vel_mag = np.linalg.norm(vel)
                batt = self.drone_batteries[i]
                state = self.drone_states[i][:6]
                health = "✓" if self.drone_health[i] else "✗"
                
                if self.drone_health[i]:
                    healthy_count += 1
                
                print(f"Drone {i} | {pos[0]:6.2f},{pos[1]:6.2f},{pos[2]:5.2f} | {vel_mag:8.2f}     | {batt:5.1f} | {state:6} | {health:6}")
            
            print("-" * 80)
            print(f"Healthy Drones: {healthy_count}/{self.num_drones}")
            print("=" * 80 + "\n")
        
        except Exception as e:
            self.get_logger().debug(f"Error displaying status: {e}")
    
    def _log_telemetry(self):
        """Log telemetry to CSV file."""
        try:
            if self.csv_writer is None:
                return
            
            row = {'timestamp': time.time()}
            
            for i in range(1, self.num_drones + 1):
                pos = self.drone_positions[i]
                vel = self.drone_velocities[i]
                
                row[f'drone_{i}_x'] = pos[0]
                row[f'drone_{i}_y'] = pos[1]
                row[f'drone_{i}_z'] = pos[2]
                row[f'drone_{i}_vx'] = vel[0]
                row[f'drone_{i}_vy'] = vel[1]
                row[f'drone_{i}_vz'] = vel[2]
                row[f'drone_{i}_battery'] = self.drone_batteries[i]
                row[f'drone_{i}_state'] = self.drone_states[i]
                row[f'drone_{i}_health'] = '1' if self.drone_health[i] else '0'
            
            row['formation_error'] = self.formation_error
            row['mission_state'] = self.mission_state
            row['mission_progress'] = self.mission_progress
            
            self.csv_writer.writerow(row)
            self.log_file.flush()
        
        except Exception as e:
            self.get_logger().error(f"Error logging telemetry: {e}")
    
    def __del__(self):
        """Clean up logging on shutdown."""
        if self.log_file:
            self.log_file.close()


def main(args=None):
    """Entry point for swarm_monitor node."""
    rclpy.init(args=args)
    
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
    
    # Create and run monitor
    monitor = SwarmMonitor(config)
    
    try:
        rclpy.spin(monitor)
    except KeyboardInterrupt:
        pass
    finally:
        monitor.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
