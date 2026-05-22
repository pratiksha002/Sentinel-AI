#!/bin/bash
# QUICK START: Run Sentinel-AI Swarm Simulation
# This script launches the complete 5-drone swarm in Gazebo

PROJECT_DIR="/home/vboxuser/Sentinel-AI"
ROS2_WS="$PROJECT_DIR/ros2_ws"

echo "╔════════════════════════════════════════════════════════╗"
echo "║    SENTINEL-AI SWARM SIMULATOR - QUICK START          ║"
echo "║         5-Drone Formation Flying Test                 ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""

# Check if ROS2 is installed
if ! command -v ros2 &> /dev/null; then
    echo "❌ ERROR: ROS2 not found"
    echo "Install with: sudo apt install ros-humble-desktop"
    exit 1
fi

# Check if Gazebo is installed
if ! command -v gazebo &> /dev/null; then
    echo "❌ ERROR: Gazebo not found"
    echo "Install with: sudo apt install gazebo"
    exit 1
fi

echo "✓ ROS2 and Gazebo detected"
echo ""

# Source ROS2
source /opt/ros/humble/setup.bash
source $ROS2_WS/install/setup.bash

echo "✓ ROS2 environment sourced"
echo "✓ Workspace loaded: $ROS2_WS"
echo ""

echo "════════════════════════════════════════════════════════"
echo "LAUNCHING SENTINEL-AI SWARM"
echo "════════════════════════════════════════════════════════"
echo ""

echo "This will launch 3 terminals:"
echo "  1. Gazebo + ROS2 Core (main simulation)"
echo "  2. Swarm Monitor (telemetry display)"
echo "  3. Manual control (optional)"
echo ""

echo "Press ENTER to launch, or Ctrl+C to cancel..."
read

cd $PROJECT_DIR

# Terminal 1: Main launch (Gazebo + all ROS2 nodes)
echo ""
echo "Launching main system (Gazebo + ROS2 nodes)..."
gnome-terminal -- bash -c "
    source /opt/ros/humble/setup.bash
    source $ROS2_WS/install/setup.bash
    cd $PROJECT_DIR
    
    echo ''
    echo '╔════════════════════════════════════════════════╗'
    echo '║  GAZEBO SIMULATION STARTING...               ║'
    echo '║  Initializing 5 drones + formation control   ║'
    echo '╚════════════════════════════════════════════════╝'
    echo ''
    
    ros2 launch sentinel_swarm swarm_launch.py
" &

sleep 3

# Terminal 2: Monitor
echo "Launching telemetry monitor..."
gnome-terminal -- bash -c "
    source /opt/ros/humble/setup.bash
    source $ROS2_WS/install/setup.bash
    cd $PROJECT_DIR
    
    sleep 2
    
    echo ''
    echo '╔════════════════════════════════════════════════╗'
    echo '║  SWARM MONITOR - Live Telemetry            ║'
    echo '║  Showing drone positions and formation error  ║'
    echo '╚════════════════════════════════════════════════╝'
    echo ''
    
    python3 -c \"
import sys
sys.path.insert(0, '.')
from swarm_core.swarm_monitor import SwarmMonitor
import rclpy

rclpy.init()
monitor = SwarmMonitor()
monitor.start()
rclpy.spin(monitor.node)
\"
" &

sleep 2

echo ""
echo "════════════════════════════════════════════════════════"
echo "✅ SIMULATION LAUNCHED"
echo "════════════════════════════════════════════════════════"
echo ""
echo "Timeline:"
echo "  • 0-2s: Initialization"
echo "  • 2-5s: Drones arming"
echo "  • 5-15s: Takeoff to 2m altitude"
echo "  • 15-30s: Formation flying"
echo "  • 30-120s: A→B navigation"
echo "  • 120-130s: Landing and shutdown"
echo ""
echo "Expected Output:"
echo "  • Gazebo window: Visual simulation"
echo "  • Monitor: Real-time telemetry (5 drones)"
echo "  • Formation error: Should converge < 1.0m"
echo ""
echo "To stop:"
echo "  • Close Gazebo window or press Ctrl+C in terminals"
echo ""
echo "Logs:"
echo "  • Telemetry saved to: /tmp/sentinel_swarm_telemetry_*.csv"
echo "  • Full logs in: ~/.ros/log/"
echo ""
echo "════════════════════════════════════════════════════════"

wait
