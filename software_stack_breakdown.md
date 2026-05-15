# Autonomous Swarm Drone: Complete Software & System Stack
## What You'll Actually Code and Use (Excluding Hardware Assembly)

---

## The Stack at a Glance

Your complete technology stack (no hardware assembly work):

```
┌─────────────────────────────────────────────────────┐
│  YOUR CODE (Python/C++)                             │
│  ├─ Formation Control Algorithm                     │
│  ├─ Swarm Coordination Logic                        │
│  └─ Mission Planning                                │
└────────────────┬────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────┐
│  ROS 2 HUMBLE (Middleware)                          │
│  ├─ Pub/Sub messaging (DDS)                         │
│  ├─ Topic management                                │
│  ├─ Service calls                                   │
│  └─ Parameter server                                │
└────────────────┬────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────┐
│  PX4-ROS 2 BRIDGE                                   │
│  ├─ uORB to ROS 2 message translation               │
│  ├─ Offboard control enablement                     │
│  └─ Telemetry streaming                             │
└────────────────┬────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────┐
│  PX4 AUTOPILOT (Flight Control)                     │
│  ├─ Sensor fusion (IMU, GPS, barometer)             │
│  ├─ Attitude stabilization (gyro feedback)          │
│  ├─ Motor control loops                             │
│  ├─ Flight modes (offboard, position hold, etc)     │
│  └─ Safety monitoring (battery, failsafe)           │
└────────────────┬────────────────────────────────────┘
                 │
     ┌───────────┴───────────┬───────────┬─────────┐
     │                       │           │         │
┌────▼──┐  ┌────▼──┐  ┌────▼──┐  ┌───▼──┐  ...  
│ Drone │  │ Drone │  │ Drone │  │ Drone│      
│  1    │  │  2    │  │  3    │  │  4  │      
└───────┘  └───────┘  └───────┘  └─────┘      

TESTING/SIMULATION ENVIRONMENT:
┌─────────────────────────────────────┐
│  GAZEBO (3D Physics Simulator)       │
│  ├─ Physics engine (realistic flight)│
│  ├─ Sensor simulation (GPS, IMU)     │
│  └─ Virtual environment              │
└─────────────────────────────────────┘
```

---

## Layer 1: YOUR CODE (What You Write)

### Language
**Python** (primary) with optional **C++** for performance-critical sections

Why Python:
- Rapid prototyping (ideal for research phase)
- ROS 2 has excellent Python support
- Easier debugging and testing
- Good enough for swarm coordination (50-100Hz is the requirement, Python handles it)

Why C++ (optional later):
- If your control loop needs to run at 200Hz+
- If profiling shows Python is too slow
- For production-level robustness
- Not needed for initial competition prototype

### What You'll Write

**1. Swarm Coordination Node**
```python
# Main ROS 2 node that runs the swarm algorithm
class SwarmCoordinator(Node):
    def __init__(self):
        # Subscribe to all drone positions
        # Subscribe to mission parameters
        # Publish velocity commands to each drone
        
    def formation_control_loop(self):
        # Your actual swarm algorithm runs here
        # Called 50 times per second
        # Input: positions of all drones
        # Output: velocity commands for each drone
```

**File**: `swarm_coordinator.py` (probably 200-300 lines)

**2. Individual Drone Controller Nodes**
```python
# One per drone - handles drone-specific logic
class DroneController(Node):
    def __init__(self, drone_id):
        # Subscribe to MY velocity commands
        # Subscribe to MY position
        # Subscribe to MY sensor data
        
    def command_processing_loop(self):
        # Convert high-level commands to PX4 messages
        # Monitor drone health (battery, GPS quality)
        # Handle emergency landing
```

**File**: `drone_controller.py` (probably 150-200 lines, runs once per drone)

**3. Mission Planner**
```python
# High-level mission orchestration
class MissionPlanner(Node):
    def __init__(self):
        # Define competition mission
        # Manage overall state (takeoff → formation → mission → landing)
        
    def execute_mission(self):
        # Step 1: Arm all drones
        # Step 2: Takeoff in formation
        # Step 3: Execute formation movement
        # Step 4: Handle any drone failures
        # Step 5: Land all drones
```

**File**: `mission_planner.py` (probably 100-150 lines)

