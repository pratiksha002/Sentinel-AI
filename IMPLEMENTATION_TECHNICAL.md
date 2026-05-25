# Document 2: Implementation & Technical Details
## Building the System (Weeks 7-18)

---

## Phase 2: Environment Setup (Weeks 7-8)

### Installing the 5-Layer Stack

I learned that the stack has 5 distinct layers, and each needs to be installed and verified separately.

```
Layer 1: Your Algorithm (Python)       ← You write this
Layer 2: ROS 2 Humble (Middleware)     ← Install this
Layer 3: PX4-ROS 2 Bridge              ← Install this
Layer 4: PX4 Autopilot                 ← Install this
Layer 5: Hardware (Drones)             ← Buy this
```

### Layer 5 to 4: Hardware and PX4

**For competition**, I'm using commercial off-the-shelf drones:
- Crazyflie 2.1 (~$100 each) or
- CoDrone EDU (~$150 each)

These come with PX4 already pre-installed on the flight controller. I don't have to compile or flash anything to the drones. PX4 is just there, waiting to receive commands.

### Layer 4 to 3: PX4 to ROS 2 Bridge

The bridge translates between PX4's internal language (uORB) and ROS 2's language (DDS).

**Installation** (Terminal):
```bash
# Clone PX4 messages
cd ~/ros2_ws/src
git clone https://github.com/PX4/px4_msgs.git

# Build
cd ~/ros2_ws
colcon build --packages-select px4_msgs

# Verify
ros2 topic list | grep px4
```

This creates message types like `TrajectorySetpoint`, `OffboardControlMode` that I'll use in my code.

### Layer 3 to 2: ROS 2 Installation

**Installation** (Terminal):
```bash
# Add ROS repository
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | sudo apt-key add -
echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install
sudo apt update
sudo apt install ros-humble-desktop-full

# Add to bashrc
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc

# Verify
ros2 --version
```

### Layer 2 to 1: Setting Up Coding Environment

I created a workspace for my code:

```bash
# Create workspace
mkdir -p ~/swarm_ws/src
cd ~/swarm_ws

# Create Python package
ros2 pkg create --build-type ament_python swarm_coordinator

# Create subdirectories
mkdir -p swarm_coordinator/swarm_coordinator
mkdir -p swarm_coordinator/config
mkdir -p swarm_coordinator/launch
```

**Directory structure**:
```
swarm_ws/
├── src/
│   └── swarm_coordinator/
│       ├── swarm_coordinator/        (Python code)
│       │   ├── __init__.py
│       │   ├── simple_drone_control.py
│       │   ├── two_drone_simple.py
│       │   └── hello_drone.py
│       ├── config/                   (Configuration files)
│       │   └── drone_config.yaml
│       ├── launch/                   (Launch scripts)
│       │   └── swarm.launch.py
│       ├── setup.py
│       ├── package.xml
│       └── README.md
```

### Verification (Week 8)

I tested each layer:

**Test Layer 2 (ROS 2)**:
```bash
# Terminal 1
ros2 run demo_nodes_cpp listener

# Terminal 2
ros2 run demo_nodes_cpp talker

# Should see "Hello World" messages
```

**Test Layer 3 (PX4 messages)**:
```bash
ros2 topic list | grep px4
# Should see: /fmu/in/vehicle_command, /fmu/in/offboard_control_mode, etc.
```

**Test Layer 1+2 Together**:
```bash
# Run the hello_drone.py example (Layer 1)
python3 hello_drone.py

# In another terminal
ros2 topic pub /test_position geometry_msgs/Point "{x: 1.0, y: 2.0, z: 3.0}" --once

# Should print in first terminal
```

If all tests passed, I knew the layers were working together.

---

## The 5-Layer Architecture in Detail

Now I understand what runs where:

### Layer 1: Your Algorithm (Runs on your laptop)

```python
# This is what you write
class SwarmCoordinator(Node):
    def formation_control(self):
        # Read drone positions
        # Compute PID error
        # Send velocity commands
        # Repeat 50 times per second
```

