# Software Module Plan: Sentinel-AI Swarm Drone (4-5 Drones, Ubuntu 26.04, ROS2)

## TL;DR
Build a fresh, scalable Python + ROS2 architecture for 4-5 autonomous quadrotor swarm on **Ubuntu 22.04 LTS**. 
- **Phase 1a-1b (Weeks 7-10):** Gazebo native physics + ROS2 (fast prototyping)
- **Phase 1c (Weeks 11-12):** Add PX4-ROS2 bridge for realistic PX4 firmware testing
- **Phase 2 (Weeks 13-18):** Hardware integration with MAVLink protocol
Deploy 8 core modules (coordinator, drone controller, mission planner, comms layer with MAVLink, math, gazebo bridge, PX4 bridge, monitoring) with clear interfaces.

---

## Software Module Architecture

### **Core Modules (8 total)**

```
swarm_core/
├── 1. swarm_coordinator.py         (~250-300 lines) - Formation algorithm & swarm state
├── 2. drone_controller.py          (~200-250 lines) - Single drone telemetry & control interface
├── 3. mission_planner.py           (~150-200 lines) - Mission state machine & waypoints
├── 4. communication_layer.py       (~150-200 lines) - ROS2 + MAVLink protocol handling
├── 5. math_utilities.py            (~100-150 lines) - Kinematics, PID, consensus math
├── 6. gazebo_bridge.py             (~100-150 lines) - Gazebo native physics ↔ ROS2 (Phase 1a-1b)
├── 7. px4_ros2_bridge.py           (~150-200 lines) - PX4 + ROS2 + Gazebo integration (Phase 1c)
├── 8. swarm_monitor.py             (~150-200 lines) - Visualization, logging, debugging
│
└── config/
    ├── swarm_config.yaml           - Formation type, drone definitions, PID gains
    ├── px4_params.yaml             - PX4 tuning parameters (gains, limits)
    ├── gazebo_config.yaml          - Gazebo environment settings
    └── mavlink_config.yaml         - MAVLink protocol settings, message routing
```

---

## Module Responsibilities & Integration Points

### **1. swarm_coordinator.py**
**Purpose:** Implements distributed formation algorithm; runs 50 Hz; computes velocity commands for all drones.

**Responsibility:**
- Consensus algorithm (formation maintenance, resilient to drone loss)
- Position/velocity state tracking per drone
- Generates velocity setpoints for each drone
- Detects and handles drone failures (graceful degradation)
- Publishes velocity commands to each drone controller

**Key Interfaces:**
- **Subscriptions:** `/drones/drone_[i]/state` (position, velocity, health)
- **Publications:** `/swarm/formation_reference`, `/drones/drone_[i]/velocity_ref`
- **Execution:** 50 Hz timer callback

**Dependencies:**
- `communication_layer.py` (ROS2 subscription helpers)
- `math_utilities.py` (consensus math, kinematics)

---

### **2. drone_controller.py**
**Purpose:** Manages single drone telemetry parsing, PX4 communication, and health monitoring. One instance per drone.

**Responsibility:**
- Parse PX4 telemetry (pose, velocity, IMU, battery)
- Translate velocity commands → PX4 `TrajectorySetpoint` messages
- Monitor drone health (battery, failsafe, connection loss)
- Manage drone state transitions (DISARMED → ARMED → OFFBOARD → LANDED)
- Publish drone state to swarm coordinator

**Key Interfaces:**
- **Subscriptions:** `/px4_[i]/fmu/in/vehicle_command`, `/px4_[i]/fmu/in/trajectory_setpoint`, drone health topics
- **Publications:** `/drones/drone_[i]/state`, `/drones/drone_[i]/telemetry`
- **Execution:** 50 Hz telemetry loop

**Dependencies:**
- `communication_layer.py` (ROS2 pub/sub)
- `math_utilities.py` (coordinate transformations if needed)

---

### **3. mission_planner.py**
**Purpose:** High-level mission state machine; sequences takeoff → formation → mission → landing phases.

**Responsibility:**
- Define mission (waypoints, formation shape, timing)
- Coordinate swarm through mission phases
- Handle timeouts, emergency conditions
- Signal formation reference changes to coordinator
- Log mission progress

**Key Interfaces:**
- **Subscriptions:** `/swarm/coordinator_state`, user mission input
- **Publications:** `/swarm/mission_state`, `/swarm/formation_reference`
- **Execution:** 10 Hz (slower than control loop; event-driven)