**4. Ground Control Station (GCS) Monitor**
```python
# Visualization and debugging tool
class GCSMonitor(Node):
    def __init__(self):
        # Subscribe to all telemetry
        
    def display_status(self):
        # Show current position of all drones
        # Show battery levels
        # Show communication quality
        # Detect and alert on failures
```

**File**: `gcs_monitor.py` (probably 100-150 lines)

**5. Configuration Files (Python reads these)**
```yaml
# formation_config.yaml - defines formation shape
# drone_params.yaml - individual drone PID tuning
# mission_config.yaml - mission definition
```

**Total Code You Write**: ~1000-1500 lines of Python
**Time to Write**: 6-8 weeks (weeks 9-16 of your timeline)
**Complexity**: Intermediate (not entry-level, not advanced)

---

## Layer 2: ROS 2 HUMBLE (Middleware)

### What It Is
ROS 2 is the communication backbone. It handles all message passing between your code and the flight controllers.

### What You Need from ROS 2

**1. Pub/Sub Messaging (Publisher/Subscriber)**
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

This is how your swarm algorithm talks to each drone. Drone 1 publishes its position; your algorithm subscribes. Your algorithm publishes desired velocity; Drone 1 subscribes.

**2. Message Types**
ROS 2 provides standard message types:
- `geometry_msgs/Point` - position (x, y, z)
- `geometry_msgs/Vector3` - velocity or acceleration
- `sensor_msgs/Image` - camera images (if using vision)
- `std_msgs/Float32` - single floating point values
- Plus hundreds more

You'll mostly use pre-built types. Sometimes you create custom messages for drone-specific data.

**3. Nodes**
A "node" is a single running program. Your swarm system will have:
- 1 SwarmCoordinator node (master control)
- 4-5 DroneController nodes (one per drone)
- 1 MissionPlanner node
- 1-2 visualization/monitoring nodes

Each runs independently. They communicate only through ROS 2 topics. This decoupling is powerful.

**4. Parameters Server**
ROS 2 has a central parameter store:
```python
# Set a PID gain parameter
self.declare_parameter('pid.kp', 0.5)

# Change it at runtime without recompiling
ros2 param set /drone_controller pid.kp 0.7

# Read it in your code
kp = self.get_parameter('pid.kp').value
```

This lets you tune your system without recompiling.

**5. Namespaces**
ROS 2 isolates drone topics:
```
/drone1/position
/drone1/velocity_command
/drone1/battery_level
/drone1/gps_quality

/drone2/position
/drone2/velocity_command
... and so on
```

This prevents conflicts when you have multiple drones.

### You Don't Write ROS 2

ROS 2 is already written. You just **use** it. You call ROS 2 functions from Python to create nodes, publish messages, and subscribe to topics. Think of it like a library that handles all the networking and message routing for you.

---

## Layer 3: PX4-ROS 2 BRIDGE

### What It Is
The bridge translates between your ROS 2 world and the PX4 world.

**PX4 uses "uORB" messaging** (internal to PX4, not network-compatible).  
**ROS 2 uses "DDS" messaging** (network protocol, works on WiFi/serial).

The bridge sits in the middle:

```
Your Python Code
    ↓ (publishes /drone1/velocity_command as geometry_msgs/Vector3)
ROS 2 Middleware (DDS)
    ↓ (converts to UDP packets)
Network (WiFi or USB serial)
    ↓
PX4 ROS 2 Bridge (runs on flight controller)
    ↓ (converts ROS 2 message to PX4 uORB message)
PX4 Core (reads TrajectorySetpoint uORB message)
    ↓ (computes motor commands)
Motors + ESCs
    ↓
Drone moves
```

### Key Messages You'll Use

**Incoming (from drone to your code)**:
- `VehicleOdometry` - current position and velocity
- `VehicleStatus` - armed state, flight mode, battery level
- `SensorCombined` - raw sensor data (IMU, pressure, etc.)

**Outgoing (from your code to drone)**:
- `OffboardControlMode` - tell PX4 to accept external commands
- `TrajectorySetpoint` - desired position/velocity
- `VehicleCommand` - arm/disarm, mode switches

### You Don't Write the Bridge

The bridge is pre-made. It's part of PX4. You just need to understand what messages exist and use them correctly.

### In Simulation (Gazebo)

When testing in simulation, the bridge still exists, but everything runs on your laptop:
- Your Python code on localhost
- ROS 2 middleware on localhost
- PX4 SITL (software-in-the-loop) on localhost
- Gazebo simulator on localhost

