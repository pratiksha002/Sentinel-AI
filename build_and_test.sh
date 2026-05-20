#!/bin/bash
# Quick start script for Sentinel-AI Swarm

set -e  # Exit on error

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROS2_WS="$PROJECT_DIR/ros2_ws"

echo "================================"
echo "SENTINEL-AI SWARM - Quick Start"
echo "================================"
echo "Project directory: $PROJECT_DIR"
echo ""

# Step 1: Setup workspace
if [ ! -d "$ROS2_WS" ]; then
    echo "Creating ROS2 workspace..."
    mkdir -p "$ROS2_WS/src"
    ln -s "$PROJECT_DIR" "$ROS2_WS/src/sentinel_swarm" || true
fi

cd "$ROS2_WS"

# Step 2: Source ROS2
echo "Sourcing ROS2 Humble..."
source /opt/ros/humble/setup.bash

# Step 3: Build package
echo ""
echo "Building sentinel_swarm package..."
colcon build --packages-select sentinel_swarm || {
    echo "Build failed! Check CMakeLists.txt and package.xml"
    exit 1
}

# Source workspace
source install/setup.bash

# Step 4: Run tests
echo ""
echo "Running unit tests..."
cd "$PROJECT_DIR"

echo "Testing math_utilities..."
python3 -m pytest tests/test_math_utilities.py -v || {
    echo "Math utilities tests failed!"
    exit 1
}

echo ""
echo "================================"
echo "✓ Build and tests successful!"
echo "================================"
echo ""
echo "Next steps:"
echo "1. Terminal 1: ros2 launch sentinel_swarm swarm_launch.py"
echo "2. Terminal 2: ros2 run sentinel_swarm swarm_monitor.py"
echo "3. Terminal 3: ros2 topic list"
echo ""
echo "Or read BUILD_AND_RUN.md for detailed instructions"