**Dependencies:**
- `swarm_coordinator.py` (formation tracking)
- `communication_layer.py` (ROS2)
- `math_utilities.py` (waypoint interpolation)

---

### **4. communication_layer.py**
**Purpose:** Abstracts ROS2 pub/sub and MAVLink protocol; provides reusable subscription/publication helpers for both simulation and hardware phases.

**Responsibility:**
- **ROS2 abstractions:** Thread-safe message queue, QoS policy enforcement, namespace management
- **MAVLink protocol:** MAVLink message serialization/deserialization (for hardware phase & Phase 1c PX4 bridge)
  - MAVLink packet encoding/decoding (heartbeat, attitude, local position, velocity estimate)
  - Autopilot message routing (COMMAND_LONG, SET_POSITION_TARGET_LOCAL_NED, TRAJECTORY_REPRESENTATION_WAYPOINTS)
  - System/component ID management (drone identification in swarm)
- **Multi-protocol handling:** ROS2 for simulation, MAVLink for hardware (abstracted interface)
- **Latency monitoring & diagnostics:** Track message round-trip times

**Key Exports:**
- `SwarmPublisher(topic, message_type, qos='reliable')` — ROS2 publisher
- `SwarmSubscriber(topic, message_type, callback, qos='reliable')` — ROS2 subscriber
- `MAVLinkEncoder(system_id, component_id)` — Encode ROS2 → MAVLink packets
- `MAVLinkDecoder()` — Decode MAVLink packets → ROS2 messages
- `SwarmMessageBroker()` — Aggregates drone state (ROS2 or MAVLink, transparent to coordinator)
- `MAVLinkRouter(broadcast_rules)` — Route MAVLink messages to correct drone (by system ID)

**MAVLink Message Subset (8 core messages):**
```
HEARTBEAT (1)                      — Alive signal, autopilot type, mode
ATTITUDE (30)                      — Roll, pitch, yaw, rates (for diagnostics)
LOCAL_POSITION_NED (32)            — Position in NED frame (primary for coordination)
GLOBAL_POSITION_INT (33)           — GPS position (for logging)
MISSION_CURRENT (42)               — Current waypoint index
VFR_HUD (74)                       — Altitude, ground speed, climb rate
COMMAND_ACK (77)                   — Command execution result
SET_POSITION_TARGET_LOCAL_NED (84) — Velocity/position setpoint to autopilot
TRAJECTORY_REPRESENTATION_WAYPOINTS (332) — Multi-waypoint trajectory (future)
SYSTEM_TIME (2)                    — Time sync (important for swarm coordination)
```

**Dependencies:**
- `pymavlink` (MAVLink protocol library)
- ROS2 core libraries (`rclpy`)
- `struct` (binary packet unpacking)

---

### **5. math_utilities.py**
**Purpose:** Centralized math library for swarm algorithms and control.

**Responsibility:**
- **Kinematics:** Rotation matrices (quaternion ↔ Euler), velocity normalization
- **PID control:** Proportional/integral/derivative tuning
- **Consensus algorithm:** Weighted averaging for formation consensus
- **Geometry:** Distance calculations, formation shape definitions (square, line, circle)
- **Safety:** Velocity saturation, collision avoidance (if adding later)

**Key Functions:**
- `compute_pid_velocity(error, kp, ki, kd, dt)`
- `consensus_velocity(drone_positions, target_offsets, kp_consensus)`
- `quaternion_to_euler(quat)`, `euler_to_rotation_matrix(roll, pitch, yaw)`
- `saturate_velocity(velocity, max_vel)`

**Dependencies:**
- `numpy`, `scipy.spatial` (distance calculations)

---

### **6. gazebo_bridge.py**
**Purpose:** Bridges Gazebo native physics ↔ ROS2 topics (Phase 1a-1b: lightweight prototyping, NO PX4).

**Responsibility:**
- Subscribe to Gazebo drone poses (via Gazebo ROS2 bridge plugins)
- Publish telemetry to ROS2 topics in standard format (pose, velocity, IMU simulation)
- Receive velocity commands and apply to Gazebo physics
- Simulation time sync (deterministic, repeatable runs)
- Logging/replay capability

**Key Interfaces:**
- **Subscriptions:** `/gazebo/model_states` or Gazebo sensor plugins
- **Publications:** `/drones/drone_[i]/pose`, `/drones/drone_[i]/velocity`, `/drones/drone_[i]/imu_sim`
- **Services:** Gazebo spawn/despawn drone models on demand

**Dependencies:**
- `gazebo_ros` (Gazebo ROS2 bridge)
- `numpy` (coordinate transformations)

