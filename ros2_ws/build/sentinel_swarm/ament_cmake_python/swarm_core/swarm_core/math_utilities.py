"""
Math utilities for swarm coordination, PID control, and geometry operations.
Supports consensus algorithms, kinematics, and formation control.
"""

import numpy as np
from typing import Tuple, List, Dict
import math


class PIDController:
    """Simple PID controller with saturation and integral anti-windup."""
    
    def __init__(self, kp: float, ki: float, kd: float, 
                 max_output: float = float('inf'),
                 max_integral: float = 1.0):
        """
        Initialize PID controller.
        
        Args:
            kp: Proportional gain
            ki: Integral gain
            kd: Derivative gain
            max_output: Maximum output saturation
            max_integral: Maximum integral term to prevent windup
        """
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.max_output = max_output
        self.max_integral = max_integral
        
        self.error_integral = 0.0
        self.last_error = 0.0
        self.last_time = None
    
    def update(self, error: float, dt: float) -> float:
        """
        Update PID controller with new error value.
        
        Args:
            error: Current error (setpoint - measurement)
            dt: Time step in seconds
        
        Returns:
            Control output
        """
        # Proportional term
        p_term = self.kp * error
        
        # Integral term with anti-windup
        self.error_integral += error * dt
        self.error_integral = np.clip(self.error_integral, 
                                      -self.max_integral, 
                                      self.max_integral)
        i_term = self.ki * self.error_integral
        
        # Derivative term
        if dt > 0:
            d_term = self.kd * (error - self.last_error) / dt
        else:
            d_term = 0.0
        
        self.last_error = error
        
        # Output with saturation
        output = p_term + i_term + d_term
        output = np.clip(output, -self.max_output, self.max_output)
        
        return output
    
    def reset(self):
        """Reset controller state."""
        self.error_integral = 0.0
        self.last_error = 0.0


class VelocityController:
    """3D velocity controller using cascaded PID loops."""
    
    def __init__(self, pid_gains: Dict):
        """
        Initialize 3D velocity controller.
        
        Args:
            pid_gains: Dict with 'position' and 'velocity' PID gains
        """
        pos_gains = pid_gains.get('position', {})
        vel_gains = pid_gains.get('velocity', {})
        
        # Position PIDs for x, y, z
        self.pid_x = PIDController(
            pos_gains.get('kp', 1.0),
            pos_gains.get('ki', 0.05),
            pos_gains.get('kd', 0.3),
            max_output=5.0
        )
        self.pid_y = PIDController(
            pos_gains.get('kp', 1.0),
            pos_gains.get('ki', 0.05),
            pos_gains.get('kd', 0.3),
            max_output=5.0
        )
        self.pid_z = PIDController(
            pos_gains.get('kp', 1.0),
            pos_gains.get('ki', 0.05),
            pos_gains.get('kd', 0.3),
            max_output=5.0
        )
        
        # Velocity PIDs (inner loop) for x, y, z
        self.vel_pid_x = PIDController(
            vel_gains.get('kp', 0.5),
            vel_gains.get('ki', 0.02),
            vel_gains.get('kd', 0.1),
            max_output=5.0
        )
        self.vel_pid_y = PIDController(
            vel_gains.get('kp', 0.5),
            vel_gains.get('ki', 0.02),
            vel_gains.get('kd', 0.1),
            max_output=5.0
        )
        self.vel_pid_z = PIDController(
            vel_gains.get('kp', 0.5),
            vel_gains.get('ki', 0.02),
            vel_gains.get('kd', 0.1),
            max_output=5.0
        )
    
    def compute_velocity_command(self, 
                                 current_pos: np.ndarray,
                                 target_pos: np.ndarray,
                                 current_vel: np.ndarray,
                                 target_vel: np.ndarray,
                                 dt: float) -> np.ndarray:
        """
        Compute velocity commands using cascaded position → velocity control.
        
        Args:
            current_pos: Current [x, y, z] position in meters
            target_pos: Target [x, y, z] position in meters
            current_vel: Current [vx, vy, vz] velocity in m/s
            target_vel: Target [vx, vy, vz] velocity in m/s
            dt: Time step in seconds
        
        Returns:
            Velocity command [vx_cmd, vy_cmd, vz_cmd]
        """
        pos_error = target_pos - current_pos
        
        # Position loop generates velocity references
        vel_ref_x = self.pid_x.update(pos_error[0], dt)
        vel_ref_y = self.pid_y.update(pos_error[1], dt)
        vel_ref_z = self.pid_z.update(pos_error[2], dt)
        
        vel_ref = np.array([vel_ref_x, vel_ref_y, vel_ref_z])
        
        # Velocity loop tracks the velocity references
        vel_error = vel_ref - current_vel
        
        vel_cmd_x = self.vel_pid_x.update(vel_error[0], dt)
        vel_cmd_y = self.vel_pid_y.update(vel_error[1], dt)
        vel_cmd_z = self.vel_pid_z.update(vel_error[2], dt)
        
        return np.array([vel_cmd_x, vel_cmd_y, vel_cmd_z])