**You control**:
- What algorithm runs
- How drones coordinate
- What parameters to tune

### Layer 2: ROS 2 Middleware (Runs on your laptop)

```
Your code publishes:
  Message: TrajectorySetpoint(vx=0.5, vy=0.2, vz=0)
  To topic: /drone1/setpoint
  ↓ (ROS 2 serializes to bytes)
  ↓ (sends via network)
  Arrives at: Drone 1 via WiFi
```

**You don't control this**, but you use it through API calls:
```python
self.publisher = self.create_publisher(TrajectorySetpoint, '/drone1/setpoint', 10)
self.publisher.publish(msg)
```

### Layer 3: PX4-ROS 2 Bridge (Runs on both laptop and drone)

On laptop side:
- Listens to ROS 2 messages
- Converts to PX4 format
- Sends to drone

On drone side:
- Receives PX4 format
- Converts to ROS 2 format
- Makes available to your code

**You don't write this**, it's pre-built. But understanding it helps:
- `ROS 2 TrajectorySetpoint` → `PX4 trajectory_setpoint uORB message`
- `PX4 vehicle_odometry uORB message` → `ROS 2 Odometry`

### Layer 4: PX4 Autopilot (Runs on drone flight controller)

```
Receives: velocity command (0.5, 0.2, 0) m/s
Does:
  1. Read sensors (IMU, GPS)
  2. Estimate current velocity
  3. Compute error: desired - actual
  4. Compute required attitude (roll, pitch)
  5. Convert to motor commands
  6. Send PWM to motors
Repeats: 50-100 times per second
```

**You don't write this**, PX4 team wrote it. You just:
- Configure parameters (PID gains, etc.)
- Send commands in offboard mode
- Trust it to control the drone

### Layer 5: Hardware (Actual drones)

- 4x Brushless motors
- 4x Electronic Speed Controllers (ESC)
- Flight controller board
- IMU, GPS, barometer sensors
- Battery
- WiFi/radio module

**You don't build this** (for competition). You buy it pre-assembled.

### Information Flow (Complete Example)

My code runs, step by step:

```
1. My Python code (Layer 1) computes:
   desired_velocity = [0.5, 0.2, 0.0] m/s

2. Creates ROS 2 message (Layer 2):
   msg.velocity = [0.5, 0.2, 0.0]

3. Publishes to topic (Layer 2):
   self.publisher.publish(msg)
   → "Send this to /drone1/setpoint"

4. ROS 2 serializes (Layer 2):
   bytes = [0x03, 0x00, 0x40, 0x3f, ...]

5. Network transmission (Layer 2):
   bytes → WiFi → drone

6. Bridge receives on drone (Layer 3):
   bytes → PX4 trajectory_setpoint message

7. PX4 reads (Layer 4):
   velocity_desired = [0.5, 0.2, 0.0]

8. PX4 computes motor commands (Layer 4):
   motor_1_power = 1200 (out of 1000-2000 range)
   motor_2_power = 1150
   motor_3_power = 1250
   motor_4_power = 1100

9. Motors spin (Layer 5):
   Propellers generate thrust
   Drone accelerates to desired velocity

10. Sensors measure (Layer 5):
    IMU: "acceleration is now 0.05 m/s²"
    GPS: "position is now (1.5, 2.1, 2.0)"

11. PX4 sends back (Layer 4):
    vehicle_odometry message

12. Bridge sends to laptop (Layer 3):
    ROS 2 Odometry message

13. My code receives (Layer 1):
    self.current_position = [1.5, 2.1, 2.0]

14. Loop: Go to step 1, repeat 50 times/second
```

This happens 50 times per second. The entire cycle takes 20ms.

---

## Phase 3: Simulation Development (Weeks 9-12)

### Starting Simple: Hello World (Week 9 Start)

Before writing formation control, I needed to verify ROS 2 + PX4 work together.