---

### **7. px4_ros2_bridge.py** ⭐ **NEW — Phase 1c Only**
**Purpose:** Bridges PX4 autopilot + ROS2 + Gazebo for realistic simulation (added in Phase 1c after prototyping validates algorithms).

**Responsibility:**
- Launch PX4-SITL (Software In The Loop) instance per drone in Gazebo
- Translate ROS2 velocity commands → MAVLink SET_POSITION_TARGET_LOCAL_NED messages to PX4
- Parse PX4 telemetry (LOCAL_POSITION_NED, ATTITUDE, SYSTEM_TIME) via MAVLink → ROS2 topics
- Multi-drone PX4 instance management (system IDs 1-5 for 5 drones)
- PX4 parameter tuning interface (gains, limits, failsafe thresholds)
- Heartbeat monitoring (detect PX4 crashes/timeouts)

**Key Interfaces:**
- **Subscriptions (from coordinator):** `/drones/drone_[i]/velocity_ref`
- **Publications (to coordinator):** `/drones/drone_[i]/state` (via MAVLink + ROS2)
- **MAVLink connections:** UDP ports 14540-14544 (local PX4 instances)
- **Gazebo integration:** Spawns iris.sdf models with PX4-Gazebo physics plugin

**MAVLink Message Flow (ROS2 → PX4 → Gazebo):**
```
ROS2: velocity_ref (vx, vy, vz, yaw_rate)
  ↓
MAVLink: SET_POSITION_TARGET_LOCAL_NED (type_mask=velocity mode)
  ↓
PX4 Autopilot: Processes velocity setpoint, runs attitude control loop
  ↓
Gazebo: Applies thrust/torque to quadrotor model
  ↓
Gazebo Physics: Integrates accelerations → new pose
  ↓
PX4 Sensors: Simulated IMU, barometer, GPS → sensor fusion
  ↓
MAVLink: LOCAL_POSITION_NED, ATTITUDE, SYSTEM_TIME
  ↓
ROS2: telemetry topics → swarm_coordinator
```

**Key Config (px4_params.yaml):**
```yaml
px4_instances:
  drone_1:
    system_id: 1
    udp_port: 14540
    gazebo_model: iris
  drone_2:
    system_id: 2
    udp_port: 14541
    gazebo_model: iris
  # ... drone_3, drone_4, drone_5

px4_gains:
  attitude_controller:
    roll_pitch_p: 6.5
    roll_pitch_i: 0.05
    roll_pitch_d: 0.1
  position_controller:
    xy_p: 1.0
    z_p: 2.0
```

**Dependencies:**
- `pymavlink` (MAVLink protocol)
- `px4-autopilot` (installed locally, built for SITL)
- `gazebo_ros` (physics plugin)
- `socket` (UDP for MAVLink)

---

### **8. swarm_monitor.py**
**Purpose:** Real-time visualization, logging, and debugging dashboard.

**Responsibility:**
- Display swarm state (drone positions, formation error, health)
- Log all telemetry to file for post-mission analysis
- Real-time plots (formation geometry, velocity commands, battery)
- Detect and alert on anomalies (formation deviation, drone loss)
- Publish metrics to GCS (if hardware deployment)

**Key Features:**
- Terminal-based dashboard (curses) or web UI (optional: matplotlib/plotly)
- CSV logging (timestamp, drone positions, velocities, errors, battery)
- Replay capability (replay logged missions in simulation)

**Dependencies:**
- `matplotlib`, `curses` (or Flask for web UI)

---

## Requirements & Dependencies

### **System Requirements**
- **OS:** Ubuntu 22.04 LTS (official ROS2 Humble standard)
- **Python:** 3.10+ (native with Ubuntu 22.04)
- **Storage:** ~3 GB (ROS2 binaries, Gazebo, PX4, dependencies)
- **RAM:** 4+ GB (4-drone Gazebo native comfortable; 6+ GB with PX4-SITL); 8+ GB recommended for Phase 1c
- **CPU:** Multi-core processor recommended (50 Hz @ 4-5 drones + Gazebo physics simulation)

### **Core Dependency Stack**

#### **ROS2 Humble & Middleware (Ubuntu 22.04 native)**
```yaml
ros2-humble:           # ROS 2 Humble (long-term support, default on Ubuntu 22.04)
  - ros2-base
  - ros2-geometry2     # tf2 for coordinate transforms
  - ros2-sensor-msgs   # IMU, odometry messages
  - ros2-std-msgs      # Standard message types
  - python3-rclpy      # ROS2 Python client library
  - python3-rclcpp     # ROS2 C++ client library (optional)
  - ros2-ament-cmake   # Build system
```

