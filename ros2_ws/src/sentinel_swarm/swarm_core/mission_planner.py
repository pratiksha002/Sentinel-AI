#!/usr/bin/env python3
"""
Mission planner node.
High-level mission orchestration and state management.
Coordinates drone takeoff, formation flying, waypoint navigation, and landing.
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool, String, Float32
import numpy as np
from typing import Dict, List
import yaml
import os
import sys
import time
from ament_index_python.packages import get_package_share_directory


class MissionState:
    """Enumeration of mission states."""
    IDLE = "IDLE"
    ARMING = "ARMING"
    TAKEOFF = "TAKEOFF"
    FORMATION_FLIGHT = "FORMATION_FLIGHT"
    MISSION = "MISSION"
    LANDING = "LANDING"
    COMPLETE = "COMPLETE"
    ABORT = "ABORT"


class MissionPlanner(Node):
    """
    Mission planner for autonomous swarm operations.
    Manages mission phases: arm → takeoff → formation → waypoints → landing → complete.
    """
    
    def __init__(self, config: Dict):
        """
        Initialize mission planner.
        
        Args:
            config: Configuration dictionary
        """
        super().__init__('mission_planner')
        
        self.config = config
        self.num_drones = config['swarm']['num_drones']
        self.mission_name = config['mission']['mission_name']
        
        # Mission state
        self.mission_state = MissionState.IDLE
        self.state_start_time = time.time()
        self.mission_timeout = config['swarm']['mission_timeout']
        
        # Drone arm status
        self.drones_armed = {i: False for i in range(1, self.num_drones + 1)}
        self.drones_ready = {i: False for i in range(1, self.num_drones + 1)}
        
        # ROS2 Publishers
        self.arm_cmd_pubs = {}
        self.mission_state_pub = self.create_publisher(String, '/swarm/mission_state', 10)
        self.mission_progress_pub = self.create_publisher(Float32, '/swarm/mission_progress', 10)
        
        for i in range(1, self.num_drones + 1):
            self.arm_cmd_pubs[i] = self.create_publisher(
                Bool,
                f'/drones/drone_{i}/arm_cmd',
                10
            )
        
        # ROS2 Subscribers (drone states)
        self.formation_error_sub = self.create_subscription(
            Float32,
            '/swarm/formation_error',
            self._formation_error_callback,
            10
        )
        
        self.drone_position_subs = {}
        self.drone_positions = {i: np.array([0.0, 0.0, 0.0]) for i in range(1, self.num_drones + 1)}
        
        for i in range(1, self.num_drones + 1):
            from geometry_msgs.msg import Point
            self.drone_position_subs[i] = self.create_subscription(
                Point,
                f'/drones/drone_{i}/position',
                lambda msg, drone_id=i: self._drone_position_callback(msg, drone_id),
                10
            )
        
        # Formation error tracking
        self.last_formation_error = float('inf')
        self.formation_stable_count = 0
        
        # Main state machine timer
        self.create_timer(1.0, self._state_machine)
        
        self.get_logger().info(
            f"MissionPlanner initialized for mission: {self.mission_name} "
            f"with {self.num_drones} drones"
        )
        
        # Start mission after brief delay
        self.create_timer(2.0, self._start_mission, oneshot=True)
    
    def _start_mission(self):
        """Start the mission sequence."""
        self.mission_state = MissionState.ARMING
        self.state_start_time = time.time()
        self.get_logger().info(f"Starting mission: {self.mission_name}")
    
    def _formation_error_callback(self, msg: Float32):
        """Callback for formation error updates."""
        self.last_formation_error = msg.data
    
    def _drone_position_callback(self, msg, drone_id: int):
        """Callback for drone position updates."""
        self.drone_positions[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def _state_machine(self):
        """Main state machine (1 Hz update)."""
        try:
            # Check mission timeout
            elapsed_time = time.time() - self.state_start_time
            if elapsed_time > self.mission_timeout and self.mission_state != MissionState.COMPLETE:
                self.get_logger().warn(f"Mission timeout! Aborting.")
                self.mission_state = MissionState.ABORT
            
            # Execute state logic
            if self.mission_state == MissionState.IDLE:
                pass  # Waiting for start command
            
            elif self.mission_state == MissionState.ARMING:
                self._state_arming()
            
            elif self.mission_state == MissionState.TAKEOFF:
                self._state_takeoff()
            
            elif self.mission_state == MissionState.FORMATION_FLIGHT:
                self._state_formation_flight()
            
            elif self.mission_state == MissionState.MISSION:
                self._state_mission()
            
            elif self.mission_state == MissionState.LANDING:
                self._state_landing()
            
            elif self.mission_state == MissionState.COMPLETE:
                self._state_complete()
            
            elif self.mission_state == MissionState.ABORT:
                self._state_abort()
            
            # Publish state
            self._publish_state()
        
        except Exception as e:
            self.get_logger().error(f"Error in state machine: {e}")
    
    def _state_arming(self):
        """Arming state: send arm commands to all drones."""
        # Send arm commands
        for i in range(1, self.num_drones + 1):
            arm_msg = Bool(data=True)
            self.arm_cmd_pubs[i].publish(arm_msg)
            self.drones_armed[i] = True
        
        # Wait for drones to be ready
        if all(self.drones_armed.values()):
            self.mission_state = MissionState.TAKEOFF
            self.state_start_time = time.time()
            self.get_logger().info("All drones armed, starting takeoff")
    
    def _state_takeoff(self):
        """Takeoff state: wait for drones to reach hover altitude."""
        # Check if all drones have reached 2m altitude
        all_airborne = True
        for i in range(1, self.num_drones + 1):
            if self.drone_positions[i][2] < 1.5:
                all_airborne = False
                break
        
        if all_airborne:
            self.mission_state = MissionState.FORMATION_FLIGHT
            self.state_start_time = time.time()
            self.get_logger().info("All drones airborne, waiting for formation")
    
    def _state_formation_flight(self):
        """Formation flight state: wait for formation to stabilize."""
        # Wait for formation error to be low and stable
        if self.last_formation_error < 1.0:  # < 1m error
            self.formation_stable_count += 1
        else:
            self.formation_stable_count = 0
        
        if self.formation_stable_count >= 5:  # Stable for 5 seconds
            self.mission_state = MissionState.MISSION
            self.state_start_time = time.time()
            self.get_logger().info(
                f"Formation stable (error: {self.last_formation_error:.2f}m), "
                f"starting mission waypoints"
            )
    
    def _state_mission(self):
        """Mission state: execute waypoints (coordinator handles this)."""
        # Check if mission is complete
        # For now, run for a fixed time
        elapsed = time.time() - self.state_start_time
        
        if elapsed > 30.0:  # 30 seconds of mission flight
            self.mission_state = MissionState.LANDING
            self.state_start_time = time.time()
            self.get_logger().info("Mission waypoints complete, landing")
    
    def _state_landing(self):
        """Landing state: command drones to descend."""
        # Check if all drones have landed
        all_landed = True
        for i in range(1, self.num_drones + 1):
            if self.drone_positions[i][2] > 0.2:
                all_landed = False
                break
        
        if all_landed:
            self.mission_state = MissionState.COMPLETE
            self.get_logger().info("All drones landed, mission complete")
    
    def _state_complete(self):
        """Mission complete state."""
        # Disarm all drones
        for i in range(1, self.num_drones + 1):
            arm_msg = Bool(data=False)
            self.arm_cmd_pubs[i].publish(arm_msg)
    
    def _state_abort(self):
        """Abort state: emergency landing."""
        self.get_logger().error("MISSION ABORT - Emergency landing!")
        
        # Force all drones to land immediately
        for i in range(1, self.num_drones + 1):
            arm_msg = Bool(data=False)
            self.arm_cmd_pubs[i].publish(arm_msg)
    
    def _publish_state(self):
        """Publish current mission state."""
        state_msg = String(data=self.mission_state)
        self.mission_state_pub.publish(state_msg)
        
        # Calculate mission progress (0.0 to 1.0)
        progress = 0.0
        if self.mission_state == MissionState.IDLE:
            progress = 0.0
        elif self.mission_state == MissionState.ARMING:
            progress = 0.1
        elif self.mission_state == MissionState.TAKEOFF:
            progress = 0.3
        elif self.mission_state == MissionState.FORMATION_FLIGHT:
            progress = 0.5
        elif self.mission_state == MissionState.MISSION:
            progress = 0.7
        elif self.mission_state == MissionState.LANDING:
            progress = 0.9
        elif self.mission_state == MissionState.COMPLETE:
            progress = 1.0
        
        progress_msg = Float32(data=progress)
        self.mission_progress_pub.publish(progress_msg)


def main(args=None):
    """Entry point for mission_planner node."""
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
    
    # Create and run planner
    planner = MissionPlanner(config)
    
    try:
        rclpy.spin(planner)
    except KeyboardInterrupt:
        pass
    finally:
        planner.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