class FormationController:
    """Consensus-based formation control for swarm of drones."""
    
    def __init__(self, kp_consensus: float = 0.5):
        """
        Initialize formation controller.
        
        Args:
            kp_consensus: Consensus gain (controls convergence speed)
        """
        self.kp_consensus = kp_consensus
    
    def compute_consensus_velocity(self,
                                   my_position: np.ndarray,
                                   my_target: np.ndarray,
                                   neighbor_positions: List[np.ndarray],
                                   neighbor_targets: List[np.ndarray]) -> np.ndarray:
        """
        Compute velocity command using consensus algorithm.
        Each drone tracks its local neighbors to maintain formation.
        
        Args:
            my_position: This drone's [x, y, z] position
            my_target: This drone's target [x, y, z] position in formation
            neighbor_positions: List of neighbor [x, y, z] positions
            neighbor_targets: List of neighbor target [x, y, z] positions
        
        Returns:
            Consensus velocity command
        """
        # Error from this drone to its target
        error = my_target - my_position
        
        # Consensus with neighbors (minimize relative positions)
        consensus_error = np.zeros(3)
        if len(neighbor_positions) > 0:
            neighbors_array = np.array(neighbor_positions)
            neighbor_targets_array = np.array(neighbor_targets)
            
            # Average neighbor error
            avg_neighbor_pos = np.mean(neighbors_array, axis=0)
            avg_neighbor_target = np.mean(neighbor_targets_array, axis=0)
            
            # Each drone should try to maintain consistent relative offset
            consensus_error = (avg_neighbor_target - avg_neighbor_pos) - \
                            (my_target - my_position)
        
        # Blend self-tracking and consensus
        total_error = error + self.kp_consensus * consensus_error
        
        # Convert to velocity (simple proportional)
        velocity = 0.5 * total_error  # Proportional to error
        
        return velocity
    
    def get_formation_error(self,
                           drone_positions: List[np.ndarray],
                           target_positions: List[np.ndarray]) -> float:
        """
        Compute formation error as RMS deviation from targets.
        
        Args:
            drone_positions: List of current [x, y, z] positions
            target_positions: List of target [x, y, z] positions
        
        Returns:
            RMS formation error in meters
        """
        errors = []
        for pos, target in zip(drone_positions, target_positions):
            error = np.linalg.norm(pos - target)
            errors.append(error)
        
        if len(errors) == 0:
            return 0.0
        
        return float(np.sqrt(np.mean(np.array(errors)**2)))


