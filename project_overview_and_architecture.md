# Project Overview & Architecture: 2–5 Autonomous Drone Swarm

> **CRITICAL NOTE:** Initial development will focus exclusively on a **quadrotor** platform. The architecture must remain **modular** so it can be implemented into any future system or link other drone types into the swarm.

---

## 1. Project Objectives & Core Configuration

### Drone Swarm Conditions

| Parameter | Specification |
|-----------|---------------|
| **Scale** | 2–5 drones |
| **Autonomy** | High-level individual drone autonomy |

### Hardware/Sensor Optimization (Alternative 1)

Because equipping every single drone with high-grade, expensive tech is budget-prohibitive, we will use a **heterogeneous sensor distribution**.

- **Example:** One drone carries advanced mapping sensors, while another carries high-res cameras.
- **Mechanism:** They will communicate and share data continuously to collaboratively map out an environment.
- **Constraint:** If this decentralized sensor method is selected, our **Drone Communication** layer must be absolutely optimized.

### Formations

Multi-drone geometric patterns.

### Technology Foundation Stack

| Layer | Choice |
|-------|--------|
| **Languages** | Python (primary for rapid development) → compiled/converted to C++ later for faster processing and deployment on the physical system |
| **Software ecosystem** | ROS2 + PX4 + Gazebo (`Gazebo` + `px4_sitl_multiple_run.sh`) + MAVLink |
| **Control package** | PX4 Swarm controller ROS2 package (supports Leader-Follower and Formation patterns; minimum 3+ drones required; currently available) |

### Swarm Algorithms Under Consideration

| Algorithm | Complexity | Operational Mechanism |
|-----------|------------|----------------------|
| **Leader-Follower** | Simplest | Drone 1 acts as the leader following a fixed flight path. Followers (Drones 2–5) maintain a constant geometric offset from it. |
| **Consensus Formation** | Sophisticated & robust *(target selection)* | All drones are equal nodes. No single point of leader failure. Each drone tracks its local neighbors' positions to maintain the global shape. |
| **Area Coverage** | Visual impact | Drones partition an environment into distinct search zones and sweep through them, maintaining a loose safety formation. |

---

## 2. Success Criteria & Competition Readiness

### Minimum Viable Swarm (MVS) Requirements

To be competitive, the swarm must autonomously handle the following phases and scenarios:

#### Autonomous Deployment

- All drones must successfully arm and take off **completely without human operator intervention**, handling minor GPS/sensor noise gracefully.

#### Formation Flying

- Successfully maintain a chosen formation (triangle, straight line, or custom shape) for a duration of **1+ minutes**.
- Keep the formation error (drift tolerance from perfect geometric shape) **under 1 meter**.

#### Graceful Degradation

- If a single drone drops communication for **5 seconds**, the remaining drones must continue safely without crashing.
- If one drone is totally removed or fails out of the swarm, the remaining drones must **dynamically adapt** their formation and complete the objective.

#### Mission Execution

- Complete a pre-planned waypoint sequence (e.g., move forward, bank turn, return to base) with **zero operator input**.
- Complete the entire mission in **under 2 minutes** due to strict battery constraints.

#### Safe Failure Modes

- If a critical error occurs, drones must execute **automated emergency landings** (avoiding people/structures).
- Eliminate any single point of failure capable of causing an immediate catastrophic crash of the whole swarm.

---

## 3. The 5-Layer Software Architecture

### Layer 1: Your Code (What You Write)

| Aspect | Detail |
|--------|--------|
| **Primary language** | Python — ideal for rapid prototyping, robust ROS2 support, fast debugging, and fully capable of maintaining the required **50–100 Hz** swarm coordination loops |
| **Secondary language** | C++ — optional; reserved for later if control loops must exceed 200 Hz, production profiling reveals bottlenecks, or for final hard real-time safety. **Unnecessary for the competition prototype.** |
| **Scope** | ~1000–1500 total lines of Python \| estimated dev time: **6–8 weeks** during weeks 9–16 |

#### Core Node Implementations

##### 1. Swarm Coordination Node (`swarm_coordinator.py`)

- **Size:** ~200–300 lines
- **Purpose:** Runs the primary swarm consensus/formation algorithm. Executes **50 times per second (50 Hz)**.

```python
# Main ROS 2 node that runs the swarm algorithm
class SwarmCoordinator(Node):
    def __init__(self):
        # Subscribe to all drone positions
        # Subscribe to mission parameters
        # Publish velocity commands to each drone
        pass

    def formation_control_loop(self):
        # Your actual swarm algorithm runs here
        # Called 50 times per second
        # Input: positions of all drones
        # Output: velocity commands for each drone
        pass
```

##### 2. Individual Drone Controller Nodes (`drone_controller.py`)

- **Size:** ~150–200 lines (runs as an independent instance per drone)
- **Purpose:** Manages drone-specific telemetry parsing, conversion, and health monitoring.