#### **Simulation & Physics**
```yaml
gazebo-classic-11:     # Gazebo 11 (standard with ROS2 Humble on Ubuntu 22.04)
  - gazebo              # Core engine
  - gazebo-plugin-base  # Plugin system
  - ros-humble-gazebo-ros-pkgs    # ROS2 ↔ Gazebo bridge
  - gazebo-dev
  - libsdl-image1.2-dev # SDL support for Gazebo GUI
```

#### **PX4 & Autopilot (Phase 1c & Phase 2 Only)**
```yaml
px4-autopilot:         # PX4 firmware (stable or main branch, built locally for SITL)
  - build-essential    # Compiler toolchain
  - cmake              # Build system
  - git                # Version control
  - python3-pip        # Python package manager
  - python3-toml       # TOML config parsing
  - libopencv-dev      # Computer vision library (PX4 build dependency)
  - libceres-dev       # Optimization library (EKF2)
  - protobuf-compiler  # Protocol buffer compiler
  - libgtest-dev       # Google Test framework
  - gazebo-plugin-base # Gazebo plugins for PX4-SITL
```

#### **MAVLink Protocol (Phase 1c & Phase 2)**
```yaml
pymavlink:             # MAVLink protocol in Python
  - mavlink             # MAVLink message definitions (C library, optional)
```

#### **Python Libraries**
```yaml
scientific-computing:
  - numpy>=1.22        # Numerical operations
  - scipy>=1.8         # Advanced math (quaternion handling, optimization)
  - sympy              # Symbolic math (verification of consensus algorithms)

communication-protocols:
  - pymavlink>=2.4.20  # MAVLink protocol encoding/decoding

visualization:
  - matplotlib>=3.5    # Plotting
  - plotly>=5.0        # Interactive plots (optional)
  - pandas>=1.3        # Data analysis, CSV logging

development:
  - pytest>=7.0        # Unit testing
  - pytest-asyncio     # Async test support (for ROS2)
  - black              # Code formatting
  - pylint             # Linting
```

#### **Hardware Integration (Phase 2 Only)**
```yaml
crazyflie:             # (if using Crazyflie platform)
  - crazyflie-lib-python
  - cflib

codrone:               # (if using CoDrone EDU platform)
  - codrone-edu

pymavlink:             # (if using MAVLink-based drones)
  - pymavlink>=2.4.20  # Already included above
```

---

### **Requirements File Structure**

#### `apt_dependencies.txt` (System packages for Ubuntu 22.04)
```
# ==================== ROS2 Core ====================
ros-humble-desktop
ros-humble-geometry2
ros-humble-sensor-msgs
ros-humble-std-msgs
ros-humble-gazebo-ros-pkgs
ros-humble-gazebo-plugins

# ==================== Development Tools ====================
build-essential
cmake
git
python3-dev
python3-pip
python3-colcon-common-extensions

# ==================== Gazebo 11 & Simulation ====================
gazebo
gazebo-plugin-base
gazebo-plugins
gazebo-dev
libsdl-image1.2-dev

# ==================== PX4 SITL (Phase 1c & Phase 2) ====================
# Note: Install after downloading PX4 source
# (see Phase 1c PX4 bridge setup steps below)
python3-toml
libopencv-dev
libceres-dev
protobuf-compiler
libgtest-dev
```

#### `requirements.txt` (Python dependencies)
```
# ROS2 Core (Ubuntu 22.04 apt packages, but listed for reference)
rclpy==0.9.7

# Sensor & Geometry Messages
sensor-msgs==0.1.1
geometry-msgs==0.1.1
std-msgs==0.1.1

# Communication Protocols
pymavlink==2.4.20

# Scientific Computing
numpy>=1.22
scipy>=1.8
sympy>=1.12

# Visualization & Analysis
matplotlib>=3.5
plotly>=5.0
pandas>=1.3

# Development & Testing
pytest>=7.0
pytest-asyncio>=0.21
black==23.1
pylint>=2.16
```

---

## Phase 1: Software Module Development (Simulation + Hybrid PX4)

### **Phase 1a: Foundation (Weeks 7-8) — Gazebo Native**

**Step 1: Environment Setup on Ubuntu 22.04**
- Fresh Ubuntu 22.04 LTS install (or verify existing)
- Install ROS2 Humble via apt (standard Ubuntu 22.04 support)
- Install Gazebo 11 + gazebo-ros-pkgs (via apt)
- Create project git repository
- *Parallel with Step 1:* Install Python dependencies (`pip install -r requirements.txt`)
- **Note:** DO NOT install PX4 yet (deferred to Phase 1c)