All communication is via localhost networking. Same code works on real drones later because the messages are identical.

---

## Layer 4: PX4 AUTOPILOT

### What It Is
PX4 is flight control software. It reads sensors (GPS, IMU, barometer) and commands motors to achieve stable flight.

### What PX4 Does (You Don't Code This)

```
Loop running at 50-100 Hz:

1. Read sensor data
   ├─ IMU: acceleration, rotation rate
   ├─ Magnetometer: heading
   ├─ Barometer: altitude
   ├─ GPS: absolute position
   └─ Optical flow (optional): relative motion

2. Estimate state
   ├─ Where am I? (sensor fusion)
   ├─ What's my velocity?
   ├─ What's my orientation?
   └─ What's my acceleration?

3. Read commanded setpoint (from ROS 2)
   ├─ Desired position
   ├─ Desired velocity
   └─ Desired orientation

4. Compute error
   ├─ Position error = desired - actual
   ├─ Velocity error = desired - actual
   └─ Attitude error = desired - actual

5. Run control loops
   ├─ Altitude PID controller
   ├─ Position X/Y PID controller
   ├─ Velocity PID controller
   ├─ Attitude (roll/pitch/yaw) controller
   └─ Motor mixing (convert desired forces to 4 motor commands)

6. Output motor commands (PWM signals)
   ├─ Motor 1: 1000-2000 microseconds
   ├─ Motor 2: 1000-2000 microseconds
   ├─ Motor 3: 1000-2000 microseconds
   └─ Motor 4: 1000-2000 microseconds

Loop repeats
```

You **don't write any of this**. PX4 handles it all. Your job is to:
1. Send it the desired position/velocity via ROS 2
2. Trust it to compute the motor commands
3. Monitor the sensors it provides back to you

### Flight Modes You'll Use

- **Offboard Mode**: "Listen to external computer (ROS 2) for commands"
- **Position Mode**: "Hold position, accept velocity commands from ROS 2"
- **Altitude Mode**: "Hold altitude, accept roll/pitch from ROS 2"
- **Auto Mode**: "Execute pre-loaded waypoints"
- **Stabilize Mode**: "Basic gyro stabilization, humans control attitude"

For your swarm, you'll use **Offboard Mode**: PX4 constantly listens to your ROS 2 velocity commands and flies accordingly.

### What You Configure in PX4 (Not Code, Just Parameters)

PX4 has ~1000 parameters you can tune:
- `MC_ACRO_R_MAX` - max roll rate
- `MC_ROLL_P` - roll PID proportional gain
- `EKF2_GPS_POS_X` - GPS antenna offset
- `SENS_BOARD_ROT` - sensor orientation
- etc.

You'll use QGroundControl (graphical tool) to set these. You don't write code to change them.

---

## Layer 5: Communication Protocol (MAVLink)

### What It Is
MAVLink is a binary serialization protocol. It converts messages into bytes that can be transmitted over radio or USB.

### Example
Your code publishes:
```python
velocity = Vector3(x=0.5, y=0.2, z=0.1)  # ROS 2 message
publisher.publish(velocity)
```

Behind the scenes:
```
ROS 2 (DDS) converts to bytes:
  0x03 0x00 0x40 0x3f 0xcd 0xcc 0x4c 0x3d ...
  
Transmitted over WiFi/USB to drone

Flight controller receives bytes and deserializes:
  → "This is a TrajectorySetpoint: vx=0.5, vy=0.2, vz=0.1"
```

You never see MAVLink directly. ROS 2 and PX4 handle it automatically.

---

## Development Tools (You'll Use These)

### 1. Ubuntu 22.04 LTS (Operating System)
Your development laptop runs Ubuntu. All the tools below are Linux-based.

**Why Linux?**
- ROS 2 is designed for Linux (Windows/Mac support is newer and less stable)
- All robotics tools assume Linux
- It's free and industry standard

**Option**: If you have Windows/Mac, use a VM (VirtualBox) or WSL2 (Windows Subsystem for Linux)

### 2. Terminal / Shell (bash)
You'll type commands constantly:
```bash
# Build your code
colcon build

# Launch your nodes
ros2 run swarm_coordinator drone_coordinator.py

# Check topics
ros2 topic list

# Debug a specific topic
ros2 topic echo /drone1/position
```

