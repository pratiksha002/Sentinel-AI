from launch import LaunchDescription
from launch.actions import ExecuteProcess, DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
import yaml

def generate_launch_description():
    # Load swarm config
    config_file = os.path.join(
        os.path.dirname(__file__), '..', 'config', 'swarm_config.yaml'
    )
    with open(config_file, 'r') as f:
        config = yaml.safe_load(f)
    
    # Gazebo world file
    world_file = os.path.join(
        os.path.dirname(__file__), '..', 'gazebo', 'worlds', 'swarm_arena.world'
    )
    
    num_drones = config['swarm']['num_drones']
    
    ld = LaunchDescription()
    
    # Launch Gazebo with the swarm arena world
    ld.add_action(ExecuteProcess(
        cmd=['gazebo', '--verbose', world_file],
        output='screen'
    ))
    
    # Launch Gazebo ROS2 bridge
    ld.add_action(Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='urdf_spawner',
        output='screen'
    ))
    
    # Launch swarm coordinator
    ld.add_action(Node(
        package='sentinel_swarm',
        executable='swarm_coordinator.py',
        name='swarm_coordinator',
        output='screen',
        parameters=[{'config_file': config_file}]
    ))
    
    # Launch mission planner
    ld.add_action(Node(
        package='sentinel_swarm',
        executable='mission_planner.py',
        name='mission_planner',
        output='screen',
        parameters=[{'config_file': config_file}]
    ))
    
    # Launch drone controllers (one per drone)
    for i in range(1, num_drones + 1):
        ld.add_action(Node(
            package='sentinel_swarm',
            executable='drone_controller.py',
            name=f'drone_controller_{i}',
            output='screen',
            parameters=[
                {'drone_id': i},
                {'config_file': config_file}
            ]
        ))
    
    # Launch swarm monitor
    ld.add_action(Node(
        package='sentinel_swarm',
        executable='swarm_monitor.py',
        name='swarm_monitor',
        output='screen',
        parameters=[{'config_file': config_file}]
    ))
    
    return ld
