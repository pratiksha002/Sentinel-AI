"""
Unit tests for math_utilities module.
Tests PID control, formation geometry, and consensus algorithms.
"""

import pytest
import numpy as np
from swarm_core.math_utilities import (
    PIDController,
    VelocityController,
    FormationController,
    GeometryUtils
)


class TestPIDController:
    """Test PID controller."""
    
    def test_pid_proportional(self):
        """Test proportional control."""
        pid = PIDController(kp=1.0, ki=0.0, kd=0.0, max_output=10.0)
        output = pid.update(error=1.0, dt=0.01)
        assert output == pytest.approx(1.0)
    
    def test_pid_saturation(self):
        """Test output saturation."""
        pid = PIDController(kp=10.0, ki=0.0, kd=0.0, max_output=5.0)
        output = pid.update(error=1.0, dt=0.01)
        assert output == pytest.approx(5.0)
    
    def test_pid_integral_windup(self):
        """Test integral anti-windup."""
        pid = PIDController(kp=0.0, ki=1.0, kd=0.0, max_integral=1.0)
        
        # Accumulate error
        for _ in range(10):
            pid.update(error=1.0, dt=0.01)
        
        # Integral should be bounded
        assert pid.error_integral <= 1.0


class TestFormationController:
    """Test formation control."""
    
    def test_consensus_basic(self):
        """Test basic consensus algorithm."""
        fc = FormationController(kp_consensus=0.5)
        
        # Drone at origin, target is +1 in x
        my_pos = np.array([0.0, 0.0, 0.0])
        my_target = np.array([1.0, 0.0, 0.0])
        
        vel = fc.compute_consensus_velocity(
            my_position=my_pos,
            my_target=my_target,
            neighbor_positions=[],
            neighbor_targets=[]
        )
        
        # Should move towards target
        assert vel[0] > 0  # Positive x velocity
    
    def test_formation_error(self):
        """Test formation error calculation."""
        fc = FormationController()
        
        positions = [
            np.array([0.0, 0.0, 0.0]),
            np.array([1.0, 0.0, 0.0]),
            np.array([0.0, 1.0, 0.0])
        ]
        
        targets = [
            np.array([0.0, 0.0, 0.0]),
            np.array([1.0, 0.0, 0.0]),
            np.array([0.0, 1.0, 0.0])
        ]
        
        error = fc.get_formation_error(positions, targets)
        assert error == pytest.approx(0.0)


class TestGeometryUtils:
    """Test geometry utilities."""
    
    def test_quaternion_conversion(self):
        """Test quaternion ↔ Euler conversion."""
        euler = np.array([0.1, 0.2, 0.3])
        
        q = GeometryUtils.euler_to_quaternion(euler[0], euler[1], euler[2])
        euler_back = GeometryUtils.quaternion_to_euler(q)
        
        # Should be close to original (modulo 2π)
        assert np.allclose(euler, euler_back, atol=1e-5)
    
    def test_velocity_saturation(self):
        """Test velocity saturation."""
        vel = np.array([10.0, 0.0, 0.0])
        saturated = GeometryUtils.saturate_velocity(vel, max_vel=5.0)
        
        assert np.linalg.norm(saturated) == pytest.approx(5.0)
    
    def test_formation_targets_line(self):
        """Test line formation generation."""
        targets = GeometryUtils.get_formation_targets(
            center=np.array([0.0, 0.0, 2.0]),
            formation_type='line',
            num_drones=3,
            scale=2.0
        )
        
        assert len(targets) == 3
        assert targets[0][2] == pytest.approx(2.0)  # All at same z
    
    def test_formation_targets_circle(self):
        """Test circular formation generation."""
        targets = GeometryUtils.get_formation_targets(
            center=np.array([0.0, 0.0, 2.0]),
            formation_type='circle',
            num_drones=4,
            scale=2.0
        )
        
        assert len(targets) == 4
        
        # Check all at same altitude
        for target in targets:
            assert target[2] == pytest.approx(2.0)
        
        # Check all at same distance from center
        for target in targets:
            dist = np.linalg.norm(target[:2])
            assert dist == pytest.approx(2.0, abs=0.1)


if __name__ == '__main__':
    pytest.main([__file__, '-v'])
