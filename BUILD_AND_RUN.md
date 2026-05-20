# Building and Running the Sentinel-AI Swarm

## Prerequisites

- Ubuntu 22.04 LTS
- ROS2 Humble (installed via `code.sh`)
- Gazebo 11
- Python 3.10+

## Build Instructions

### 1. Setup Workspace

```bash
cd ~/Sentinel-AI

# Create ROS2 workspace
mkdir -p ros2_ws/src
cd ros2_ws

# Copy the Sentinel-AI package
cp -r ~/Sentinel-AI src/sentinel_swarm
```

### 2. Build the Package

```bash
cd ~/Sentinel-AI/ros2_ws

# Source ROS2
source /opt/ros/humble/setup.bash

# Build
colcon build --packages-select sentinel_swarm

# Source workspace
source install/setup.bash
```

### 3. Run Tests

```bash
cd ~/Sentinel-AI

# Run math utilities tests
python3 -m pytest tests/test_math_utilities.py -v

# Run communication layer tests
python3 -m pytest tests/test_communication.py -v
```

## Running the Simulation

### Terminal 1: Launch Gazebo + Nodes

```bash
cd ~/Sentinel-AI/ros2_ws
source install/setup.bash

ros2 launch sentinel_swarm swarm_launch.py
```

### Terminal 2: Monitor Swarm Status

```bash
cd ~/Sentinel-AI/ros2_ws
source install/setup.bash

ros2 run sentinel_swarm swarm_monitor.py
```

### Terminal 3: Inspect ROS2 Topics

```bash
cd ~/Sentinel-AI/ros2_ws
source install/setup.bash

# List all active topics
ros2 topic list

# Echo drone positions
ros2 topic echo /drones/drone_1/position

# Echo formation error
ros2 topic echo /swarm/formation_error

# View ROS2 graph
rqt_graph
```

## Key ROS2 Topics

### Drone Topics (per drone, e.g., drone_1)

- `/drones/drone_{i}/position` (geometry_msgs/Point) - 3D position
- `/drones/drone_{i}/velocity` (geometry_msgs/Vector3) - Velocity
- `/drones/drone_{i}/velocity_cmd` (geometry_msgs/Vector3) - Velocity commands
- `/drones/drone_{i}/battery` (std_msgs/Float32) - Battery percentage
- `/drones/drone_{i}/state` (std_msgs/String) - Flight state
- `/drones/drone_{i}/health` (std_msgs/Bool) - Health status
- `/drones/drone_{i}/arm_cmd` (std_msgs/Bool) - Arming command

### Swarm Topics

- `/swarm/formation_error` (std_msgs/Float32) - Formation error in meters
- `/swarm/formation_reference` (std_msgs/String) - Current formation shape
- `/swarm/mission_state` (std_msgs/String) - Mission phase
- `/swarm/mission_progress` (std_msgs/Float32) - Mission progress (0-1)

## Mission Sequence

1. **IDLE** - Waiting for start command
2. **ARMING** - Sending arm commands to all drones
3. **TAKEOFF** - Drones ascending to 2m altitude
4. **FORMATION_FLIGHT** - Drones forming triangle pattern
5. **MISSION** - Following waypoints (A→B)
6. **LANDING** - Descending and landing
7. **COMPLETE** - Mission finished

## Waypoints

Default mission waypoints (configurable in `config/swarm_config.yaml`):

```
1. [0.0, 0.0, 2.0]    - Start hover
2. [5.0, 0.0, 2.0]    - Move to midpoint
3. [10.0, 0.0, 2.0]   - Move to destination (Point B)
4. [10.0, 0.0, 0.5]   - Descend for landing
```

## Configuration

Edit `config/swarm_config.yaml` to adjust:

- Number of drones
- Formation type (line, triangle, square, circle)
- Formation scale
- PID gains
- Waypoints and mission name
- Safety limits (max velocity, min/max altitude, etc.)

## Troubleshooting

### ROS2 nodes not starting

```bash
# Check ROS2 distro
echo $ROS_DISTRO  # Should be "humble"

# Verify package is discoverable
ros2 pkg list | grep sentinel
```

### Gazebo not launching

```bash
# Check Gazebo installation
gazebo --version

# Check world file exists
ls config/worlds/swarm_arena.world
```

### No drone movement

1. Check mission state: `ros2 topic echo /swarm/mission_state`
2. Check formation error: `ros2 topic echo /swarm/formation_error`
3. Check drone positions: `ros2 topic echo /drones/drone_1/position`

## Next Steps (Phase 1c - PX4 Integration)

To add realistic PX4 autopilot simulation:

1. Install PX4 SITL: `git clone https://github.com/PX4/PX4-Autopilot.git`
2. Build: `make px4_sitl gazebo-classic`
3. Implement `px4_ros2_bridge.py` with MAVLink protocol
4. Update `drone_controller.py` to interface with PX4

## Logging

Flight logs are saved to `logs/mission_YYYYMMDD_HHMMSS.csv` with full telemetry.

To analyze logs:

```python
import pandas as pd
df = pd.read_csv('logs/mission_20260520_120000.csv')
df.head()
```