**File: hello_drone.py**

```python
#!/usr/bin/env python3
"""
Simple ROS 2 node that publishes and subscribes to test messages.
This verifies ROS 2 is working before touching drones.
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Point

class HelloDrone(Node):
    def __init__(self):
        super().__init__('hello_drone')
        
        # Publisher: publish a simple message
        self.publisher = self.create_publisher(String, 'drone_status', 10)
        
        # Subscriber: listen for messages
        self.subscriber = self.create_subscription(
            Point,
            'test_position',
            self.position_callback,
            10
        )
        
        # Timer: publish every 1 second
        self.timer = self.create_timer(1.0, self.publish_status)
        
        self.get_logger().info('HelloDrone node started!')
        
    def publish_status(self):
        """Publish status message every second"""
        msg = String()
        msg.data = 'Drone system is running!'
        self.publisher.publish(msg)
        self.get_logger().info(f'Published: {msg.data}')
        
    def position_callback(self, msg):
        """Receive position updates"""
        self.get_logger().info(f'Received position: x={msg.x}, y={msg.y}, z={msg.z}')

def main(args=None):
    rclpy.init(args=args)
    node = HelloDrone()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
```

**Running it**:
```bash
# Terminal 1: Run the node
cd ~/swarm_ws
colcon build
source install/setup.bash
python3 -m swarm_coordinator.hello_drone

# Terminal 2: Send a test message
ros2 topic pub /test_position geometry_msgs/Point "{x: 1.0, y: 2.0, z: 3.0}" --once

# Terminal 1 should print: "Received position: x=1.0, y=2.0, z=3.0"
```

This verified Layer 1 and Layer 2 working together.

### Testing Single Drone in Gazebo (Week 9-10)

Now I test actual PX4 communication.

**File: simple_drone_control.py**

```python
#!/usr/bin/env python3
"""
Simple drone control: takeoff, hover, land.
This is the minimal code to actually control a drone via PX4.
Works with real drones or PX4 SITL simulation.
"""

import rclpy
from rclpy.node import Node
from px4_msgs.msg import (
    VehicleCommand,
    OffboardControlMode,
    TrajectorySetpoint
)

class SimpleDroneControl(Node):
    def __init__(self):
        super().__init__('simple_drone_control')
        
        # Publishers (send commands to drone)
        self.vehicle_command_pub = self.create_publisher(
            VehicleCommand,
            '/fmu/in/vehicle_command',
            10
        )
        
        self.offboard_control_mode_pub = self.create_publisher(
            OffboardControlMode,
            '/fmu/in/offboard_control_mode',
            10
        )
        
        self.trajectory_setpoint_pub = self.create_publisher(
            TrajectorySetpoint,
            '/fmu/in/trajectory_setpoint',
            10
        )
        
        # Control loop timer (50 Hz)
        self.timer = self.create_timer(0.02, self.control_loop)
        
        # State tracking
        self.state = "IDLE"
        self.state_time = 0.0
        self.arm_command_sent = False
        
        self.get_logger().info('Simple Drone Control started')
        
    def send_vehicle_command(self, command_type, param1=0.0):
        """Send a vehicle command to PX4"""
        cmd = VehicleCommand()
        cmd.command = command_type
        cmd.param1 = param1
        self.vehicle_command_pub.publish(cmd)
        
    def send_offboard_control_mode(self):
        """Tell PX4 we're sending offboard control commands"""
        mode = OffboardControlMode()
        mode.velocity = True
        self.offboard_control_mode_pub.publish(mode)
        
    def send_trajectory_setpoint(self, vx=0.0, vy=0.0, vz=0.0):
        """Send velocity command to drone"""
        setpoint = TrajectorySetpoint()
        setpoint.velocity[0] = vx
        setpoint.velocity[1] = vy
        setpoint.velocity[2] = vz
        self.trajectory_setpoint_pub.publish(setpoint)
        
    def control_loop(self):
        """Main control loop, runs 50 times per second"""
        
        if self.state == "IDLE":
            if not self.arm_command_sent:
                self.get_logger().info('Sending ARM command')
                self.send_vehicle_command(
                    command_type=400,  # MAV_CMD_COMPONENT_ARM_DISARM
                    param1=1.0
                )
                self.arm_command_sent = True
                self.state_time = 0.0
            
            self.state_time += 0.02
            if self.state_time > 2.0:
                self.state = "TAKING_OFF"
                self.state_time = 0.0
                self.get_logger().info('State: TAKING_OFF')
        
        elif self.state == "TAKING_OFF":
            self.send_offboard_control_mode()
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=-1.0)  # negative = up
            
            self.state_time += 0.02
            if self.state_time > 3.0:
                self.state = "HOVERING"
                self.state_time = 0.0
                self.get_logger().info('State: HOVERING')
        
        elif self.state == "HOVERING":
            self.send_offboard_control_mode()
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=0.0)
            
            self.state_time += 0.02
            if self.state_time > 5.0:
                self.state = "LANDING"
                self.state_time = 0.0
                self.get_logger().info('State: LANDING')
        
        elif self.state == "LANDING":
            self.send_offboard_control_mode()
            self.send_trajectory_setpoint(vx=0.0, vy=0.0, vz=0.5)  # positive = down
            
            self.state_time += 0.02
            if self.state_time > 5.0:
                self.get_logger().info('Mission complete!')
                rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    controller = SimpleDroneControl()
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
```

