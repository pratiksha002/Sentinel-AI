# Document 3: References, Troubleshooting & Resources
## Everything You Need to Get Help and Move Forward

---

## PART 1: COMPLETE LEARNING RESOURCES

### Quadrotor Dynamics & Control

**Best Resource**: ETH Zurich Quadrotor Control (YouTube)
- Search: "Quadrotor Control ETH Zurich"
- Duration: 45 minutes
- Why: Most intuitive explanation with animations
- When to watch: Week 1, before anything else

**Reading**: PX4 Concepts & Architecture
- URL: docs.px4.io/main/en/concept/
- Sections: Architecture, Flight Modes, Offboard Control
- Duration: 2-3 hours
- Why: Official documentation, authoritative
- When to read: Week 1, after video

**Supplementary**: MIT OpenCourseWare Underactuated Robotics
- URL: ocw.mit.edu
- Search: "Underactuated Robotics"
- Lectures 4-6: Quadrotor control
- Why: Deep mathematical understanding
- When to use: Week 2, optional for depth

### PID Control Theory

**Best Video Series**: Brian Douglas Control Systems Lectures
- Search YouTube: "Brian Douglas Control Systems Lectures"
- Videos to watch: PID Control series (4 parts, 15 min each)
- Why: Clear visual explanations of P, I, D terms
- When to watch: Week 2

**Interactive Learning**: Online PID Simulator
- Sites: Khan Academy, EveryEng, or search "PID simulator online"
- Duration: 1-2 hours of hands-on practice
- Why: See immediately what changing gains does
- When to use: Week 2, after Brian Douglas videos

**Reference**: "Feedback Control of Dynamic Systems" (Book)
- Authors: Franklin, Powell, Emami-Naeini
- Chapters: 1-3 (fundamentals), 5-6 (design)
- Duration: Heavy reading, reference as needed
- Why: Rigorous mathematical foundation
- When to use: Week 2-3, if you want deep theory

### Distributed Algorithms

**Key Paper**: "Consensus Problems in Networks of Agents with Switching Topology"
- Authors: Olfati-Saber & Murray (2004)
- Where: IEEE Transactions on Automatic Control (ResearchGate)
- Pages: Read 1-3 (skip proofs initially)
- Duration: 2-3 hours
- Why: Foundation for leaderless swarms
- When to read: Week 3

**Key Paper**: "Distributed Formation Flying Using Vision and Relative Navigation"
- Authors: Kumar et al. (2001)
- Where: Journal of Guidance, Control and Dynamics (Google Scholar)
- Pages: Sections 2-3 (algorithm description)
- Duration: 1-2 hours
- Why: Practical formation control approach
- When to read: Week 3

**Overview Paper**: "A Comprehensive Tutorial on Swarm Robotics"
- Authors: Brambilla et al. (2013)
- Where: ACM Computing Surveys
- Duration: 2-3 hours (optional)
- Why: See different approaches, compare algorithms
- When to read: Week 3, after main papers

**YouTube Alternative**: Search "Consensus algorithms explained" or "swarm robotics tutorial"
- Duration: 20-30 min videos
- Why: Visual alternative to papers
- When to watch: If papers are too dense

### ROS 2 Learning

**Official Documentation**: ROS 2 Humble
- URL: docs.ros.org/en/humble/
- Sections: Concepts, Beginner CLI Tools, Beginner Client Libraries
- Duration: 2-3 hours reading + 2-3 hours hands-on
- Why: Official source, always current
- When to use: Week 4, primarily

**YouTube Tutorials**: ROS 2 Concepts
- Search: "ROS 2 Humble Tutorial Beginner"
- Duration: 20-30 min video
- Why: Visual explanation of pub/sub
- When to watch: Week 4, before official docs

**Hands-on Practice**: Official ROS 2 Tutorials
- URL: docs.ros.org/en/humble/Tutorials.html
- Focus: "Beginner CLI Tools" and "Client Libraries Python"
- Duration: 3-5 hours of actually running code
- Why: Learning by doing
- When to do: Week 4, essential

### PX4 Flight Control