**Step 2: Module Skeleton + Gazebo Native Config**
- Create module files: `swarm_coordinator.py`, `drone_controller.py`, `gazebo_bridge.py`, etc. (stub implementations)
- Define custom ROS2 message types: `DroneState.msg`, `SwarmCommand.msg`
- Set up CMakeLists.txt and package.xml for ROS2 build
- Create `config/swarm_config.yaml` (drone definitions, formation type, PID gains)
- **Create `config/mavlink_config.yaml` template** (for Phase 1c integration)
- Verify all modules import without errors

**Step 3: Gazebo Environment Setup**
- Create Gazebo SDF model files for 4 quadrotor drones (use iris.sdf as base, simplified physics)
- Create Gazebo world file (empty arena, gravity, physics engine settings)
- Verify Gazebo spawns drones without crashes

**Verification:**
- ✅ `python3 -m pytest tests/test_imports.py` (all modules importable)
- ✅ `ros2 pkg list | grep sentinel` (ROS2 sees package)
- ✅ `gazebo <world_file>` (Gazebo GUI launches, 4 drones spawn, physics stable)
- ✅ `python3 -c "import yaml; yaml.safe_load(open('config/swarm_config.yaml'))"` (config parses)

---

### **Phase 1b: Core Algorithm + Gazebo Native Integration (Weeks 9-10)**

**Step 4: Math Utilities**
- Implement quaternion ↔ Euler conversions
- Implement consensus algorithm for 4-5 drones (weighted averaging formation)
- Implement PID controller with saturation
- Implement velocity geometry helpers
- Add comprehensive unit tests

**Step 5: Communication Layer (ROS2 only, MAVLink stub)**
- Implement `SwarmPublisher`, `SwarmSubscriber` classes
- Implement `SwarmMessageBroker` (aggregates drone state)
- Implement QoS policy support
- Add latency monitoring
- **Stub out `MAVLinkEncoder`, `MAVLinkDecoder` (will implement in Phase 1c)**

**Step 6: Swarm Coordinator (Core Algorithm)**
- Implement consensus-based formation control
- Drone failure detection (timeout → mark as lost)
- Graceful degradation (recompute formation without failed drone)
- State management (all drone positions, velocities, health)
- 50 Hz main loop
- Unit tests for consensus + failure scenarios

**Step 7: Gazebo Bridge (Native Physics)**
- Subscribe to Gazebo drone poses
- Publish ROS2 telemetry topics (pose, velocity, simulated IMU)
- Receive ROS2 velocity commands → apply to Gazebo physics (via forces/torques)
- Time sync between ROS2 and Gazebo
- Logging/replay capability

**Step 8: Drone Controller + Mission Planner (Gazebo Native)**
- Implement `drone_controller.py` (parse Gazebo telemetry via ROS2)
- Implement state machine (DISARMED → ARMED → OFFBOARD → LANDED)
- Implement `mission_planner.py` (takeoff → formation → hold → land)
- Integration with gazebo_bridge

**Step 9: Swarm Monitor**
- Terminal dashboard (drone positions, formation error, battery, health)
- CSV logging of telemetry
- Real-time matplotlib plots
- Replay capability

**Verification:**
- ✅ `pytest tests/test_math_utilities.py -v` (all math tests pass)
- ✅ `pytest tests/test_consensus_algorithm.py` (formation without failures, with drone loss)
- ✅ Gazebo + ROS2: launch 4 drones, verify pose/velocity publishing at 50 Hz
- ✅ `ros2 run sentinel swarm_coordinator` (runs without errors, processes drone state)
- ✅ Formation maintained within 1m error in Gazebo native simulation

---

### **Phase 1c: PX4-ROS2 Bridge Integration (Weeks 11-12) — Add Realistic Autopilot**

**Step 10: PX4 SITL Setup**
- Download PX4 autopilot source code (stable branch)
- Build PX4 for SITL (Software In The Loop) mode on Ubuntu 22.04
  - Requires: `build-essential`, `cmake`, `python3-toml`, `libopencv-dev`, `libceres-dev`, `protobuf-compiler`, `libgtest-dev`
- Verify single PX4-SITL instance launches in Gazebo
- Configure UDP ports for 4-5 PX4 instances (14540-14544)