**Running with Gazebo**:
```bash
# Terminal 1: Start Gazebo with PX4 SITL
cd ~/PX4-Autopilot
make px4_sitl gazebo-classic

# Terminal 2: Run the drone control
cd ~/swarm_ws
source install/setup.bash
python3 -m swarm_coordinator.simple_drone_control

# Watch Gazebo: drone arms → takes off → hovers → lands
```

This verifies all 5 layers working together. I was amazed when the virtual drone actually moved in Gazebo.

### Two-Drone Formation (Week 11)

Now the swarm begins.

**File: two_drone_simple.py**

```python
#!/usr/bin/env python3
"""
Two drone coordination: Drone 2 follows Drone 1.
This is the start of swarm behavior.
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from px4_msgs.msg import TrajectorySetpoint, OffboardControlMode

class TwoDroneControl(Node):
    def __init__(self):
        super().__init__('two_drone_control')
        
        # Subscribe to drone positions
        self.drone1_pos_sub = self.create_subscription(
            Point, '/drone1/position', self.drone1_position_callback, 10
        )
        self.drone2_pos_sub = self.create_subscription(
            Point, '/drone2/position', self.drone2_position_callback, 10
        )
        
        # Publish commands to drone 2
        self.drone2_setpoint_pub = self.create_publisher(
            TrajectorySetpoint, '/drone2/setpoint', 10
        )
        self.drone2_mode_pub = self.create_publisher(
            OffboardControlMode, '/drone2/mode', 10
        )
        
        # Current positions
        self.drone1_pos = Point(x=0.0, y=0.0, z=0.0)
        self.drone2_pos = Point(x=0.0, y=0.0, z=0.0)
        
        # Control loop at 50Hz
        self.timer = self.create_timer(0.02, self.coordination_loop)
        
        self.get_logger().info('Two Drone Control started')
        
    def drone1_position_callback(self, msg):
        self.drone1_pos = msg
        
    def drone2_position_callback(self, msg):
        self.drone2_pos = msg
        
    def coordination_loop(self):
        """Main swarm coordination logic"""
        
        # Desired formation: Drone 2 should be 1 meter to the right of Drone 1
        desired_offset_x = 1.0
        desired_offset_y = 0.0
        desired_offset_z = 0.0
        
        # Drone 2's desired position
        drone2_desired_x = self.drone1_pos.x + desired_offset_x
        drone2_desired_y = self.drone1_pos.y + desired_offset_y
        drone2_desired_z = self.drone1_pos.z + desired_offset_z
        
        # Error (how far from desired position)
        error_x = drone2_desired_x - self.drone2_pos.x
        error_y = drone2_desired_y - self.drone2_pos.y
        error_z = drone2_desired_z - self.drone2_pos.z
        
        # PID control (proportional for now)
        Kp = 0.5  # Proportional gain
        
        velocity_x = Kp * error_x
        velocity_y = Kp * error_y
        velocity_z = Kp * error_z
        
        # Limit velocity for safety
        max_velocity = 1.0
        velocity_x = max(-max_velocity, min(max_velocity, velocity_x))
        velocity_y = max(-max_velocity, min(max_velocity, velocity_y))
        velocity_z = max(-max_velocity, min(max_velocity, velocity_z))
        
        # Send commands
        mode = OffboardControlMode()
        mode.velocity = True
        self.drone2_mode_pub.publish(mode)
        
        setpoint = TrajectorySetpoint()
        setpoint.velocity[0] = velocity_x
        setpoint.velocity[1] = velocity_y
        setpoint.velocity[2] = velocity_z
        self.drone2_setpoint_pub.publish(setpoint)
        
        # Log every 1 second
        if int(self.get_clock().now().nanoseconds / 1e9) % 1 == 0:
            self.get_logger().info(
                f'D1: ({self.drone1_pos.x:.2f}, {self.drone1_pos.y:.2f}) | '
                f'D2: ({self.drone2_pos.x:.2f}, {self.drone2_pos.y:.2f}) | '
                f'Error: ({error_x:.2f}, {error_y:.2f})'
            )

def main(args=None):
    rclpy.init(args=args)
    controller = TwoDroneControl()
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
```

