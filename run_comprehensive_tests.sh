#!/bin/bash
# Comprehensive test suite for Sentinel-AI Swarm
# Run this script to verify all components before full mission

set -e

PROJECT_DIR="/home/vboxuser/Sentinel-AI"
ROS2_WS="$PROJECT_DIR/ros2_ws"

echo "╔════════════════════════════════════════════════════════╗"
echo "║     SENTINEL-AI SWARM - COMPREHENSIVE TEST SUITE      ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counter
TESTS_PASSED=0
TESTS_FAILED=0

test_section() {
    echo ""
    echo -e "${BLUE}═════════════════════════════════════════${NC}"
    echo -e "${BLUE}TEST: $1${NC}"
    echo -e "${BLUE}═════════════════════════════════════════${NC}"
}

test_pass() {
    echo -e "${GREEN}✓ PASS: $1${NC}"
    ((TESTS_PASSED++))
}

test_fail() {
    echo -e "${RED}✗ FAIL: $1${NC}"
    ((TESTS_FAILED++))
}

# ============================================================================
# TEST 1: Environment Setup
# ============================================================================
test_section "1. Environment Setup"

if [ -d "$ROS2_WS" ]; then
    test_pass "ROS2 workspace exists at $ROS2_WS"
else
    test_fail "ROS2 workspace not found"
    exit 1
fi

if [ -f "$ROS2_WS/install/setup.bash" ]; then
    test_pass "ROS2 install setup.bash found"
else
    test_fail "ROS2 install setup.bash not found"
    exit 1
fi

# Source ROS2
source /opt/ros/humble/setup.bash
source $ROS2_WS/install/setup.bash

if [ "$ROS_DISTRO" == "humble" ]; then
    test_pass "ROS2 Humble sourced correctly (ROS_DISTRO=$ROS_DISTRO)"
else
    test_fail "ROS2 Humble not properly sourced"
fi

# ============================================================================
# TEST 2: Python Module Imports
# ============================================================================
test_section "2. Python Module Imports"

cd $PROJECT_DIR

python3 -c "from swarm_core.math_utilities import PIDController, FormationController, GeometryUtils" 2>/dev/null && \
    test_pass "math_utilities module imports successfully" || \
    test_fail "Failed to import math_utilities"

python3 -c "from swarm_core.communication_layer import SwarmPublisher, SwarmMessageBroker" 2>/dev/null && \
    test_pass "communication_layer module imports successfully" || \
    test_fail "Failed to import communication_layer"

python3 -c "from swarm_core.drone_controller import DroneController, DroneState" 2>/dev/null && \
    test_pass "drone_controller module imports successfully" || \
    test_fail "Failed to import drone_controller"

python3 -c "from swarm_core.swarm_coordinator import SwarmCoordinator" 2>/dev/null && \
    test_pass "swarm_coordinator module imports successfully" || \
    test_fail "Failed to import swarm_coordinator"

python3 -c "from swarm_core.mission_planner import MissionPlanner, MissionState" 2>/dev/null && \
    test_pass "mission_planner module imports successfully" || \
    test_fail "Failed to import mission_planner"

python3 -c "from swarm_core.swarm_monitor import SwarmMonitor" 2>/dev/null && \
    test_pass "swarm_monitor module imports successfully" || \
    test_fail "Failed to import swarm_monitor"

# ============================================================================
# TEST 3: Unit Tests
# ============================================================================
test_section "3. Unit Tests (math_utilities)"

cd $PROJECT_DIR
python3 -m pytest tests/test_math_utilities.py -v --tb=short 2>&1 | tee /tmp/pytest_output.txt

if grep -q "passed" /tmp/pytest_output.txt; then
    test_pass "Unit tests executed"
else
    test_fail "Unit tests did not execute properly"
fi

# ============================================================================
# TEST 4: Configuration Files
# ============================================================================
test_section "4. Configuration Files"

if [ -f "$PROJECT_DIR/config/swarm_config.yaml" ]; then
    test_pass "swarm_config.yaml exists"
    python3 -c "import yaml; yaml.safe_load(open('$PROJECT_DIR/config/swarm_config.yaml'))" && \
        test_pass "swarm_config.yaml is valid YAML" || \
        test_fail "swarm_config.yaml has syntax errors"
else
    test_fail "swarm_config.yaml not found"
fi

# ============================================================================
# TEST 5: Gazebo World File
# ============================================================================
test_section "5. Gazebo World File"

if [ -f "$PROJECT_DIR/gazebo/worlds/swarm_arena.world" ]; then
    test_pass "swarm_arena.world exists"
    if grep -q "<sdf version" "$PROJECT_DIR/gazebo/worlds/swarm_arena.world"; then
        test_pass "swarm_arena.world contains valid SDF structure"
    else
        test_fail "swarm_arena.world missing SDF structure"
    fi