```python
# One per drone - handles drone-specific logic
class DroneController(Node):
    def __init__(self, drone_id):
        # Subscribe to MY velocity commands
        # Subscribe to MY position
        # Subscribe to MY sensor data
        pass

    def command_processing_loop(self):
        # Convert high-level commands to PX4 messages
        # Monitor drone health (battery, GPS quality)
        # Handle emergency landing
        pass
```

##### 3. Mission Planner Node (`mission_planner.py`)

- **Size:** ~100–150 lines
- **Purpose:** Manages high-level global state transitions.

```python
# High-level mission orchestration
class MissionPlanner(Node):
    def __init__(self):
        # Define competition mission
        # Manage overall state (takeoff → formation → mission → landing)
        pass

    def execute_mission(self):
        # Step 1: Arm all drones
        # Step 2: Takeoff in formation
        # Step 3: Execute formation movement
        # Step 4: Handle any drone failures
        # Step 5: Land all drones
        pass
```

##### 4. Ground Control Station Monitor Node (`gcs_monitor.py`)

- **Size:** ~100–150 lines
- **Purpose:** Real-time telemetry visualization, asset mapping, and failure alerts.

```python
# Visualization and debugging tool
class GCSMonitor(Node):
    def __init__(self):
        # Subscribe to all telemetry
        pass

    def display_status(self):
        # Show current position of all drones
        # Show battery levels
        # Show communication quality
        # Detect and alert on failures
        pass
```

##### 5. Configuration Files (YAML inputs parsed by nodes)

| File | Purpose |
|------|---------|
| `formation_config.yaml` | Sets coordinates and geometric layouts for shapes |
| `drone_params.yaml` | Stores unique PID flight tuning constants per drone |
| `mission_config.yaml` | Pre-defined flight path vectors and search zones |

---

### Layer 2: ROS2 Humble (Communication Middleware)

ROS2 acts as our networking backbone, managing decentralized message handling. We do not write ROS2; we call its client library APIs.

#### Core Capabilities Utilized

**Publisher/Subscriber framework** — used to feed velocity adjustments and share state coordinates across the swarm:

```python
# Your code publishes velocity commands
self.velocity_pub = self.create_publisher(
    Vector3,  # Message type
    '/drone1/velocity_command',  # Topic name
    10  # Queue size
)

# Your code subscribes to drone positions
self.position_sub = self.create_subscription(
    Point,  # Message type
    '/drone1/position',  # Topic name
    self.position_callback,
    10
)
```

**Standard message types:**

| Message | Use |
|---------|-----|
| `geometry_msgs/Point` | Tracks cartesian positions (x, y, z) |
| `geometry_msgs/Vector3` | Manages structural velocities/accelerations |
| `sensor_msgs/Image` | Streams camera optics data payload (if vision-equipped) |
| `std_msgs/Float32` | Handles generalized scalar variables |

**Decoupled nodes:** Individual execution blocks (`SwarmCoordinator`, `DroneController` × N, `MissionPlanner`) isolated cleanly and routed exclusively via topics.

**Dynamic parameter server** — modifies flight characteristics dynamically at runtime without recompiling source scripts:

```python
# Set a PID gain parameter
self.declare_parameter('pid.kp', 0.5)

# Change it at runtime without recompiling
# via terminal: ros2 param set /drone_controller pid.kp 0.7

# Read it in your code
kp = self.get_parameter('pid.kp').value
```

**Topic namespacing** — isolates unique telemetry routes to clear up cross-communication conflicts:

- `/drone1/position`, `/drone1/velocity_command`, `/drone1/battery_level`
- `/drone2/position`, `/drone2/velocity_command`, `/drone2/battery_level`

---

### Layer 3: PX4-ROS2 Bridge

Translates network-compatible DDS protocols (ROS2) to lightweight internal uORB micro-object messages (PX4).

#### Pipeline Flow

```
Python Application Code
  → geometry_msgs/Vector3
  → ROS2 DDS Middleware (Localhost/UDP)
  → WiFi / Serial Connection
  → PX4-ROS2 Bridge (FCU Hardware)
  → uORB TrajectorySetpoint
  → PX4 Core Autopilot
```

#### Essential Bridge Messages

| Direction | Messages |
|-----------|----------|
| **Telemetry (incoming)** | `VehicleOdometry` (state position/vector), `VehicleStatus` (arming state, flags), `SensorCombined` (raw inertial unit metrics) |
| **Control (outgoing)** | `OffboardControlMode` (engages external overrides), `TrajectorySetpoint` (target vectors), `VehicleCommand` (direct hardware utility toggles like arming/disarming) |

---

### Layer 4: PX4 Autopilot

The core flight safety loop running at **50–100 Hz** to stabilize the physical frame. We only configure its operational parameters using QGroundControl.

```
[PX4 Continuous Control Loop]
 │
 ├── 1. Read Raw Sensors (IMU, Mag, Baro, GPS, Optical Flow)
 ├── 2. State Estimation (Sensor Fusion Kalman filtering)
 ├── 3. Read Commanded Setpoint (Via ROS2 bridge Offboard Mode)
 ├── 4. Compute Error Matrix (Desired Vector - Actual Position Vector)
 ├── 5. Run Cascaded PID Controls (Altitude, Position, Velocity, Attitude loops)
 └── 6. Output Motor Signals (PWM updates to ESCs ranging 1000-2000 µs)
```