**What's happening**:
- Drone 1 flies a path (in real scenario)
- My code reads Drone 1's position
- Computes Drone 2's desired position = Drone 1 + offset
- Computes error = desired - actual
- Applies PID: velocity = Kp × error
- Drone 2 moves toward desired position
- Loop repeats 50 times/second

**Key insight**: This IS the entire swarm algorithm at its core. Just repeat for 3, 4, 5 drones.

### Configuration File (Week 11)

**File: drone_config.yaml**

```yaml
# Simple drone configuration

formation:
  type: "line"
  spacing: 1.0  # meters between drones
  
drones:
  drone_1:
    id: 1
    name: "leader"
    offset: [0.0, 0.0, 0.0]
  
  drone_2:
    id: 2
    name: "follower_1"
    offset: [1.0, 0.0, 0.0]  # 1 meter to the right
  
  drone_3:
    id: 3
    name: "follower_2"
    offset: [2.0, 0.0, 0.0]  # 2 meters to the right

control:
  control_frequency: 50  # Hz
  
pid:
  Kp: 0.5
  Ki: 0.1
  Kd: 0.2
```

Load in Python:
```python
import yaml

with open('drone_config.yaml', 'r') as f:
    config = yaml.safe_load(f)

Kp = config['control']['pid']['Kp']
offsets = config['drones']
```

### What I Learned in Weeks 9-12

1. **Layer integration works**: ROS 2 + PX4 actually communicate correctly
2. **Simulation is reliable**: Drones behave predictably in Gazebo
3. **Algorithm is simple**: Formation control is just PID on error
4. **50Hz is the magic frequency**: Everything runs at this rate
5. **Tuning matters**: Different Kp values change behavior significantly

---

## Phase 4: Hardware Testing (Weeks 13-16)

### The Transition from Simulation to Reality

When I moved to real drones, almost everything was the same code. The only differences:

**Simulation**:
```
Gazebo (on your laptop) ↔ PX4 SITL (on your laptop) ↔ ROS 2 (on your laptop)
All on localhost, perfect physics, instant communication
```

**Hardware**:
```
Real drones ↔ PX4 (on drone) ↔ ROS 2 (on your laptop) ↔ Your code (on your laptop)
Over WiFi, real physics, ~50-100ms latency
```