**Official Documentation**: PX4 Developer Guide
- URL: docs.px4.io/main/en/
- Key sections: Concept (architecture), Offboard Control, Message Reference
- Duration: 2-3 hours reading
- Why: Everything you need to know about PX4
- When to read: Week 5

**Video**: PX4 System Architecture Overview
- Search YouTube: "PX4 System Architecture"
- Duration: 20-30 minutes
- Why: Visual understanding of data flow
- When to watch: Week 5, before documentation

**Integration Guide**: PX4 + ROS 2
- URL: docs.px4.io/main/en/ros2/
- Duration: 1-2 hours
- Why: Shows how they communicate
- When to read: Week 5, after learning each separately

**Simulation**: PX4 SITL with Gazebo
- URL: docs.px4.io/main/en/simulation/gazebo/
- Duration: 1-2 hours (mostly installation)
- Why: Setup instructions you'll actually use
- When to follow: Week 7-8

---

## PART 2: COMPLETE TROUBLESHOOTING GUIDE

### ROS 2 Installation Problems

**Problem**: `ros2` command not found

**Diagnosis**:
```bash
which ros2  # Returns nothing
```

**Solution**:
```bash
# Add to ~/.bashrc
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc

# Verify
ros2 --version  # Should print version
```

**Why this happens**: ROS 2 needs to be sourced in shell environment

---