#### Flight Modes Utilized

| Mode | Role |
|------|------|
| **Offboard** | Overrides standard control; directly tracks incoming ROS2 velocity command arrays |
| **Position** | Stationary braking; locks 3D spatial points automatically when manual input stops |
| **Altitude** | Restricts Z-axis drift; leaves heading adjustments open |
| **Auto** | Executes standard localized path missions via pre-calculated waypoints |
| **Stabilize** | Fallback manual recovery leveling mode using internal gyros |

---

### Layer 5: Communication Protocol (MAVLink)

The underlying serialization standard packing structural language types into raw packed hex-streams over wireless channels.

**Example:**

`Vector3(x=0.5, y=0.2, z=0.1)` → DDS / MAVLink serialization → `0x03 0x00 0x40 0x3f 0xcd 0xcc ...` → hardware de-serialization → PX4 flight setpoint command.

---

## 4. Development & Utility Tools Reference

### Operating System & Core Environment

| Component | Choice |
|-----------|--------|
| **OS** | Ubuntu 22.04 LTS (industry standard for robotics development; native stable ROS2 testing) |
| **Alternative hosts** | VirtualBox VM or Windows Subsystem for Linux (WSL2) |
| **Code workspace** | VS Code (recommended), PyCharm, or Vim |
| **Version control** | Git via GitHub/GitLab |

### Essential Terminal Cheat-Sheet

```bash
# Build the current workspace packages
colcon build

# Source the setup script to overlay workspace variables
source install/setup.bash

# Spin up a specific node script manually
ros2 run swarm_coordinator drone_coordinator.py

# List out all active cluster topics
ros2 topic list

# Echo live topic data output streams directly into terminal
ros2 topic echo /drone1/position

# View exact formatting type requirement of a target topic
ros2 topic info /drone1/position

# View list of editable node properties
ros2 param list

# Modify a node parameter live during runtime
ros2 param set /node_name param_name value
```

### Analysis & Visualization Suites

| Tool | Purpose |
|------|---------|
| **rosbag2** | Logs flight streams for review (`ros2 bag record -a` / `ros2 bag play file.db3`) |
| **rviz2** | Real-time 3D spatial representations of trajectories and transforms |
| **rqt_plot** | 2D real-time line charts (e.g., `/drone1/position/x`) |
| **QGroundControl** | Sensor calibrations, physical hardware config, emergency diagnostics (weeks 13–16) |

---

## 5. Testing & Simulation Environment

All testing occurs within the **Gazebo** 3D physics simulator to safely evaluate algorithm performance before deploying to real physical hardware.

```bash
# Run PX4 Software-In-The-Loop (SITL) bundled with classic Gazebo simulation models
make px4_sitl gazebo-classic
```

### Project Roadmap & Execution Flow

#### Weeks 9–12: Simulation & Algorithm Design

```
┌───────────────────────────────────────────────────────────┐
│ 1. Build and test logic arrays for a single virtual drone │
│ 2. Verify dual-drone communication steps in Gazebo      │
│ 3. Scale up execution to 3-4 multi-drone models           │
│ 4. Inject artificial sensor faults, delays, and drops     │
│ 5. Tune cascade PID controllers until response error <1m  │
└─────────────────────────────┬─────────────────────────────┘
                              │ (Once simulation passes successfully)
                              ▼
```

#### Weeks 13–16: Physical Hardware Integration

```
┌───────────────────────────────────────────────────────────┐
│ 1. Flash official PX4 firmware directly to Pixhawk boards │
│ 2. Calibrate onboard compasses, IMUs, and power monitors  │
│ 3. Flash Python nodes to individual onboard companion PCs │
│ 4. Perform isolated outdoor safety flights with 1 drone   │
│ 5. Test coordinate matching loops with 2-drone frameworks │
│ 6. Launch the complete 4-drone autonomous swarm           │
└───────────────────────────────────────────────────────────┘
```

---

## 6. Full Operational Dependency Tree

### Simulation Execution Dependency Path

```
Your Python Node Script
  → ROS2 Client Library (rclpy)
  → ROS2 DDS Middleware (via Localhost Network)
  → PX4 SITL (Simulated Firmware Instance)
  → Gazebo Physics Engine
  → Virtual Drone Model Visualizer
```

### Real Hardware Execution Dependency Path

```
Your Python Node Script
  → ROS2 Client Library (rclpy)
  → ROS2 DDS Core Middleware
  → PX4 ROS2 Bridge Protocol
  → PX4 Autopilot Firmware
  → Flight Controller Unit Hardware (Pixhawk)
  → Electronic Speed Controllers (ESCs)
  → Brushless Motors
  → Propellers
  → Aerodynamic Flight
```