My code for `two_drone_simple.py` ran unchanged on real drones. Only the parameters needed tuning.

### Hardware Selection

I chose **Crazyflie 2.1** nano drones because:
- Cheap ($100 each) so crashes aren't disasters
- Pre-built (no assembly needed)
- WiFi/radio communication built-in
- Small enough for indoor flight
- Active research community

Alternatives:
- **CoDrone EDU** ($150): Better battery life, more official support
- **DIY from kit**: More work but learn more hardware

### Single Drone Testing (Week 13)

**Pre-flight checklist**:
```bash
1. Battery fully charged
2. Propellers intact (no cracks)
3. WiFi connection established
4. PX4 firmware up-to-date
5. Sensors calibrated (compass, accelerometer)
6. Large clear space available
7. No people in flight area
8. Safety briefing done
```

Testing sequence:
```
1. Manual hover test
   - Control drone with remote
   - Verify it responds
   - Check altitude hold

2. Simple waypoint test
   - 1 meter takeoff
   - 1 second hover
   - Land
   
3. Formation formation test
   - 2 meters takeoff
   - Move forward 1 meter
   - Return to start
   - Land
```

When step 3 worked consistently, I knew the hardware was ready for multi-drone.

### Two-Drone Real Test (Week 14)

Same code as simulation, but:
- **Shorter flights** (batteries last ~7 minutes)
- **Continuous tuning** (different Kp every flight)
- **Careful monitoring** (watching for crashes)
- **Detailed logging** (recording every flight with rosbag)

```bash
# Record flight data
ros2 bag record -a -o flight_test_1

# Run formation
python3 two_drone_simple.py

# Stop and analyze
ros2 bag play flight_test_1
```

Analysis of first flight:
- Drone 2 oscillated (Kp too high)
- Adjusted to Kp = 0.3
- Second flight: smooth tracking

This iterative process took about 10 flights per parameter adjustment.

### Adding More Drones (Week 15-16)

Adding drone 3 and 4 followed the same pattern:
```python
# Copy drone 2 code
# Change drone_id: 2 → 3
# Change offsets: [1.0, 0.0, 0.0] → [2.0, 0.0, 0.0]
# Test formation with 3 drones

# Repeat for drone 4
```

By week 16:
- 4 drones flying in formation consistently
- Tuned parameters: Kp=0.4, Ki=0.05, Kd=0.1
- Can handle one drone disconnecting (others re-form)
- Flight time: 5 minutes per battery

---

## Phase 5: Competition Preparation (Weeks 17-18)

### What I Documented

**Technical report sections**:
1. System architecture
2. Algorithm explanation
3. Hardware specifications
4. Software stack
5. Test results
6. Known limitations
7. Future improvements

**Videos created**:
- Takeoff in formation (30 seconds)
- Formation movement (60 seconds)
- Graceful failure (45 seconds)
- Complete mission (120 seconds)

### Pre-Flight Checklist for Competition

```
Hour -24:
  [ ] All batteries charged
  [ ] Propellers checked
  [ ] Firmware verified
  [ ] WiFi tested
  [ ] Code compiled and tested

Hour -1:
  [ ] Arrive at competition venue
  [ ] Test WiFi at location
  [ ] Verify all 4 drones arm
  [ ] Calibrate compass
  [ ] Check battery voltage

Minute -5:
  [ ] Clear flying area
  [ ] Launch ground computer
  [ ] Initialize ROS 2 coordinator
  [ ] Connect to all drones
  [ ] Verify ROS 2 sees all drones

Minute 0:
  [ ] Execute mission
  [ ] Monitor all drone positions
  [ ] Watch for failures
  [ ] Log entire flight
```

### Lessons Learned

**Things that worked**:
- Simulation → hardware transition was smooth
- PID control was stable after tuning
- Formation recovered from single drone loss
- WiFi communication was reliable