**Problem**: DDS Discovery Timeout (nodes can't find each other)

**Symptoms**:
```bash
ros2 topic list  # Returns empty
ros2 node list   # Returns empty
```

**Diagnosis**:
```bash
# Check firewall
sudo ufw status
```

**Solution**:
```bash
# Allow UDP ports for ROS 2 DDS
sudo ufw allow 7400:7410/udp
sudo ufw allow 7410:7420/udp

# Restart firewall
sudo ufw reload

# Test
ros2 run demo_nodes_cpp listener &
ros2 run demo_nodes_cpp talker
# Should see messages
```

**Why this happens**: ROS 2 uses UDP multicast for discovery, firewall blocks it

---

**Problem**: Import errors in Python code

**Symptoms**:
```
ModuleNotFoundError: No module named 'px4_msgs'
```

**Diagnosis**:
```bash
# Check if package is built
colcon list | grep px4_msgs
```

**Solution**:
```bash
# Rebuild if missing
cd ~/ros2_ws
colcon build --packages-select px4_msgs
source install/setup.bash

# Or: Make sure to source before running
source install/setup.bash
python3 my_script.py
```

**Why this happens**: Python can't find package because setup.bash not sourced

---

### PX4 Installation Problems

**Problem**: `make px4_sitl` fails with "dependencies not found"

**Symptoms**:
```
Error: cannot find -lm
```

**Diagnosis**:
```bash
# Check if setup script ran
ls ~/PX4-Autopilot/Tools/setup  # Should exist
```

**Solution**:
```bash
cd ~/PX4-Autopilot
bash ./Tools/setup/ubuntu.sh  # Run again
make clean
make px4_sitl gazebo-classic
```

**Why this happens**: Setup script didn't run or was incomplete

---

**Problem**: Gazebo window won't open

**Symptoms**:
```
No window opens
Or: Error: cannot open display
```

**Diagnosis**:
```bash
# Check graphics
glxinfo | grep "direct rendering"  # Should say "Yes"
```

**Solution**:
```bash
# Update graphics drivers
sudo apt-get update
sudo apt-get install nvidia-driver-535  # Or appropriate version

# If still fails:
make px4_sitl gazebo-classic_headless  # No graphics mode
```

**Why this happens**: Graphics driver issues, common on Linux

---

**Problem**: Very slow build times

**Symptoms**:
```
make px4_sitl takes 30+ minutes
```

**Solution**:
```bash
# Use parallel build
make px4_sitl -j4  # Use 4 cores
make px4_sitl -j$(nproc)  # Use all cores

# Or: Use pre-built binaries instead of building from source
```

**Why this happens**: Single-threaded build uses one CPU core

---

### ROS 2 + PX4 Integration Problems

**Problem**: ROS 2 can't see PX4 topics

**Symptoms**:
```bash
ros2 topic list | grep px4  # Returns empty
```

**Diagnosis**:
```bash
# Check if PX4 is running
ps aux | grep px4
```

**Solution**:
```bash
# Make sure you started PX4 SITL:
cd ~/PX4-Autopilot
make px4_sitl gazebo-classic

# Then source ROS 2 in different terminal:
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 topic list
```

**Why this happens**: PX4 must be running before ROS 2 can see its topics

---

**Problem**: Drone doesn't respond to commands

**Symptoms**:
```
Publish to /fmu/in/trajectory_setpoint but drone doesn't move
```

**Diagnosis**:
```bash
# Check drone status
ros2 topic echo /fmu/out/vehicle_status
# Look for: armed=True, nav_state=OFFBOARD
```

**Solution**:
```python
# Must arm and enable offboard mode first:

# 1. Send arm command
vehicle_command.command = 400  # MAV_CMD_COMPONENT_ARM_DISARM
vehicle_command.param1 = 1.0   # 1.0 = arm

# 2. Send offboard control mode
offboard_mode.velocity = True

# 3. Only then send trajectory setpoint
trajectory_setpoint.velocity = [0.5, 0.2, 0]
```

**Why this happens**: PX4 requires proper sequence of commands

---

### Simulation Problems

**Problem**: Drone falls through ground in Gazebo

**Symptoms**:
```
Drone falls in Gazebo, doesn't land on ground
```

**Diagnosis**:
```bash
# Check if physics plugin loaded
# Look in Gazebo window for ground plane
```

**Solution**:
```bash
# Restart Gazebo completely
pkill -9 gzserver
pkill -9 gzclient
make px4_sitl gazebo-classic  # Start again

# Or: Check drone mass is realistic
# In Gazebo model file, verify mass ~1 kg
```

**Why this happens**: Physics plugin issue or drone mass unrealistic

---

**Problem**: Drone behaves unrealistically in simulation

**Symptoms**:
```
Drone too responsive or too sluggish
Drifts without input
```

**Diagnosis**:
```bash
# Check PX4 parameters
# In PX4 console: param show MC_ROLL_P
```

**Solution**:
```bash
# Verify simulation parameters match real defaults
# Look in PX4 docs for default parameters

# Or: Adjust drone mass to be realistic
# Light drone: 0.5 kg
# Medium drone: 1-2 kg  
# Heavy drone: 3-5 kg
```

**Why this happens**: Simulation parameters different from real life

---

### Hardware Problems

**Problem**: Drone won't connect via WiFi

**Symptoms**:
```bash
Can't see drone in network
Can't SSH into drone
```

**Diagnosis**:
```bash
# Check WiFi network
networkctl  # Or: nmcli device wifi list
```

**Solution**:
```bash
# For Crazyflie: Connect via USB first
# For CoDrone: Check WiFi SSID matches configuration
# For DIY: Check router connected and broadcasting

# Test connection:
ping <drone_ip>  # Should respond
```

**Why this happens**: Network configuration, WiFi not enabled

---

**Problem**: Battery drains too fast

**Symptoms**:
```
Battery goes from 100% to 10% in 3 minutes
```

**Diagnosis**:
```bash
# Check motor current draw
# Use battery meter or oscilloscope
```

**Solution**:
```bash
# Verify:
1. Propellers balanced (no vibration)
2. No continuous high throttle
3. Battery not damaged
4. Motors working normally

# Test: Gentle hover for 5 minutes should use ~20% battery
```

**Why this happens**: Mechanical inefficiency or battery issue

---

**Problem**: Compass interference

**Symptoms**:
```
Drone drifts left/right without input
Yaw unstable
```

**Diagnosis**:
```bash
# Check compass calibration
# In QGroundControl: Vehicle Setup → Compass
```

**Solution**:
```bash
# Recalibrate compass:
1. Remove metal objects (phone, laptop) from area
2. Rotate drone in figure-8 pattern
3. Or: Move WiFi router further away (interference)
```

**Why this happens**: Metal interference with magnetometer

---

## PART 3: TESTING STRATEGIES

### Unit Testing (Test Single Component)

**What to test**: Formation algorithm in isolation

```python
import unittest
from my_code import FormationController

class TestFormation(unittest.TestCase):
    def test_static_formation(self):
        controller = FormationController(num_drones=3)
        
        # Set up: drones already in formation
        controller.positions[1] = (0, 0, 2)
        controller.positions[2] = (1, 0, 2)
        controller.positions[3] = (0, 1, 2)
        
        # Run one control step
        command = controller.compute_commands()
        
        # Assert: commands should be near zero
        for cmd in command.values():
            assert abs(cmd.x) < 0.1  # Small error
```

**Run with**:
```bash
python -m unittest test_formation.py
```

### Integration Testing (Test Components Together)

**What to test**: ROS 2 communication

```bash
# Terminal 1: Publish test message
ros2 topic pub /test_topic geometry_msgs/Point "{x: 1.0, y: 2.0, z: 3.0}"

# Terminal 2: Subscribe
ros2 topic echo /test_topic
# Should print the message immediately
```

### Simulation Testing (Full System)

**What to test**: Formation in Gazebo

```bash
# Terminal 1: Start Gazebo
cd ~/PX4-Autopilot
make px4_sitl gazebo-classic

# Terminal 2: Run your code
python3 two_drone_simple.py

# Watch Gazebo: drones should form/maintain formation
```

### Hardware Testing (Real Drones)

**Safety first**:
```
1. Clear flying area (10m radius)
2. No people nearby
3. Spotter ready to take manual control
4. Battery alarm set
5. Kill switch ready
```

**Test progression**:
```
1. Day 1: Single drone, manual control only
2. Day 2: Single drone, simple autonomous flight
3. Day 3: Two drones, formation holding
4. Day 4: Three drones, formation with movement
5. Day 5+: Full swarm, edge cases, competition scenario
```

**Don't skip steps**. Each step builds confidence for the next.

---

## PART 4: TEAM MANAGEMENT

### Role Assignments

**Algorithm Lead** (You or friend A):
- Responsibility: Swarm coordination algorithm
- Time: 30-40 hours during weeks 9-16
- Skills: Python, control theory understanding
- Deliverable: Working formation controller

**Systems Integration Lead** (You or friend B):
- Responsibility: ROS 2 setup, system architecture
- Time: 25-35 hours during weeks 7-16
- Skills: ROS 2, debugging, system design
- Deliverable: All components talking to each other

**Division of labor for 2 people**:
- One person focuses on algorithm (weeks 9-12)
- Other person focuses on hardware/testing (weeks 13-16)
- Both do research together (weeks 1-6)
- Both prepare for competition (weeks 17-18)

### Communication Strategy

**Weekly meetings** (30 min):
- What did you do?
- What's blocking you?
- What's next week?

**Async communication**:
- Quick questions: WhatsApp/Discord (same-day response)
- Technical discussions: Email or shared doc (next-day response)
- Bug reports: GitHub issues (with reproducible steps)

### Decision Making

- Algorithm decisions: Algorithm Lead decides
- Architecture decisions: Systems Lead decides
- Timeline issues: Discuss and decide together
- Competition strategy: Decide together

**Principle**: Once decided, both support the decision. Don't re-argue after decision made.

### Preventing Burnout

- Schedule is non-negotiable (20-30 hours/week)
- Breaks are essential (don't work 7 days/week)
- Celebrate milestones (first flight is worth celebrating!)
- Help each other (if one person gets stuck, pause and help)
- Document as you go (don't leave everything for end)

---

## PART 5: COMPETITION PREPARATION

### Know Your Competition

Before starting, find out:
- [ ] How many drones can you use?
- [ ] What formation required?
- [ ] What waypoints must be visited?
- [ ] Are there failure scenarios?
- [ ] How is scoring done?
- [ ] Time limits?
- [ ] Flying area size?

### Pre-Flight Checklist

**24 Hours Before**:
```
[ ] All batteries charged overnight
[ ] Propellers inspected
[ ] Firmware on all drones current
[ ] WiFi tested at venue
[ ] Code compiled and tested in simulation
[ ] All team members know their role
```

**1 Hour Before**:
```
[ ] Clear flying area
[ ] Launch ground computer
[ ] Boot all drones
[ ] Calibrate compass
[ ] Check battery voltages
```

**5 Minutes Before**:
```
[ ] Start ROS 2 coordinator
[ ] Connect to all 4 drones
[ ] Verify ROS 2 sees all topics
[ ] Check all drones armed status
[ ] Monitor telemetry display
```

**0 Minutes**:
```
[ ] Execute mission
[ ] Watch for failures
[ ] Log entire flight
[ ] Stay calm!
```

### Contingency Planning

**If one drone fails**:
- Code automatically removes it from swarm
- Remaining drones re-form with fewer drones
- Mission continues

**If you lose WiFi**:
- Drones enter failsafe (land automatically)
- Restart and try again
- Have backup WiFi router ready

**If code crashes**:
- Kill switch: Stop all drones immediately
- Restart code and retry
- Have manual control ready

### Post-Competition

- Save all flight logs
- Document what worked/didn't work
- Take photos/videos
- Write brief post-mortem
- Celebrate! (You did something genuinely impressive)

---

## PART 6: QUICK REFERENCE COMMANDS

### ROS 2 Commands

```bash
# List all topics
ros2 topic list

# Show message type
ros2 topic info /topic_name

# See live data
ros2 topic echo /topic_name

# Publish a message
ros2 topic pub /topic_name MessageType "{field: value}"

# Record all data
ros2 bag record -a -o filename

# Playback recording
ros2 bag play filename

# List running nodes
ros2 node list

# See node details
ros2 node info /node_name

# List parameters
ros2 param list

# Set a parameter
ros2 param set /node_name param_name value
```

### PX4 Commands

```bash
# Start PX4 SITL with Gazebo
make px4_sitl gazebo-classic

# Headless mode (no graphics)
make px4_sitl gazebo-classic_headless

# In PX4 console:
status                    # Show drone status
commander arm             # Arm the drone
commander land            # Land immediately
param show SYS_AUTOSTART  # Show parameters
param set MC_ROLL_P 5.0   # Set parameter
```

### Linux Commands

```bash
# Kill stuck processes
pkill -9 gzserver
pkill -9 python3

# Check processes
ps aux | grep ros2
ps aux | grep px4

# Monitor CPU/memory
watch -n 1 "free -h && echo '---' && top -bn1 | head -20"

# SSH into drone
ssh <username>@<drone_ip>

# Copy file to drone
scp myfile.py <username>@<drone_ip>:~/
```

---

## PART 7: EXTERNAL RESOURCES (Always Available)

### Official Documentation
- ROS 2: docs.ros.org/en/humble/
- PX4: docs.px4.io/main/en/
- Gazebo: gazebosim.org/docs
- QGroundControl: docs.qgroundcontrol.com

### Forums & Communities
- ROS 2 Discourse: discourse.ros.org
- PX4 Forum: discuss.px4.io
- Stack Exchange Robotics: robotics.stackexchange.com
- GitHub Issues: Search specific repo for known issues

### Research Papers
- Google Scholar: scholar.google.com
- ResearchGate: researchgate.net
- ArXiv: arxiv.org (free preprints)

### YouTube Channels
- ETH Zurich Robotics
- Brian Douglas (Control Systems)
- ROS official tutorials
- PX4 official channel

### Books Worth Reading
- "Robotics, Vision and Control" by Peter Corke
- "Modern Robotics" by Kevin Lynch
- "Aerial Robots" (various authors)

---

## FINAL ADVICE

**When stuck**:
1. Check troubleshooting section above
2. Search Google for exact error message
3. Check official documentation
4. Ask on forum with reproducible example
5. Reach out to team member for fresh perspective

**When frustrated**:
- Take a break (seriously, step away)
- Go do something else for 30 min
- Come back with fresh mind
- 90% of problems have simple solutions you missed

**When behind schedule**:
- Cut features, not quality
- Prioritize: working swarm > fancy features
- Ask for help
- Adjust timeline if needed

**When it works**:
- Document immediately
- Save video/logs
- Celebrate
- Move to next problem

You've got this. These three documents cover everything. Use them.