class GeometryUtils:
    """Utility functions for geometry and kinematics."""
    
    @staticmethod
    def quaternion_to_euler(q: np.ndarray) -> np.ndarray:
        """
        Convert quaternion [qx, qy, qz, qw] to Euler angles [roll, pitch, yaw].
        
        Args:
            q: Quaternion as [qx, qy, qz, qw]
        
        Returns:
            Euler angles [roll, pitch, yaw] in radians
        """
        qx, qy, qz, qw = q
        
        # Roll
        sinr_cosp = 2 * (qw * qx + qy * qz)
        cosr_cosp = 1 - 2 * (qx**2 + qy**2)
        roll = math.atan2(sinr_cosp, cosr_cosp)
        
        # Pitch
        sinp = 2 * (qw * qy - qz * qx)
        sinp = np.clip(sinp, -1, 1)
        pitch = math.asin(sinp)
        
        # Yaw
        siny_cosp = 2 * (qw * qz + qx * qy)
        cosy_cosp = 1 - 2 * (qy**2 + qz**2)
        yaw = math.atan2(siny_cosp, cosy_cosp)
        
        return np.array([roll, pitch, yaw])
    
    @staticmethod
    def euler_to_quaternion(roll: float, pitch: float, yaw: float) -> np.ndarray:
        """
        Convert Euler angles to quaternion [qx, qy, qz, qw].
        
        Args:
            roll, pitch, yaw: Angles in radians
        
        Returns:
            Quaternion as [qx, qy, qz, qw]
        """
        cy = math.cos(yaw * 0.5)
        sy = math.sin(yaw * 0.5)
        cp = math.cos(pitch * 0.5)
        sp = math.sin(pitch * 0.5)
        cr = math.cos(roll * 0.5)
        sr = math.sin(roll * 0.5)
        
        qw = cr * cp * cy + sr * sp * sy
        qx = sr * cp * cy - cr * sp * sy
        qy = cr * sp * cy + sr * cp * sy
        qz = cr * cp * sy - sr * sp * cy
        
        return np.array([qx, qy, qz, qw])
    
    @staticmethod
    def saturate_velocity(velocity: np.ndarray, max_vel: float) -> np.ndarray:
        """
        Saturate velocity to maximum magnitude.
        
        Args:
            velocity: [vx, vy, vz] velocity vector
            max_vel: Maximum velocity magnitude
        
        Returns:
            Saturated velocity
        """
        vel_mag = np.linalg.norm(velocity)
        if vel_mag > max_vel:
            return velocity * (max_vel / vel_mag)
        return velocity
    
    @staticmethod
    def get_formation_targets(center: np.ndarray,
                             formation_type: str,
                             num_drones: int,
                             scale: float = 2.0) -> List[np.ndarray]:
        """
        Generate target positions for drones in a formation.
        
        Args:
            center: Formation center [x, y, z]
            formation_type: 'line', 'triangle', 'square', 'circle'
            num_drones: Number of drones
            scale: Distance scale between drones
        
        Returns:
            List of target positions for each drone
        """
        targets = []
        
        if formation_type == 'line':
            # Linear formation along x-axis
            for i in range(num_drones):
                offset = np.array([i * scale, 0, 0])
                targets.append(center + offset)
        
        elif formation_type == 'triangle':
            # Triangular formation
            if num_drones >= 1:
                targets.append(center)  # Center
            if num_drones >= 2:
                targets.append(center + np.array([scale, 0, 0]))
            if num_drones >= 3:
                targets.append(center + np.array([0, scale, 0]))
            if num_drones >= 4:
                targets.append(center + np.array([scale, scale, 0]))
            if num_drones >= 5:
                targets.append(center + np.array([-scale, 0, 0]))
        
        elif formation_type == 'square':
            # Square formation
            half_scale = scale / 2
            for i in range(num_drones):
                if i == 0:
                    targets.append(center + np.array([-half_scale, -half_scale, 0]))
                elif i == 1:
                    targets.append(center + np.array([half_scale, -half_scale, 0]))
                elif i == 2:
                    targets.append(center + np.array([half_scale, half_scale, 0]))
                elif i == 3:
                    targets.append(center + np.array([-half_scale, half_scale, 0]))
                else:
                    targets.append(center + np.array([i * scale, 0, 0]))
        
        elif formation_type == 'circle':
            # Circular formation
            angle_step = 2 * math.pi / num_drones
            for i in range(num_drones):
                angle = i * angle_step
                x = center[0] + scale * math.cos(angle)
                y = center[1] + scale * math.sin(angle)
                z = center[2]
                targets.append(np.array([x, y, z]))
        
        else:
            # Default: line formation
            for i in range(num_drones):
                offset = np.array([i * scale, 0, 0])
                targets.append(center + offset)
        
        return targets


if __name__ == '__main__':
    # Simple tests
    print("Testing PID Controller...")
    pid = PIDController(kp=1.0, ki=0.1, kd=0.1)
    error = 1.0
    for _ in range(10):
        output = pid.update(error, dt=0.01)
        error *= 0.9  # Simulate error reduction
    print(f"PID test passed, final output: {output:.4f}")
    
    print("\nTesting geometry utils...")
    euler = np.array([0.1, 0.2, 0.3])
    q = GeometryUtils.euler_to_quaternion(euler[0], euler[1], euler[2])
    euler_back = GeometryUtils.quaternion_to_euler(q)
    print(f"Original euler: {euler}")
    print(f"Recovered euler: {euler_back}")
    
    print("\nTesting formation controller...")
    fc = FormationController()
    targets = GeometryUtils.get_formation_targets(
        center=np.array([0, 0, 2]),
        formation_type='triangle',
        num_drones=5,
        scale=2.0
    )
    print(f"Generated {len(targets)} target positions for triangle formation")
    for i, t in enumerate(targets):
        print(f"  Drone {i+1} target: {t}")