You'll need to be comfortable with command line. Not deep Linux knowledge, just basic commands.

### 3. Text Editor / IDE
Write Python code in:
- **VS Code** (recommended, lightweight, has ROS 2 extension)
- **PyCharm** (heavier, more features)
- **Vim** (if you're hardcore)

Most people use VS Code.

### 4. Git / GitHub (Version Control)
Keep your code in version control:
```bash
git init  # Start tracking
git add my_code.py
git commit -m "Implemented formation control algorithm"
git push origin main
```

Saves you if something breaks. Allows team collaboration.

Use GitHub (free) or GitLab.

### 5. ROS 2 Tools

**ros2 CLI commands**:
```bash
ros2 node list          # What nodes are running?
ros2 topic list         # What topics exist?
ros2 topic echo /topic  # Print live data from a topic
ros2 topic info /topic  # What's the message type?
ros2 param list         # What parameters are available?
ros2 param set /node param_name value  # Change a parameter
```

**rosbag** (recording tool):
```bash
ros2 bag record -a      # Record all topics to file
ros2 bag play file.db3  # Playback the recording
```

Invaluable for debugging. Record a flight, then replay it to understand what went wrong.

**rviz2** (visualization):
```bash
rviz2  # Opens 3D visualization
```

Shows drone positions, sensor data, planned trajectories. Helps you understand what your algorithm is doing.

**rqt** (graphing tool):
```bash
rqt_plot /drone1/position/x  # Graph position X over time
```

Plot sensor data or control signals.

### 6. QGroundControl (Ground Control Station)
Graphical app for managing drones:
- Parameter tuning (without writing code)
- Flight mode switching
- Telemetry monitoring
- Mission upload
- Pre-flight checks

Download from qgroundcontrol.com. You'll use this during hardware testing weeks 13-16.

### 7. PX4 Tools

**PX4 System Console** (inside PX4):
```bash
# In the PX4 console
status          # Drone status
param show      # Show current parameters
commander arm   # Arm the drone
listener odometry  # Listen to odometry messages
```

Access through serial connection or Gazebo console.

**PX4 SITL** (Software-In-The-Loop):
```bash
make px4_sitl gazebo-classic
```

Runs PX4 on your laptop instead of on hardware. Identical code works on real drones.

---

## Testing & Simulation Environment

### Gazebo (3D Physics Simulator)

Gazebo is where you develop and test everything before buying real drones.

```bash
# Start Gazebo with a single simulated drone
make px4_sitl gazebo-classic
```

What happens:
1. Gazebo opens a 3D window
2. PX4 SITL starts (running on your laptop, not on hardware)
3. ROS 2 bridge starts (translating between PX4 and ROS 2)
4. You can now launch your Python code to command the virtual drone

**In Gazebo, you can**:
- Crash drones without damage (just reset)
- Test edge cases (wind, GPS loss, motor failure)
- Run 10 test flights in 5 minutes (vs 50 minutes with real drones)
- Record everything for analysis

### Simulation Workflow

```
Week 9-12: Simulation
┌─────────────────────────────────────────┐
│ 1. Write formation control algorithm    │
│ 2. Test with 1 drone in Gazebo         │
│ 3. Test with 2 drones in Gazebo        │
│ 4. Test with 3-4 drones in Gazebo      │
│ 5. Test failure scenarios               │
│ 6. Tune PID parameters                 │
│ 7. Verify algorithm works perfectly    │
└─────────────────────────────────────────┘
       ↓ (when simulation works)
Week 13-16: Real Hardware
┌─────────────────────────────────────────┐
│ 1. Flash real drones with PX4 firmware │
│ 2. Calibrate sensors                   │
│ 3. Deploy code to real drone            │
│ 4. Test with 1 real drone              │
│ 5. Test with 2 real drones             │
│ 6. Adjust parameters for real-world    │
│ 7. Test full 4-drone swarm             │
└─────────────────────────────────────────┘
```

The key insight: your Python code is **identical** in both simulation and real hardware. Only the environment changes.

---

## Complete Dependency Tree

What depends on what:

```
Your Python Code
  ↓ imports
ROS 2 Python Client Library
  ↓ uses
ROS 2 Core (DDS middleware)
  ↓ sends messages to
PX4 ROS 2 Bridge
  ↓ communicates with
PX4 Autopilot
  ↓ controls
Flight Controller (Pixhawk, etc.)
  ↓ commands
Electronic Speed Controllers (ESCs)
  ↓ power
4x Brushless Motors
  ↓ spin
Propellers
  ↓ generate
Thrust
  ↓ results in
Flight
```

When testing in simulation, the chain is:

```
Your Python Code
  ↓ (same as above)
ROS 2 DDS Middleware (via localhost)
  ↓
PX4 SITL (on your laptop)
  ↓
Gazebo Physics Engine (on your laptop)
  ↓
Virtual Drone Model
  ↓
Visual display in Gazebo window
```

---

## What You Actually Install & Configure

### Initial Setup (Week 7-8: ~10 hours)

1. **Install Ubuntu 22.04** (if not already)
   - Command: Download ISO, create bootable USB
   - Time: 30 min
   - Difficulty: Easy

2. **Install ROS 2 Humble**
   - Command: `sudo apt install ros-humble-desktop-full`
   - Time: 10 min
   - Difficulty: Very Easy

3. **Install PX4 Autopilot** (source code)
   - Command: `git clone https://github.com/PX4/PX4-Autopilot.git`
   - Command: `cd PX4-Autopilot && bash ./Tools/setup/ubuntu.sh`
   - Command: `make px4_sitl`
   - Time: 1 hour (lots of downloading and compiling)
   - Difficulty: Easy (just follow instructions)

4. **Install Gazebo**
   - Command: `sudo apt install ros-humble-gazebo-ros`
   - Time: 10 min
   - Difficulty: Very Easy

5. **Install PX4-ROS 2 Bridge**
   - Command: `git clone https://github.com/PX4/px4_msgs.git`
   - Command: `colcon build --packages-select px4_msgs`
   - Time: 20 min
   - Difficulty: Easy

6. **Install QGroundControl**
   - Command: Download from qgroundcontrol.com, install like any app
   - Time: 10 min
   - Difficulty: Very Easy

7. **Install Code Editor (VS Code)**
   - Command: `sudo apt install code` (or download from Microsoft)
   - Time: 10 min
   - Difficulty: Very Easy

**Total Setup Time**: ~2-3 hours  
**Total Difficulty**: All "Easy" - no configuration required, just installing packages

### Verification (Week 8: ~1 hour)
```bash
# Run talker/listener demo
ros2 run demo_nodes_cpp listener &
ros2 run demo_nodes_cpp talker
# Should see "Hello World" messages printed

# Run PX4 + Gazebo
cd ~/PX4-Autopilot
make px4_sitl gazebo-classic
# Gazebo should open with a virtual drone model
```

---

## Summary: Your Complete Tech Stack

| Layer | Technology | Role | Language | You Code? |
|-------|-----------|------|----------|-----------|
| **Application** | Your Code | Swarm algorithm, mission planning | Python | **YES** |
| **Middleware** | ROS 2 Humble | Message passing, networking | (You use it) | No |
| **Bridge** | PX4-ROS 2 | Translate between ROS 2 and PX4 | (Pre-built) | No |
| **Flight Control** | PX4 Autopilot | Sensor fusion, motor control | C++ (pre-built) | No |
| **Simulator** | Gazebo | Physics simulation for testing | (Pre-built) | No |
| **Tools** | VS Code, Git, QGroundControl | Development, debugging, monitoring | (Tools) | No |
| **OS** | Ubuntu 22.04 | Everything runs on this | (OS) | No |

---

## What You DON'T Do

You don't:
- Build drones (hardware assembly is later, post-competition)
- Write PX4 flight control code (it's already written)
- Write ROS 2 framework code (it's a library you use)
- Write Linux kernel code
- Design circuit boards
- Tune motor ESCs (PX4 handles this)
- Configure WiFi protocols
- Write network drivers

You just:
- Write the **swarm coordination algorithm** (your algorithm in Python)
- Configure existing tools (ROS 2, PX4, Gazebo)
- Test and debug your algorithm
- Handle the integration between layers

---

## Time Breakdown

**Research Phase (Weeks 1-6): 90-120 hours**
- No coding yet, just learning
- Reading papers, watching lectures, understanding concepts

**Setup Phase (Weeks 7-8): 20 hours**
- Installing tools (3 hours)
- Verifying everything works (1 hour)
- Understanding how tools fit together (16 hours)

**Development Phase (Weeks 9-16): 200-240 hours**
- **Week 9**: Write single-drone controller (~30 lines → 50 lines code)
- **Week 10**: Write multi-drone communication (~100 lines new)
- **Week 11**: Write formation algorithm (~150 lines core, ~200 lines with error handling)
- **Week 12**: Add robustness (~100 lines for failsafes)
- **Weeks 13-16**: Hardware testing (mostly running existing code, tuning parameters)

**Total Code Written**: ~1000-1500 lines of Python

**Competition Prep (Weeks 17-18): 30-40 hours**
- Documentation (not code)
- Practice runs (testing existing code)
- Parameter tuning (using QGroundControl GUI, not writing code)

---

## The Hardware Assembly Part (Post-Competition)

Just for clarity, here's what happens after competition:

**Hardware Assembly (~4-6 weeks)**:
- If building from scratch: solder flight controller, motors, ESCs together
- Flash Pixhawk firmware (graphical tool, not coding)
- Calibrate sensors (using QGroundControl GUI)
- Tune ESC protocols (using QGroundControl GUI)

But that's after competition. For your 18-week timeline, you only write the coordination algorithm and test in simulation. Real hardware uses off-the-shelf commercial drones (Crazyflie, CoDrone EDU) where assembly is minimal (put batteries in, attach props, that's it).

---

## Final Architecture Diagram

What your system looks like:

```
┌────────────────────────────────────────────────────────┐
│                    YOUR LAPTOP                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │              YOUR PYTHON CODE                    │  │
│  │  ┌────────────────────────────────────────────┐  │  │
│  │  │  SwarmCoordinator                          │  │  │
│  │  │  ├─ Read drone positions                   │  │  │
│  │  │  ├─ Compute formation control commands     │  │  │
│  │  │  └─ Publish velocity commands              │  │  │
│  │  └────────────────────────────────────────────┘  │  │
│  │  ┌────────────────────────────────────────────┐  │  │
│  │  │  DroneControllers (4 instances)            │  │  │
│  │  │  ├─ Subscribe to coordination commands     │  │  │
│  │  │  ├─ Convert to PX4 messages                │  │  │
│  │  │  └─ Publish to PX4                         │  │  │
│  │  └────────────────────────────────────────────┘  │  │
│  └──────────────────────────────────────────────────┘  │
│  ┌──────────────────────────────────────────────────┐  │
│  │           ROS 2 MIDDLEWARE (DDS)                │  │
│  │  Topics, Publishers, Subscribers, Parameters  │  │
│  └──────────────────────────────────────────────────┘  │
│  ┌──────────────────────────────────────────────────┐  │
│  │      PX4 AUTOPILOT (via USB/WiFi)              │  │
│  │  ├─ Sensor fusion                              │  │
│  │  ├─ Control loops                              │  │
│  │  ├─ Motor commands                             │  │
│  │  └─ Telemetry                                  │  │
│  └──────────────────────────────────────────────────┘  │
└────────────────────────────────────────────────────────┘
         ↓ (WiFi or USB connection)
┌────────────────────────────────────────────────────────┐
│                  4-5 PHYSICAL DRONES                   │
│  Each drone has:                                       │
│  ├─ Flight controller (receives your code's commands) │
│  ├─ 4 motors with ESCs                                │
│  ├─ IMU, GPS, barometer                               │
│  ├─ WiFi/radio modem (communicates with laptop)      │
│  └─ Battery                                           │
└────────────────────────────────────────────────────────┘
```

Everything from "YOUR PYTHON CODE" to "ROS 2 MIDDLEWARE" runs on your laptop.

During Weeks 9-12 (simulation), PX4 also runs on your laptop, and Gazebo simulates the drones.

During Weeks 13-16 (hardware), PX4 runs on the flight controllers inside the real drones, and your code talks to them via WiFi.

---

## Next Steps for You

1. **Confirm you understand the stack**: Can you explain what each layer does without looking?
2. **Identify gaps**: Is there anything unclear?
3. **Plan your learning**: Which parts of this stack need deep understanding vs. surface understanding?

You now understand exactly what you're building: ~1000-1500 lines of Python coordinating multiple drones, using ROS 2 as the networking layer, commanding PX4 autopilot on each drone.

No hardware assembly until after competition. For now, it's pure software + simulation.

Make sense?
