#!/usr/bin/env python3
"""
Swarm coordinator node.
Implements consensus-based formation control algorithm.
Runs at 50 Hz and coordinates all drones to maintain formation.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point, Vector3
from std_msgs.msg import String, Float32
import numpy as np
from typing import Dict, List, Optional
import yaml
import os
import sys
import time
from ament_index_python.packages import get_package_share_directory
from swarm_core.math_utilities import FormationController, GeometryUtils
from swarm_core.communication_layer import SwarmCommunicationManager, SwarmMessageBroker


class SwarmCoordinator(Node):
    """
    Swarm coordination node.
    Implements formation control algorithm that runs at 50 Hz.
    """
    
    def __init__(self, config: Dict):
        """
        Initialize swarm coordinator.
        
        Args:
            config: Configuration dictionary
        """
        super().__init__('swarm_coordinator')
        
        self.config = config
        self.num_drones = config['swarm']['num_drones']
        self.control_freq = config['swarm']['control_frequency']
        self.formation_type = config['swarm']['formation_type']
        self.formation_scale = config['swarm']['formation_scale']
        
        # Formation controller with consensus algorithm
        self.formation_controller = FormationController(kp_consensus=0.5)
        
        # Current formation state
        self.formation_center = np.array([0.0, 0.0, 2.0])
        self.formation_targets = self._generate_formation_targets()
        
        # Drone state tracking
        self.drone_positions = {}
        self.drone_velocities = {}
        self.drone_healthy = {}
        
        for i in range(1, self.num_drones + 1):
            start_pos = config['drones'][f'drone_{i}'].get('start_position', [0, 0, 1])
            self.drone_positions[i] = np.array(start_pos)
            self.drone_velocities[i] = np.array([0.0, 0.0, 0.0])
            self.drone_healthy[i] = True
        
        # ROS2 Publishers (velocity commands to each drone)
        self.velocity_cmd_pubs = {}
        for i in range(1, self.num_drones + 1):
            self.velocity_cmd_pubs[i] = self.create_publisher(
                Vector3,
                f'/drones/drone_{i}/velocity_cmd',
                10
            )
        
        # Formation reference publisher
        self.formation_ref_pub = self.create_publisher(
            String,
            '/swarm/formation_reference',
            10
        )
        
        # Formation error publisher
        self.formation_error_pub = self.create_publisher(
            Float32,
            '/swarm/formation_error',
            10
        )
        
        # ROS2 Subscribers (drone state feedback)
        self.position_subs = {}
        self.velocity_subs = {}
        self.health_subs = {}
        
        for i in range(1, self.num_drones + 1):
            self.position_subs[i] = self.create_subscription(
                Point,
                f'/drones/drone_{i}/position',
                lambda msg, drone_id=i: self._position_callback(msg, drone_id),
                10
            )
            
            self.velocity_subs[i] = self.create_subscription(
                Vector3,
                f'/drones/drone_{i}/velocity',
                lambda msg, drone_id=i: self._velocity_callback(msg, drone_id),
                10
            )
        
        # Mission waypoint tracking
        self.mission_waypoints = config['mission']['waypoints']
        self.current_waypoint_idx = 0
        self.waypoint_tolerance = 0.5  # meters
        
        # Main control loop
        dt = 1.0 / self.control_freq
        self.create_timer(dt, self._control_loop)
        
        # Health check timer (slower)
        self.create_timer(1.0, self._health_check)
        
        self.last_loop_time = time.time()
        
        self.get_logger().info(
            f"SwarmCoordinator initialized: {self.num_drones} drones, "
            f"{self.formation_type} formation at {self.control_freq} Hz"
        )
    
    def _position_callback(self, msg: Point, drone_id: int):
        """Callback for drone position updates."""
        self.drone_positions[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def _velocity_callback(self, msg: Vector3, drone_id: int):
        """Callback for drone velocity updates."""
        self.drone_velocities[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def _generate_formation_targets(self) -> Dict[int, np.ndarray]:
        """Generate target positions for current formation."""
        targets = GeometryUtils.get_formation_targets(
            center=self.formation_center,
            formation_type=self.formation_type,
            num_drones=self.num_drones,
            scale=self.formation_scale
        )
        
        targets_dict = {}
        for i in range(1, self.num_drones + 1):
            if i - 1 < len(targets):
                targets_dict[i] = targets[i - 1]
            else:
                targets_dict[i] = self.formation_center
        
        return targets_dict
    
    def _update_formation_center(self, new_center: np.ndarray):
        """Update formation center and regenerate targets."""
        self.formation_center = new_center
        self.formation_targets = self._generate_formation_targets()
    
    def _control_loop(self):
        """
        Main swarm control loop (50 Hz).
        Implements consensus-based formation control.
        """
        try:
            now = time.time()
            dt = now - self.last_loop_time
            self.last_loop_time = now
            
            if dt <= 0:
                return
            
            # Update formation targets based on mission waypoint
            self._update_mission_state()
            
            # Compute velocity commands for each drone
            velocity_commands = {}
            
            for drone_id in range(1, self.num_drones + 1):
                if not self.drone_healthy.get(drone_id, False):
                    # Skip unhealthy drones, let them hover
                    velocity_commands[drone_id] = np.array([0.0, 0.0, 0.0])
                    continue
                
                # Get neighbor information (for consensus)
                neighbor_positions = []
                neighbor_targets = []
                
                for other_id in range(1, self.num_drones + 1):
                    if other_id != drone_id and self.drone_healthy.get(other_id, False):
                        neighbor_positions.append(self.drone_positions[other_id])
                        neighbor_targets.append(self.formation_targets[other_id])
                
                # Compute consensus velocity
                vel_cmd = self.formation_controller.compute_consensus_velocity(
                    my_position=self.drone_positions[drone_id],
                    my_target=self.formation_targets[drone_id],
                    neighbor_positions=neighbor_positions,
                    neighbor_targets=neighbor_targets
                )
                
                # Saturate velocity
                vel_cmd = GeometryUtils.saturate_velocity(
                    vel_cmd,
                    max_vel=self.config['safety']['max_velocity']
                )
                
                velocity_commands[drone_id] = vel_cmd
            
            # Publish velocity commands
            for drone_id, vel_cmd in velocity_commands.items():
                msg = Vector3(x=vel_cmd[0], y=vel_cmd[1], z=vel_cmd[2])
                self.velocity_cmd_pubs[drone_id].publish(msg)
            
            # Calculate and publish formation error
            positions = [self.drone_positions[i] for i in range(1, self.num_drones + 1)]
            targets = [self.formation_targets[i] for i in range(1, self.num_drones + 1)]
            
            formation_error = self.formation_controller.get_formation_error(positions, targets)
            error_msg = Float32(data=formation_error)
            self.formation_error_pub.publish(error_msg)
            
            # Log periodically
            if int(now) % 5 == 0:  # Every 5 seconds
                healthy_count = sum(1 for h in self.drone_healthy.values() if h)
                self.get_logger().info(
                    f"Formation error: {formation_error:.2f}m | "
                    f"Healthy drones: {healthy_count}/{self.num_drones} | "
                    f"Waypoint: {self.current_waypoint_idx + 1}/{len(self.mission_waypoints)}"
                )
        
        except Exception as e:
            self.get_logger().error(f"Error in control loop: {e}")
    
    def _update_mission_state(self):
        """Update mission state and formation center based on waypoints."""
        if self.current_waypoint_idx >= len(self.mission_waypoints):
            return  # Mission complete
        
        current_waypoint = np.array(self.mission_waypoints[self.current_waypoint_idx])
        
        # Check if formation has reached current waypoint
        distance_to_waypoint = np.linalg.norm(self.formation_center - current_waypoint)
        
        if distance_to_waypoint < self.waypoint_tolerance:
            # Move to next waypoint
            self.current_waypoint_idx += 1
            if self.current_waypoint_idx < len(self.mission_waypoints):
                next_waypoint = np.array(self.mission_waypoints[self.current_waypoint_idx])
                self._update_formation_center(next_waypoint)
                self.get_logger().info(f"Reached waypoint {self.current_waypoint_idx}, moving to next")
        else:
            # Move formation center towards current waypoint
            direction = (current_waypoint - self.formation_center) / (distance_to_waypoint + 1e-6)
            movement_speed = self.config['safety']['max_velocity'] * 0.3  # 30% of max
            movement = direction * movement_speed * (1.0 / self.control_freq)
            
            new_center = self.formation_center + movement
            self._update_formation_center(new_center)
    
    def _health_check(self):
        """Check drone health and detect communication loss."""
        # For now, mark all drones as healthy
        # In real implementation, check timestamp of last message
        for i in range(1, self.num_drones + 1):
            self.drone_healthy[i] = True  # Always true in simulation


def main(args=None):
    """Entry point for swarm_coordinator node."""
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
    
    # Create and run coordinator
    coordinator = SwarmCoordinator(config)
    
    try:
        rclpy.spin(coordinator)
    except KeyboardInterrupt:
        pass
    finally:
        coordinator.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