**Things that didn't work initially**:
- Oscillation (too high Kp) → reduced to 0.4
- Compass interference → moved WiFi router
- Battery sag → tested with fully charged batteries only
- GPS drift → used relative positioning instead

**Time spent**:
- Weeks 1-6: Research (actual ~80 hours)
- Weeks 7-8: Setup (actual ~25 hours)
- Weeks 9-12: Simulation (actual ~110 hours)
- Weeks 13-16: Hardware (actual ~115 hours)
- Weeks 17-18: Competition prep (actual ~30 hours)
- **Total: ~360 hours**

Not all weeks had equal hours, but distribution was:
- Research: 20% (foundations)
- Setup: 7% (one-time)
- Simulation: 30% (testing algorithms)
- Hardware: 32% (getting it to work in real life)
- Prep: 8% (final polish)

---

## Common Issues I Encountered

### Issue 1: ROS 2 DDS Timeout

**Problem**: Nodes couldn't find each other

**Solution**: Firewall was blocking UDP ports 7400-7410

```bash
sudo ufw allow 7400:7410/udp
```

### Issue 2: PX4 SITL Won't Connect to Gazebo

**Problem**: "Failed to spawn model"

**Solution**: Graphics driver issue

```bash
# Update graphics drivers
sudo apt-get install nvidia-driver-XXX  # or amd, intel

# Or: Use non-graphics mode
make px4_sitl gazebo-classic headless
```

### Issue 3: Drones Oscillate in Real Flight

**Problem**: Shaking motion around desired position

**Solution**: PID gains too aggressive

```yaml
# Reduced
Kp: 0.5 → 0.4
Kd: 0.2 → 0.3  # increased dampening
```

### Issue 4: WiFi Drops Connection

**Problem**: "Lost communication with drone"

**Solution**: Antenna positioning and interference

- Moved WiFi router away from metal objects
- Kept drones within 50m of router
- Tested WiFi signal strength before flying

### Issue 5: GPS Drift Causes Formation Shift

**Problem**: "All drones drifting same direction"

**Solution**: GPS noise is normal, use relative positioning

Changed from absolute positions to relative:
```python
# Old (absolute)
desired_x = 5.0  # meters (GPS-based)

# New (relative)
desired_x = drone1_x + 1.0  # relative to other drone
```

---

## Success Criteria (Looking Back)

Did I meet my goals?

**Research Phase** ✓
- Understood quadrotor dynamics
- Understood PID control
- Understood distributed algorithms
- Understood ROS 2 and PX4

**Simulation Phase** ✓
- Single drone autonomous flight
- Two-drone formation
- Four-drone swarm
- Failure recovery

**Hardware Phase** ✓
- Real drones flying
- Formation maintained
- Parameters tuned
- Reliable for competition

**Competition** ✓
- Mission executed successfully
- Judges impressed with swarm coordination
- Graceful failure recovery demonstrated
- Technical knowledge impressive

Looking back, the 18-week timeline was realistic. If I had to do it again, I wouldn't change the pace.

---

## Code Summary

**Lines of code written**:
- hello_drone.py: ~40 lines
- simple_drone_control.py: ~120 lines
- two_drone_simple.py: ~100 lines
- Configuration and launch files: ~50 lines
- **Total: ~310 lines**

The code is simple because:
1. ROS 2 handles complexity
2. PX4 handles complexity
3. My code is just the algorithm

**Actually**, if I had to code everything from scratch (networking, flight control, etc.), it would be thousands of lines. By leveraging existing tools, I stayed focused on the swarm algorithm.

---

## Final Thought on Implementation

The 5-layer architecture made this project feasible:
- Not writing Layer 4 (PX4) saved me ~5000 lines of C++
- Not writing Layer 2 (ROS 2) saved me ~10000 lines of networking code
- Not writing Layer 5 (hardware) saved me weeks of mechanical work

I only wrote Layer 1 and used the others. This is how real robotics works - stand on the shoulders of giants.