**Step 11: MAVLink Protocol Integration**
- Implement `MAVLinkEncoder` in `communication_layer.py` (ROS2 → MAVLink packets)
  - Encode: velocity commands → `SET_POSITION_TARGET_LOCAL_NED`
  - Encode: mission commands → `SET_POSITION_TARGET_GLOBAL_INT` (future)
- Implement `MAVLinkDecoder` in `communication_layer.py` (MAVLink packets → ROS2)
  - Decode: `LOCAL_POSITION_NED` → `/drones/drone_[i]/pose`
  - Decode: `ATTITUDE` → `/drones/drone_[i]/attitude`
  - Decode: `SYSTEM_TIME` → time sync
- Implement `MAVLinkRouter` (route messages by system ID to correct drone)
- Unit tests for MAVLink encoding/decoding + message integrity

**Step 12: PX4-ROS2 Bridge Module**
- Implement `px4_ros2_bridge.py` (new module)
  - Launch 4-5 PX4-SITL instances (child processes, system IDs 1-5)
  - Manage UDP sockets (one per drone) for MAVLink communication
  - Subscribe to ROS2 velocity commands → encode MAVLink → send to PX4
  - Receive MAVLink telemetry from PX4 → publish to ROS2 topics
  - Heartbeat monitoring (detect PX4 crashes)
  - PX4 parameter tuning interface (gains, limits)
- Create/update `config/px4_params.yaml` (PX4 gains, limits, failsafe thresholds)
- Integration tests: single PX4-SITL with ROS2 control

**Step 13: Swarm Coordinator Adapter (Transparent MAVLink Support)**
- Update `drone_controller.py` to support both Gazebo native AND MAVLink inputs
  - Check `config/mavlink_config.yaml` to determine mode
  - Gazebo native: telemetry from ROS2 topics directly
  - PX4 bridge: telemetry from `px4_ros2_bridge.py` (already published as ROS2 topics, so coordinator unchanged)
- No changes needed to `swarm_coordinator.py` (consumes ROS2 topics regardless of source)

**Step 14: End-to-End PX4-ROS2-Gazebo Test**
- Launch Gazebo with 4-drone world
- Launch 4-5 PX4-SITL instances (via `px4_ros2_bridge.py`)
- Launch swarm_coordinator + drone_controller (×4) + mission_planner + monitor
- Verify:
  - Autonomous takeoff via PX4 offboard mode
  - Formation maintained (<1m error) for 60+ seconds
  - Drone loss recovery (graceful degradation)
  - Mission completes in <2 minutes
  - PX4 telemetry correctly parsed and logged

**Verification (Phase 1c):**
- ✅ Single PX4-SITL spawns and responds to MAVLink commands
- ✅ MAVLink encoder/decoder unit tests pass (no corruption)
- ✅ 4 PX4-SITL instances launch concurrently, receive heartbeats
- ✅ ROS2 velocity commands → MAVLink → PX4 → Gazebo physics (latency <50ms)
- ✅ PX4 LOCAL_POSITION_NED → MAVLink → ROS2 topics → coordinator
- ✅ Full swarm autonomous mission in PX4-ROS2-Gazebo (realistic autopilot)
- ✅ Formation error <1m, mission <2 minutes, graceful degradation on drone loss
- ✅ Telemetry logged; replay works

---

## Phase 2: Hardware Integration (Post-Simulation, Weeks 13-18)

**Step 11: Hardware Selection & Porting**
- Decision point: Crazyflie? CoDrone? Custom quadcopter?
- Write hardware abstraction layer in `drone_controller.py`
- Port PX4 telemetry parsing to hardware API

**Step 12: Real-World Testing**
- Test single drone first (existing simple_drone_control pattern)
- Test two-drone formation (expand two_drone_simple pattern)
- Stress-test swarm coordinator with real latency
- PID tuning on real drones

**Step 13: Deployment & Competition Prep**
- Integration with real mission planning (payload, obstacles)
- Emergency failsafe procedures
- Thermal/battery stress testing

---

## Critical Files & Modules to Create

