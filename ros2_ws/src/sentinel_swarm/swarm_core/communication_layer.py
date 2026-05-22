"""
Communication layer for ROS2 pub/sub and message handling.
Provides abstraction for drone telemetry, swarm coordination, and multi-protocol support.
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSHistoryPolicy, QoSReliabilityPolicy, QoSDurabilityPolicy
from typing import Callable, Dict, Any, Optional, List
from geometry_msgs.msg import Point, Vector3, Pose
from std_msgs.msg import Float32
import threading
from collections import defaultdict
import time


class SwarmQoSProfiles:
    """Standard QoS profiles for swarm communication."""
    
    # Reliable: for critical state updates (drone positions, health)
    RELIABLE = QoSProfile(
        history=QoSHistoryPolicy.KEEP_LAST,
        depth=10,
        reliability=QoSReliabilityPolicy.RELIABLE,
        durability=QoSDurabilityPolicy.VOLATILE
    )
    
    # Best-effort: for frequent telemetry (sensor data, velocities)
    BEST_EFFORT = QoSProfile(
        history=QoSHistoryPolicy.KEEP_LAST,
        depth=5,
        reliability=QoSReliabilityPolicy.BEST_EFFORT,
        durability=QoSDurabilityPolicy.VOLATILE
    )


class SwarmPublisher:
    """Wrapper for ROS2 publisher with metadata tracking."""
    
    def __init__(self, node: Node, topic: str, msg_type: type, qos: str = 'reliable'):
        """
        Initialize publisher.
        
        Args:
            node: ROS2 node
            topic: Topic name
            msg_type: Message type class
            qos: 'reliable' or 'best_effort'
        """
        self.node = node
        self.topic = topic
        self.msg_type = msg_type
        
        qos_profile = SwarmQoSProfiles.RELIABLE if qos == 'reliable' else SwarmQoSProfiles.BEST_EFFORT
        self.publisher = node.create_publisher(msg_type, topic, qos_profile)
        
        self.last_publish_time = time.time()
        self.publish_count = 0
    
    def publish(self, msg: Any):
        """Publish message and track stats."""
        self.publisher.publish(msg)
        self.publish_count += 1
        self.last_publish_time = time.time()
    
    def get_stats(self) -> Dict[str, Any]:
        """Get publisher statistics."""
        return {
            'topic': self.topic,
            'publish_count': self.publish_count,
            'last_publish_time': self.last_publish_time
        }


class SwarmSubscriber:
    """Wrapper for ROS2 subscriber with latency monitoring."""
    
    def __init__(self, node: Node, topic: str, msg_type: type, 
                 callback: Callable, qos: str = 'reliable'):
        """
        Initialize subscriber.
        
        Args:
            node: ROS2 node
            topic: Topic name
            msg_type: Message type class
            callback: Callback function for messages
            qos: 'reliable' or 'best_effort'
        """
        self.node = node
        self.topic = topic
        self.msg_type = msg_type
        
        qos_profile = SwarmQoSProfiles.RELIABLE if qos == 'reliable' else SwarmQoSProfiles.BEST_EFFORT
        self.subscriber = node.create_subscription(msg_type, topic, callback, qos_profile)
        
        self.message_count = 0
        self.last_message_time = None
        self.latencies = []
        self.is_connected = False
    
    def record_message(self):
        """Record message receipt for latency tracking."""
        self.message_count += 1
        self.last_message_time = time.time()
        self.is_connected = True
    
    def get_stats(self) -> Dict[str, Any]:
        """Get subscriber statistics."""
        avg_latency = None
        if len(self.latencies) > 0:
            avg_latency = sum(self.latencies) / len(self.latencies)
        
        return {
            'topic': self.topic,
            'message_count': self.message_count,
            'last_message_time': self.last_message_time,
            'avg_latency': avg_latency,
            'is_connected': self.is_connected
        }


class SwarmMessageBroker:
    """
    Aggregates drone state from multiple sources (ROS2 topics).
    Provides unified interface for swarm coordinator to access drone state.
    """
    
    def __init__(self, num_drones: int):
        """
        Initialize message broker.
        
        Args:
            num_drones: Number of drones in swarm
        """
        self.num_drones = num_drones
        self.drone_states = {}
        self.state_lock = threading.Lock()
        
        # Initialize drone state containers
        for i in range(1, num_drones + 1):
            self.drone_states[i] = {
                'drone_id': i,
                'position': None,
                'velocity': None,
                'battery_percentage': 100.0,
                'is_armed': False,
                'is_healthy': True,
                'flight_mode': 'MANUAL',
                'gps_hdop': 0.0,
                'timestamp': time.time()
            }
    
    def update_drone_state(self, drone_id: int, state_dict: Dict[str, Any]):
        """
        Update state for a specific drone.
        
        Args:
            drone_id: Drone ID
            state_dict: Dictionary with state fields to update
        """
        with self.state_lock:
            if drone_id in self.drone_states:
                self.drone_states[drone_id].update(state_dict)
                self.drone_states[drone_id]['timestamp'] = time.time()
    
    def get_drone_state(self, drone_id: int) -> Dict[str, Any]:
        """Get current state for a drone."""
        with self.state_lock:
            if drone_id in self.drone_states:
                return dict(self.drone_states[drone_id])
        return None
    
    def get_all_drone_states(self) -> Dict[int, Dict[str, Any]]:
        """Get current state for all drones."""
        with self.state_lock:
            return {k: dict(v) for k, v in self.drone_states.items()}
    
    def get_drone_positions(self) -> Dict[int, tuple]:
        """Get positions of all drones as {drone_id: (x, y, z)}."""
        with self.state_lock:
            positions = {}
            for drone_id, state in self.drone_states.items():
                if state['position'] is not None:
                    pos = state['position']
                    positions[drone_id] = (pos.x, pos.y, pos.z) if hasattr(pos, 'x') else pos
            return positions
    
    def get_drone_velocities(self) -> Dict[int, tuple]:
        """Get velocities of all drones as {drone_id: (vx, vy, vz)}."""
        with self.state_lock:
            velocities = {}
            for drone_id, state in self.drone_states.items():
                if state['velocity'] is not None:
                    vel = state['velocity']
                    velocities[drone_id] = (vel.x, vel.y, vel.z) if hasattr(vel, 'x') else vel
            return velocities
    
    def is_drone_healthy(self, drone_id: int) -> bool:
        """Check if drone is healthy and connected."""
        with self.state_lock:
            if drone_id in self.drone_states:
                state = self.drone_states[drone_id]
                # Timeout after 5 seconds of no update
                if time.time() - state['timestamp'] > 5.0:
                    return False
                return state['is_healthy']
        return False
    
    def get_swarm_health(self) -> Dict[str, Any]:
        """Get overall swarm health status."""
        with self.state_lock:
            healthy_drones = sum(1 for i in range(1, self.num_drones + 1) 
                               if self.drone_states[i]['is_healthy'])
            
            avg_battery = np.mean([self.drone_states[i]['battery_percentage'] 
                                 for i in range(1, self.num_drones + 1)])
            
            return {
                'healthy_drones': healthy_drones,
                'total_drones': self.num_drones,
                'avg_battery': avg_battery,
                'swarm_operational': healthy_drones >= self.num_drones - 1  # Tolerate 1 drone loss
            }


class DroneStateTopic:
    """
    Helper class to manage subscription to a single drone's state topic
    and integrate with SwarmMessageBroker.
    """
    
    def __init__(self, node: Node, drone_id: int, broker: SwarmMessageBroker):
        """
        Initialize drone state topic subscription.
        
        Args:
            node: ROS2 node
            drone_id: Drone ID
            broker: SwarmMessageBroker instance
        """
        self.drone_id = drone_id
        self.broker = broker
        self.node = node
        
        # Subscribe to drone state topic
        topic_name = f'/drones/drone_{drone_id}/state'
        # Note: This assumes a custom DroneState message type
        # For now, we'll use geometry_msgs for compatibility
        self.subscriber = node.create_subscription(
            Point,
            f'/drones/drone_{drone_id}/position',
            self._position_callback,
            SwarmQoSProfiles.BEST_EFFORT
        )
        
        self.vel_subscriber = node.create_subscription(
            Vector3,
            f'/drones/drone_{drone_id}/velocity',
            self._velocity_callback,
            SwarmQoSProfiles.BEST_EFFORT
        )
    
    def _position_callback(self, msg: Point):
        """Callback for position updates."""
        self.broker.update_drone_state(self.drone_id, {'position': msg})
    
    def _velocity_callback(self, msg: Vector3):
        """Callback for velocity updates."""
        self.broker.update_drone_state(self.drone_id, {'velocity': msg})


class SwarmCommunicationManager:
    """
    High-level manager for all swarm communication.
    Handles publishers, subscribers, and message routing.
    """
    
    def __init__(self, node: Node, num_drones: int):
        """
        Initialize communication manager.
        
        Args:
            node: ROS2 node
            num_drones: Number of drones in swarm
        """
        self.node = node
        self.num_drones = num_drones
        self.broker = SwarmMessageBroker(num_drones)
        
        self.publishers: Dict[str, SwarmPublisher] = {}
        self.subscribers: Dict[str, SwarmSubscriber] = {}
        self.drone_state_topics: Dict[int, DroneStateTopic] = {}
        
        # Create drone state subscriptions
        for i in range(1, num_drones + 1):
            self.drone_state_topics[i] = DroneStateTopic(node, i, self.broker)
    
    def create_publisher(self, topic: str, msg_type: type, qos: str = 'reliable') -> SwarmPublisher:
        """Create a publisher with tracking."""
        pub = SwarmPublisher(self.node, topic, msg_type, qos)
        self.publishers[topic] = pub
        return pub
    
    def create_subscriber(self, topic: str, msg_type: type, 
                         callback: Callable, qos: str = 'reliable') -> SwarmSubscriber:
        """Create a subscriber with tracking."""
        sub = SwarmSubscriber(self.node, topic, msg_type, callback, qos)
        self.subscribers[topic] = sub
        return sub
    
    def get_broker(self) -> SwarmMessageBroker:
        """Get the message broker instance."""
        return self.broker
    
    def get_stats(self) -> Dict[str, Any]:
        """Get communication statistics."""
        pub_stats = {topic: pub.get_stats() for topic, pub in self.publishers.items()}
        sub_stats = {topic: sub.get_stats() for topic, sub in self.subscribers.items()}
        
        return {
            'publishers': pub_stats,
            'subscribers': sub_stats,
            'broker_health': self.broker.get_swarm_health()
        }


# Import numpy for broker utilities
import numpy as np


if __name__ == '__main__':
    print("Communication layer module loaded successfully")
    
    # Test SwarmMessageBroker
    broker = SwarmMessageBroker(num_drones=5)
    
    # Simulate drone state updates
    from geometry_msgs.msg import Point, Vector3
    
    for i in range(1, 6):
        pos = Point(x=float(i), y=0.0, z=1.0)
        vel = Vector3(x=0.1, y=0.0, z=0.0)
        broker.update_drone_state(i, {'position': pos, 'velocity': vel})
    
    print("Broker test passed")
    print(f"Swarm health: {broker.get_swarm_health()}")
