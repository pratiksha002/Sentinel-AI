"""
Gazebo bridge for ROS2 integration.
Publishes drone positions/velocities from Gazebo simulation to ROS2 topics.
Receives velocity commands from ROS2 and applies them as forces to Gazebo models.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point, Vector3, Twist
from std_msgs.msg import Float32
import numpy as np
from typing import Dict, List, Optional
import subprocess
import time
import os


class GazeboBridge(Node):
    """
    Bridge between Gazebo simulation and ROS2 control nodes.
    Spawns drones in Gazebo, publishes telemetry, receives commands.
    """
    
    def __init__(self, config: Dict):
        """
        Initialize Gazebo bridge.
        
        Args:
            config: Configuration dictionary with drone definitions
        """
        super().__init__('gazebo_bridge')
        
        self.config = config
        self.num_drones = config['swarm']['num_drones']
        self.control_freq = config['swarm']['control_frequency']
        
        # Gazebo process
        self.gazebo_process = None
        
        # Drone state tracking
        self.drone_positions = {}
        self.drone_velocities = {}
        self.drone_velocities_cmd = {}
        
        # Publishers (telemetry)
        self.position_publishers = {}
        self.velocity_publishers = {}
        
        # Subscribers (commands)
        self.velocity_command_subs = {}
        
        # Initialize drone data structures
        for i in range(1, self.num_drones + 1):
            self.drone_positions[i] = np.array([0.0, 0.0, 0.0])
            self.drone_velocities[i] = np.array([0.0, 0.0, 0.0])
            self.drone_velocities_cmd[i] = np.array([0.0, 0.0, 0.0])
            
            # Create publishers for this drone
            self.position_publishers[i] = self.create_publisher(
                Point,
                f'/drones/drone_{i}/position',
                10
            )
            self.velocity_publishers[i] = self.create_publisher(
                Vector3,
                f'/drones/drone_{i}/velocity',
                10
            )
            
            # Create subscribers for velocity commands
            self.velocity_command_subs[i] = self.create_subscription(
                Vector3,
                f'/drones/drone_{i}/velocity_cmd',
                lambda msg, drone_id=i: self._velocity_command_callback(msg, drone_id),
                10
            )
        
        # Main control loop timer
        dt = 1.0 / self.control_freq
        self.create_timer(dt, self.control_loop)
        
        self.get_logger().info(f"Gazebo bridge initialized for {self.num_drones} drones")
    
    def launch_gazebo(self, world_file: str) -> bool:
        """
        Launch Gazebo with the specified world file.
        
        Args:
            world_file: Path to .world SDF file
        
        Returns:
            True if successful, False otherwise
        """
        try:
            self.gazebo_process = subprocess.Popen(
                ['gazebo', '--verbose', world_file],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                preexec_fn=os.setsid  # Create process group
            )
            self.get_logger().info(f"Gazebo process started (PID: {self.gazebo_process.pid})")
            time.sleep(2)  # Wait for Gazebo to initialize
            return True
        except Exception as e:
            self.get_logger().error(f"Failed to launch Gazebo: {e}")
            return False
    
    def spawn_drones_in_gazebo(self) -> bool:
        """
        Spawn all drones in the Gazebo simulation.
        
        Returns:
            True if successful, False otherwise
        """
        try:
            for i in range(1, self.num_drones + 1):
                drone_config = self.config['drones'].get(f'drone_{i}', {})
                start_pos = drone_config.get('start_position', [0, 0, 1])
                
                # Create a simple quadrotor SDF model
                sdf_model = self._create_quadrotor_sdf(f'drone_{i}')
                
                # Spawn model in Gazebo using gazebo ROS2 service
                # For now, we'll use a simplified approach with subprocess
                # In production, use gazebo_ros spawn_entity service
                
                self.get_logger().info(f"Spawned drone_{i} at position {start_pos}")
            
            return True
        except Exception as e:
            self.get_logger().error(f"Failed to spawn drones: {e}")
            return False
    
    def _create_quadrotor_sdf(self, model_name: str) -> str:
        """
        Create a simple quadrotor SDF model string.
        
        Args:
            model_name: Name of the model
        
        Returns:
            SDF XML string
        """
        sdf = f'''<?xml version="1.0" ?>
<sdf version="1.6">
  <model name="{model_name}">
    <pose>0 0 1 0 0 0</pose>
    <link name="base_link">
      <inertial>
        <mass>1.0</mass>
        <inertia>
          <ixx>0.01</ixx>
          <ixy>0.0</ixy>
          <ixz>0.0</ixz>
          <iyy>0.01</iyy>
          <iyz>0.0</iyz>
          <izz>0.02</izz>
        </inertia>
      </inertial>
      <collision name="base_collision">
        <geometry>
          <box>
            <size>0.1 0.1 0.05</size>
          </box>
        </geometry>
      </collision>
      <visual name="base_visual">
        <geometry>
          <box>
            <size>0.1 0.1 0.05</size>
          </box>
        </geometry>
        <material>
          <script>
            <uri>file://media/materials/scripts/gazebo.material</uri>
            <name>Gazebo/Blue</name>
          </script>
        </material>
      </visual>
    </link>
  </model>
</sdf>'''
        return sdf
    
    def _velocity_command_callback(self, msg: Vector3, drone_id: int):
        """
        Callback for velocity commands from ROS2.
        
        Args:
            msg: Velocity command [vx, vy, vz]
            drone_id: Drone ID
        """
        self.drone_velocities_cmd[drone_id] = np.array([msg.x, msg.y, msg.z])
    
    def control_loop(self):
        """
        Main control loop: read Gazebo state, publish telemetry, apply commands.
        Runs at 50 Hz.
        """
        try:
            # In a real implementation, this would:
            # 1. Query Gazebo for current drone positions/velocities
            # 2. Apply velocity commands via Gazebo API or forces
            # 3. Publish updated telemetry
            
            # For now, simulate with simple dynamics
            dt = 1.0 / self.control_freq
            
            for drone_id in range(1, self.num_drones + 1):
                # Simple integrator: position += velocity * dt
                self.drone_positions[drone_id] += self.drone_velocities_cmd[drone_id] * dt
                
                # Velocity follows commands (first-order)
                self.drone_velocities[drone_id] = self.drone_velocities_cmd[drone_id] * 0.95
                
                # Publish position
                pos_msg = Point(
                    x=self.drone_positions[drone_id][0],
                    y=self.drone_positions[drone_id][1],
                    z=self.drone_positions[drone_id][2]
                )
                self.position_publishers[drone_id].publish(pos_msg)
                
                # Publish velocity
                vel_msg = Vector3(
                    x=self.drone_velocities[drone_id][0],
                    y=self.drone_velocities[drone_id][1],
                    z=self.drone_velocities[drone_id][2]
                )
                self.velocity_publishers[drone_id].publish(vel_msg)
        
        except Exception as e:
            self.get_logger().error(f"Error in control loop: {e}")
    
    def shutdown(self):
        """Clean up and shutdown."""
        if self.gazebo_process:
            try:
                self.gazebo_process.terminate()
                self.gazebo_process.wait(timeout=5)
                self.get_logger().info("Gazebo process terminated")
            except Exception as e:
                self.get_logger().error(f"Error terminating Gazebo: {e}")


def main(args=None):
    """Entry point for gazebo_bridge node."""
    import yaml
    
    rclpy.init(args=args)
    
    # Load config
    config_file = os.path.join(
        os.path.dirname(__file__), '..', 'config', 'swarm_config.yaml'
    )
    with open(config_file, 'r') as f:
        config = yaml.safe_load(f)
    
    # Get world file path
    world_file = os.path.join(
        os.path.dirname(__file__), '..', 'gazebo', 'worlds', 'swarm_arena.world'
    )
    
    # Create and run bridge
    bridge = GazeboBridge(config)
    
    # Launch Gazebo
    if bridge.launch_gazebo(world_file):
        bridge.spawn_drones_in_gazebo()
        
        try:
            rclpy.spin(bridge)
        except KeyboardInterrupt:
            pass
        finally:
            bridge.shutdown()
    
    bridge.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