| File | Purpose | Phase | Dependencies |
|------|---------|-------|--------------|
| [swarm_core/swarm_coordinator.py](swarm_core/swarm_coordinator.py) | Formation algorithm, 50 Hz loop | 1b | `communication_layer.py`, `math_utilities.py` |
| [swarm_core/drone_controller.py](swarm_core/drone_controller.py) | Per-drone telemetry & control | 1b | `communication_layer.py`, `math_utilities.py` |
| [swarm_core/mission_planner.py](swarm_core/mission_planner.py) | Mission state machine | 1b | `swarm_coordinator.py`, `communication_layer.py` |
| [swarm_core/communication_layer.py](swarm_core/communication_layer.py) | ROS2 + MAVLink abstractions | 1b/1c | `rclpy`, `pymavlink` |
| [swarm_core/math_utilities.py](swarm_core/math_utilities.py) | Kinematics, PID, consensus | 1b | `numpy`, `scipy` |
| [swarm_core/gazebo_bridge.py](swarm_core/gazebo_bridge.py) | Gazebo native ↔ ROS2 | 1a-1b | `gazebo_ros`, `numpy` |
| **[swarm_core/px4_ros2_bridge.py](swarm_core/px4_ros2_bridge.py)** | **PX4 SITL + ROS2 + MAVLink** | **1c** | **`pymavlink`, `communication_layer.py`, `socket`** |
| [swarm_core/swarm_monitor.py](swarm_core/swarm_monitor.py) | Visualization & logging | 1b | `matplotlib`, `pandas` |
| [config/swarm_config.yaml](config/swarm_config.yaml) | Formation & drone definitions | 1a | — |
| **[config/mavlink_config.yaml](config/mavlink_config.yaml)** | **MAVLink routing & system IDs** | **1c** | — |
| [config/px4_params.yaml](config/px4_params.yaml) | PX4 tuning (Phase 1c+) | 1c | — |
| [launch/swarm_sim_gazebo_native.launch.py](launch/swarm_sim_gazebo_native.launch.py) | ROS2 launch file (Gazebo native, Phase 1a-1b) | 1b | — |
| **[launch/swarm_sim_px4_bridge.launch.py](launch/swarm_sim_px4_bridge.launch.py)** | **ROS2 launch file (PX4-ROS2-Gazebo, Phase 1c)** | **1c** | — |
| [tests/test_*.py](tests/) | Unit & integration tests | 1a+ | `pytest` |

---

---

## Verification Strategy

### **Phase 1a Verification (Weeks 7-8) — Gazebo Native Setup**
- ✅ Ubuntu 22.04 with ROS2 Humble installed
- ✅ Gazebo 11 launches without errors
- ✅ All modules import without errors
- ✅ Config YAML loads and validates
- ✅ ROS2 package recognized (`ros2 pkg list`)
- ✅ Gazebo SDF models spawn (4 drones, physics stable)

### **Phase 1b Verification (Weeks 9-10) — Gazebo Native Algorithm**
- ✅ Math unit tests pass (quaternions, consensus, PID)
- ✅ Communication layer pub/sub works with mock nodes
- ✅ Consensus algorithm handles drone loss gracefully
- ✅ 50 Hz coordinator loop maintains timing (<5ms jitter)
- ✅ Gazebo bridge reads drone poses at 50 Hz, publishes to ROS2
- ✅ ROS2 velocity commands applied to Gazebo physics (visible drone acceleration)
- ✅ Full swarm autonomous takeoff without operator input (Gazebo native)
- ✅ Formation maintained within 1m error for 60+ seconds
- ✅ Graceful landing on command
- ✅ Drone loss: swarm reformats, continues mission
- ✅ Mission completes in <2 minutes
- ✅ Telemetry logged (CSV), replay works

### **Phase 1c Verification (Weeks 11-12) — PX4-ROS2 Bridge**
- ✅ PX4 SITL builds successfully on Ubuntu 22.04
- ✅ Single PX4-SITL launches, responds to heartbeat
- ✅ MAVLink encoder/decoder unit tests pass (no corruption)
- ✅ 4 PX4-SITL instances launch concurrently (system IDs 1-5, UDP ports 14540-14544)
- ✅ ROS2 velocity commands → MAVLink SET_POSITION_TARGET_LOCAL_NED → PX4 (latency <50ms)
- ✅ PX4 LOCAL_POSITION_NED → MAVLink → ROS2 topics → coordinator
- ✅ Full swarm autonomous mission (PX4-ROS2-Gazebo, realistic autopilot)
  - Formation error <1m, mission <2 minutes
  - Graceful degradation on drone loss
- ✅ Telemetry logged, replay works
- ✅ PX4 parameter tuning interface functional (gains, limits configurable)

### **Phase 2 Verification (Weeks 13-18) — Hardware**
- ✅ Single real drone controlled via drone_controller.py
- ✅ Two-drone formation on real hardware
- ✅ Full 4-5 drone swarm tested
- ✅ PID gains tuned for real hardware dynamics
- ✅ Communication latency < 100ms (ROS2 DDS + MAVLink)
- ✅ Battery/thermal performance validated
- ✅ Emergency failsafe procedures tested