else
    test_fail "swarm_arena.world not found"
fi

# ============================================================================
# TEST 6: ROS2 Package Discovery
# ============================================================================
test_section "6. ROS2 Package Discovery"

if ros2 pkg list 2>/dev/null | grep -q "sentinel_swarm"; then
    test_pass "sentinel_swarm package discovered by ROS2"
else
    test_fail "sentinel_swarm package not found by ROS2"
fi

# ============================================================================
# TEST 7: ROS2 Message Types
# ============================================================================
test_section "7. ROS2 Message Types"

if ros2 interface list 2>/dev/null | grep -q "sentinel_swarm/msg/DroneState"; then
    test_pass "DroneState message type registered"
else
    test_fail "DroneState message type not registered"
fi

if ros2 interface list 2>/dev/null | grep -q "sentinel_swarm/msg/SwarmCommand"; then
    test_pass "SwarmCommand message type registered"
else
    test_fail "SwarmCommand message type not registered"
fi

if ros2 interface list 2>/dev/null | grep -q "sentinel_swarm/msg/FormationReference"; then
    test_pass "FormationReference message type registered"
else
    test_fail "FormationReference message type not registered"
fi

# ============================================================================
# TEST 8: System Dependencies
# ============================================================================
test_section "8. System Dependencies"

command -v gazebo &> /dev/null && test_pass "Gazebo is installed" || test_fail "Gazebo not found"
command -v ros2 &> /dev/null && test_pass "ROS2 CLI is available" || test_fail "ROS2 CLI not available"
python3 -c "import numpy; import yaml; import pytest" 2>/dev/null && \
    test_pass "Python dependencies (numpy, yaml, pytest) available" || \
    test_fail "Missing Python dependencies"

# ============================================================================
# TEST 9: Math Algorithms (Functional Tests)
# ============================================================================
test_section "9. Math Algorithms (Functional Tests)"

python3 << 'EOF'
import sys
sys.path.insert(0, '/home/vboxuser/Sentinel-AI')
import numpy as np
from swarm_core.math_utilities import PIDController, FormationController, GeometryUtils

# Test PID
pid = PIDController(kp=1.0, ki=0.1, kd=0.1)
output = pid.update(1.0, 0.01)
assert abs(output) > 0, "PID output should be non-zero"
print("✓ PID controller working")

# Test Formation
fc = FormationController()
targets = GeometryUtils.get_formation_targets(
    center=np.array([0, 0, 2]),
    formation_type='triangle',
    num_drones=5,
    scale=2.0
)
assert len(targets) == 5, "Should generate 5 targets"
print("✓ Formation geometry working")

# Test consensus
vel = fc.compute_consensus_velocity(
    my_position=np.array([0, 0, 0]),
    my_target=np.array([1, 0, 0]),
    neighbor_positions=[np.array([1, 1, 0])],
    neighbor_targets=[np.array([2, 1, 0])]
)
assert vel is not None, "Consensus should return velocity"
print("✓ Consensus algorithm working")

EOF

if [ $? -eq 0 ]; then
    test_pass "All math algorithms functional"
else
    test_fail "Math algorithm tests failed"
fi

# ============================================================================
# TEST 10: Logs Directory
# ============================================================================
test_section "10. Logs Directory"

if [ ! -d "$PROJECT_DIR/logs" ]; then
    mkdir -p "$PROJECT_DIR/logs"
    test_pass "Created logs directory"
else
    test_pass "Logs directory exists"
fi

# ============================================================================
# SUMMARY
# ============================================================================
echo ""
echo "╔════════════════════════════════════════════════════════╗"
echo "║                    TEST SUMMARY                        ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""
echo -e "${GREEN}Tests Passed: $TESTS_PASSED${NC}"
echo -e "${RED}Tests Failed: $TESTS_FAILED${NC}"
echo ""

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║          ✓ ALL TESTS PASSED - READY TO RUN!           ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════════╝${NC}"
    echo ""
    echo "Next steps:"
    echo "  1. Terminal 1: cd $ROS2_WS && source install/setup.bash && ros2 launch sentinel_swarm swarm_launch.py"
    echo "  2. Terminal 2: cd $ROS2_WS && source install/setup.bash && ros2 run sentinel_swarm swarm_monitor.py"
    echo "  3. Terminal 3: cd $ROS2_WS && source install/setup.bash && ros2 topic list"
    echo ""
    exit 0
else
    echo -e "${RED}╔════════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║          ✗ SOME TESTS FAILED - CHECK ABOVE            ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════════╝${NC}"
    exit 1
fi