---

## Decisions & Scope

**Included:**
- **Ubuntu 22.04 LTS** (official ROS2 Humble standard; long-term support)
- **Hybrid simulation approach:** Gazebo native (Phase 1a-1b) → PX4-ROS2 bridge (Phase 1c)
- **MAVLink protocol** (Phase 1c+): Full implementation for autopilot communication
- **Distributed (not centralized) swarm coordination** → Resilient to single drone failure
- **Consensus-based formation** → No single point of failure
- **Velocity control mode** → More robust than position commands
- **Python primary** → Fast prototyping; sufficient for 50 Hz control
- **Modular architecture** → Each module independently testable
- **Hardware abstraction from day 1** → Flexibility for Crazyflie, CoDrone, or custom
- **4-5 drones scalable architecture**
- **CSV logging & replay capability**
- **Graceful degradation on drone failure**
- **<2 minute mission constraint**

**Deliberately Excluded (Phase 1):**
- Obstacle avoidance (can add with collision detection later)
- Advanced AI/ML algorithms (keep deterministic for competition)
- GCS (Ground Control Station) web UI (optional for Phase 2)
- PX4 in Phase 1a-1b (added in Phase 1c after algorithm validation)
- Multi-platform hardware abstraction (Phase 1c: separate per platform in Phase 2)

**Architecture Decisions:**
- **Hybrid simulation:** Gazebo native first (fast prototyping/debugging) → PX4-ROS2 bridge (realistic validation)
- **No central leader:** Consensus ensures one drone failure ≠ cascade failure
- **ROS2 DDS:** Multi-machine ready; standard in robotics
- **MAVLink for hardware:** Full protocol implementation (Phase 1c bridge → hardware transition)
- **50 Hz control loop:** Sufficient for quadrotor dynamics
- **YAML config:** Human-readable formation, PID gains, MAVLink routing
- **Modular design:** Each module independently testable (unit tests first)
- **Deferred PX4:** Algorithms validated in Phase 1b with Gazebo native before adding autopilot complexity

---

## Further Considerations

1. **Hybrid PX4 Strategy (Validated):**
   - **Phase 1a-1b:** Gazebo native physics for rapid algorithm prototyping (no PX4 overhead)
   - **Phase 1c:** Add realistic PX4-ROS2 bridge for autopilot validation before hardware
   - **Phase 2:** Transition to real hardware with proven algorithms
   - **Benefit:** Faster iteration cycles in Phase 1b; realistic autopilot testing in Phase 1c; proven algorithm transfer to Phase 2

2. **MAVLink Implementation (Critical for Hardware Transition):**
   - Full MAVLink protocol in Phase 1c enables direct hardware integration in Phase 2
   - 8 core messages (heartbeat, attitude, local position, system time, command ack, etc.) sufficient for swarm
   - Scaling to larger swarms (N > 5) requires message optimization (batch position updates, etc.)
   - **Recommendation:** Test MAVLink routing with 5 drones in Phase 1c; monitor message latency (<50ms target)

3. **Hardware Platform Decision (For Phase 2):**
   - **Option A:** Crazyflie 2.1 (well-documented ROS2 support, small, <100g, ~$150/unit, MAVLink-compatible)
   - **Option B:** CoDrone EDU (Python-friendly, Python API, ~$100/unit, no native MAVLink)
   - **Option C:** Custom quadcopter + PX4 (most flexibility, highest cost/complexity)
   - **Recommendation:** Design `drone_controller.py` abstraction in Phase 1b; defer platform choice to phase boundary (week 13) when hardware budget confirmed. Crazyflie recommended for ease of integration with ROS2 + MAVLink.

4. **Ubuntu 22.04 Verification (Immediate Action in Week 7):**
   - Standard LTS with excellent ROS2 Humble support
   - Gazebo 11 available via default apt
   - PX4 builds without issues (tested)
   - **Action:** Run Phase 1a setup immediately; report any system-level issues
   - Monitor: `cmake --version`, `python3 --version`, compiler compatibility

5. **Competition Requirements (To Be Clarified):**
   - Autonomous takeoff required? (assumed yes → coded in mission_planner.py)
   - Communication loss tolerance? (assumed 5s recovery per docs → timeout in drone_controller.py)
   - Formation geometry specifics? (assumes flexible, but affects mission_planner.py)
   - Swarm size fixed or flexible? (plan targets 4-5, scalable to N)
   - Safety requirements (geofence, emergency stop, battery thresholds)? (affects failsafe logic)
