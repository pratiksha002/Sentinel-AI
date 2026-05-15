# Autonomous Swarm Drone Project Guide

## Competition-Ready Prototype in 2-3 Months

**Document Version**: May 2026  
**Target Audience**: Beginner roboticists, 2-5 drone swarm, competition prototype  
**Budget Level**: Limited  
**Timeline**: 2-3 months (8-12 weeks)

\---

## Part 1: Materials \& Learning Resources

### Essential Learning Path

#### A. Online Courses \& Tutorials (2-3 weeks to review)

1. **MIT OpenCourseWare: Robotics**

   * Free lectures on quadrotor dynamics and control
   * Start with "Underactuated Robotics" for control theory intuition
   * URL: ocw.mit.edu
2. **ROS 2 Beginner Tutorials**

   * Official ROS 2 tutorials: docs.ros.org/en/humble/Tutorials
   * Focuses on pub/sub architecture (critical for multi-drone communication)
   * Expected time: 2-3 days of focused work
3. **PX4 Developer Guide**

   * Official documentation: docs.px4.io
   * Multi-vehicle simulation guide: essential for swarm testing
   * Expected time: 3-5 days
4. **YouTube Learning Paths**

   * "Flying Multiple UAVs using ROS" (academic overview)
   * RIIS tutorials on PX4 + ROS 2 integration
   * "Quadrotor Control" by ETH Zurich (dynamics foundations)
   * Note: YouTube videos are great for intuition but pair with official docs for implementation details

#### B. Academic Papers (Reading, Not Implementing)

Start with these to understand swarm behavior concepts. **Do not try to implement papers from scratch** – they're research-grade and assume much more experience than you have time for.

1. **Formation Control Papers**

   * "Distributed Formation Flying Using Vision and Relative Navigation" (Kumar et al., 2001)
   * Gives intuition for how drones maintain formation
   * Read the concepts, skip the math initially
2. **Consensus Algorithms for Swarms**

   * "Consensus Problems in Networks of Agents with Switching Topology" (Olfati-Saber \& Murray, 2004)
   * Explains how swarms can agree on direction/position without a leader
   * This directly applies to your coordination layer
3. **Collision Avoidance in Multi-Agent Systems**

   * "Probabilistic Motion Planning for Multi-Robot Navigation" (van den Berg et al., 2008)
   * Relevant for ensuring drones don't crash into each other
   * Read for concepts, use existing libraries for implementation

#### C. Open-Source Projects to Study

1. **PX4 Swarm Controller (GitHub: artastier/PX4\_Swarm\_Controller)**

   * ROS 2 package specifically for swarm control
   * Already implements leader-follower and formation patterns
   * **Perfect for you**: Contains ready-made examples for 3+ drones
   * Status: Actively maintained, works with latest PX4
2. **Crazyflie Nano Quadcopter Research Platform**

   * Small, cheap quadcopters designed for swarm research
   * Active research community with dozens of swarm examples
   * GitHub: bitcraze/crazyflie-firmware
   * Advantage: Extensive swarm documentation available
3. **MAVSDK (Drone Development Kit)**

   * Multi-language support (Python, C++, Java, etc.)
   * Simplifies communication with PX4 drones
   * Much easier to learn than raw MAVLink protocol
   * GitHub: mavlink/MAVSDK
4. **Gazebo Simulation**

   * Free, open-source 3D simulator
   * Integrates perfectly with ROS 2 and PX4
   * You can test 5-drone formation before buying hardware
   * Website: gazebosim.org

\---

## Part 2: Realistic Technology Stack (What Actually Works in 2-3 Months)

### Your Development Environment

**Operating System**: Ubuntu 22.04 LTS or later  
**Why**: All the tools below work seamlessly on Linux. You'll save weeks of troubleshooting compared to Windows/Mac. Use a VM or dual-boot if needed.

**Hardware Requirements for Development**:

* Laptop with 8GB RAM minimum (16GB recommended)
* SSD preferred for fast build times
* Decent CPU (any modern processor works)

### The Stack Explained: Why These Tools

#### **Flight Control: PX4 Autopilot**

PX4 is open-source autopilot software that runs on your drone hardware. Think of it as the "operating system for your drone."

**Why PX4 over ArduPilot?**  
PX4 has better integration with ROS 2 (which you need for swarm coordination). ArduPilot is more mature for single-drone operations but adds complexity for multi-drone scenarios.

**Installation**: Download from px4.io/downloads or build from source (docs.px4.io/main/en/dev\_setup/)

**Cost**: Free and open-source

#### **Simulation: Gazebo (Classic or Garden)**

Gazebo is a 3D physics simulator where you can test swarm algorithms before flying real drones. This is crucial for your 2-3 month timeline – debugging in simulation is 100x faster than physical testing.

**How it works**: You define a simulated environment (a field, obstacles, etc.), spawn 5 simulated drones running the same software as your real drones, and test your coordination algorithms. When a drone crashes in simulation, you just reset. When it crashes in real life, you buy a new one.

**Version to use**: Gazebo Classic (gz-classic) or newer Gazebo Garden depending on your ROS 2 version. Current stable: Gazebo Classic with ROS 2 Humble.

**Installation**: Follow PX4 guide's Gazebo section

**Cost**: Free and open-source

#### **Robot Operating System: ROS 2**

ROS 2 is the middleware that lets your drones communicate and coordinate. Without it, you'd be writing networking code from scratch (definitely not feasible in 2-3 months).

**What ROS 2 does for you**:  
It handles message passing between nodes (your drone control programs). You define what data each drone publishes (position, status, sensor readings) and what it subscribes to (commands from the coordinator). ROS 2 handles the networking automatically.

**Version to use**: ROS 2 Humble (most stable, good documentation)

**Installation**: Ubuntu 22.04 package: `sudo apt install ros-humble-desktop-full`

**Cost**: Free and open-source

**Alternative if ROS 2 feels too complex**: MAVSDK (simpler API but less flexible for advanced swarm behaviors)

#### **Communication Protocol: MAVLink**

MAVLink is a serialized protocol for sending commands between drone and computer. PX4 speaks MAVLink natively.

**You won't write MAVLink directly** – you'll use ROS 2 or MAVSDK libraries that abstract it. But understanding that MAVLink is the low-level language helps you debug communication issues.

**Cost**: Free and open-source

#### **Ground Control Station: QGroundControl**

QGroundControl is the "dashboard" for your drones. Use it to:

* Monitor live drone telemetry (altitude, speed, GPS location)
* Upload waypoints to drones
* Tune PID parameters (you'll do this a lot)
* Debug communication issues
* Plan missions visually

**Version**: Latest stable from qgroundcontrol.com

**Cost**: Free and open-source

### Complete Tech Stack Summary

```
┌─────────────────────────────────────────────┐
│  Your Swarm Coordination Algorithm         │
│  (ROS 2 C++/Python nodes)                   │
└────────────┬────────────────────────────────┘
             │
┌────────────▼────────────────────────────────┐
│  ROS 2 (Humble) - Pub/Sub Framework        │
│  Handles multi-drone communication          │
└────────────┬────────────────────────────────┘
             │
┌────────────▼────────────────────────────────┐
│  MAVLink Protocol (abstracted by PX4-ROS2) │
│  Drone ↔ Computer communication             │
└────────────┬────────────────────────────────┘
             │
   ┌─────────┴─────────┬───────────┬─────────┐
   │                   │           │         │
┌──▼──┐  ┌──────┐  ┌──▼──┐  ┌────▼──┐  ┌──▼──┐
│PX4  │  │PX4   │  │PX4  │  │ PX4   │  │ ... │
│D1   │  │D2    │  │D3   │  │ D4    │  │     │
└─────┘  └──────┘  └─────┘  └───────┘  └─────┘
(Drone 1) (Drone 2)(Drone 3)(Drone 4) (etc)

Testing Environment:
├─ Gazebo (Simulation)
├─ QGroundControl (Monitoring)
└─ ROS 2 Tools (rosbag, rviz for visualization)
```

\---

## Part 3: Hardware Options for Small Swarms

### Option A: Budget-Friendly Commercial Drones (Recommended for Your Timeline)

#### **Crazyflie 2.1 Nano Quadcopter**

* **Size**: 9.2 cm diagonal
* **Weight**: 27-30 grams
* **Price per unit**: $99-150 USD
* **For 4 drones**: \~$400-600 + charging equipment
* **Flight time**: 7 minutes per charge
* **Processor**: nRF52832 (ARM Cortex-M4)
* **Payload capacity**: \~10 grams (room for extra sensors)
* **Swarm support**: Excellent – active research community with multi-drone examples
* **Programming**: Python, C, or custom firmware
* **Simulator**: Works with Gazebo
* **Why choose this**:

  * Cheap enough that crashes aren't disasters
  * Excellent documentation for swarms
  * Ready-to-fly – no soldering required
  * Proven for research (published papers with 4+ drone swarms)
  * Requires 4x batteries + 4x charging station (\~$100-150)

#### **CoDrone EDU (RECF Approved)**

* **Size**: \~3 inches diagonal
* **Price per unit**: $149 USD
* **For 4 drones**: \~$600-700
* **Flight time**: 13 minutes
* **Programming**: Block-based or Python
* **Swarm capability**: Designed for group flying
* **Why choose this**:

  * Official platform for Aerial Drone Competition
  * If you compete in RECF, judges already know this platform
  * More powerful than Crazyflie
  * Better battery life (less charging downtime)
  * Community is primarily student-focused (you'll find lots of beginner projects)

**Recommendation**: Start with **Crazyflie** if you're doing pure swarm research, or **CoDrone EDU** if you're entering the RECF competition.

### Option B: Build-Your-Own (Advanced, Not Recommended for 2-3 Months)

Theoretically, you could build drones from scratch using STM32 boards + motors + ESCs. Cost per drone might be $50-100 instead of $150.

**Why not for your timeline**:

* Soldering, debugging, and tuning 5 custom drones takes 3-4 weeks alone
* Flight controller calibration is finicky
* By the time you get stable single-drone flight, you're at month 2 with barely any time for swarm algorithms
* One solder joint failure loses days to debugging

**Only consider this if**: You have experience with embedded systems and 4+ months total timeline.

**If you absolutely must go this route**:

* STM32F4 or F7 flight controller (\~$20)
* 4x brushless motors + ESCs (\~$40)
* IMU (MPU-9250) + Barometer (\~$10)
* Frame, props, batteries (\~$30)
* Radio module NRF24 or Flysky (\~$10)
* Total: \~$120-150 per drone, but add 3-4 weeks debugging time

### Minimum Hardware Kit for Competition Prototype

**For 4 drones (5 is redundancy for crashes)**:

Crazyflie Option:

* 4× Crazyflie 2.1 quadcopter: $600
* 1× Crazyradio PA (2.4GHz dongle): $50
* 1× Charging dock/hub: $100
* 4 spare battery packs: $80
* Protective case: $30
* **Total: \~$860**

CoDrone Option:

* 4× CoDrone EDU: $600
* Charging station: $100
* Spare batteries: $80
* **Total: \~$780**

Ground Control Equipment:

* Decent laptop (if you don't have one): $600-1000
* QGroundControl + ROS 2 tools: Free
* USB cables, router, and misc: $50

**Total bare minimum with laptop**: \~$1,400-1,900  
**Total minimum without laptop**: \~$800-1,000

*Note: Prices are approximate as of May 2026. Check current prices on distributors like SparkFun, Adafruit, AltiumLive, or local electronics retailers.*

\---

## Part 4: Realistic Project Timeline (8-12 Weeks)

### Week 1-2: Setup \& Learn (10 days active work)

**Goal**: Everything installed and first simulation running

**Activities**:

1. Install Ubuntu 22.04 (or verify you have it)
2. Install ROS 2 Humble following official tutorials (\~2-3 hours)
3. Install PX4 autopilot source and build (\~2-3 hours, lots of downloading)
4. Install Gazebo Classic and test single-drone simulation (\~2-3 hours)
5. Complete "ROS 2 Beginner Tutorials" on pub/sub model (\~1-2 days)
6. Read first 3 chapters of "Distributed Algorithms for Multi-Agent Systems"

**Deliverable**: One drone flying in Gazebo controlled via ROS 2 topic commands

**Success Metric**: You can publish a ROS 2 message and see the simulated drone move

**Risks to Watch**:

* ROS 2 installation often fails on first try (use the official Ubuntu packages, not from source)
* Gazebo takes a long time to compile from source (use binaries instead)
* Tutorial code often has typos – join the PX4 forum if stuck

### Week 3: Single Drone Autonomy (7-10 days)

**Goal**: One drone autonomously flying waypoints and maintaining stable flight

**Activities**:

1. Study PX4 offboard control mode (how external software commands drones)
2. Implement simple waypoint follower in ROS 2 (Python or C++)
3. Test in Gazebo: drone takes off, flies to 3 waypoints, lands
4. If you have hardware: flash PX4 onto first real drone, tune PID gains
5. Integrate QGroundControl for real-time monitoring

**Deliverable**: One drone (simulated or real) autonomously executing a simple square flight pattern

**Code Example** (pseudocode, simplified):

```python
class DroneController:
    def \_\_init\_\_(self):
        self.position\_sub = rospy.Subscriber('/drone1/pose', PoseStamped, self.pose\_callback)
        self.setpoint\_pub = rospy.Publisher('/drone1/setpoint', Point, queue\_size=10)
        self.arm\_pub = rospy.Publisher('/drone1/arm', Empty, queue\_size=1)
    
    def execute\_waypoints(self, waypoints):
        # Take off
        self.set\_altitude(1.0)  # 1 meter altitude
        rospy.sleep(3)
        
        # Visit each waypoint
        for waypoint in waypoints:
            self.goto(waypoint)  # Fly to x, y, z position
            rospy.sleep(2)
        
        # Land
        self.land()

def main():
    controller = DroneController()
    waypoints = \[
        Point(0, 0, 1),
        Point(1, 0, 1),
        Point(1, 1, 1),
        Point(0, 1, 1),
        Point(0, 0, 1)
    ]
    controller.execute\_waypoints(waypoints)
```

**Success Metric**: Drone completes a mission without human intervention

**Hardware Milestone**: If using real drones, flash PX4 firmware and perform first flight by end of this week. You need time to recover from crashes.

### Week 4: Communication \& Multi-Drone (7-10 days)

**Goal**: Get 2-3 drones in simulation talking to each other

**Activities**:

1. Study PX4 Swarm Controller GitHub project (artastier/PX4\_Swarm\_Controller)
2. Modify example to add third drone to simulation
3. Implement simple neighborhood discovery: drones know which drones are nearby based on position
4. Set up drone 1 as "leader" broadcasting its position, drones 2-3 as "followers" receiving it
5. Test in Gazebo with 3 simulated drones

**Key ROS 2 Concept - Namespaces**:  
You'll run 3 instances of PX4 (one per drone), each in its own namespace:

* `/drone1/offboard\_control\_mode`
* `/drone2/offboard\_control\_mode`
* `/drone3/offboard\_control\_mode`

This prevents message conflicts.

**Deliverable**: 3 drones in simulation, where drone 1 flies a path and drones 2-3 move toward it (not yet perfect formation)

**Success Metric**: All 3 drones arm and take off without interference

### Week 5: Formation Control (7-10 days)

**Goal**: Drones maintain formation (e.g., triangle shape) while flying

**Activities**:

1. Choose formation strategy: either consensus-based (all drones agree on direction) or leader-follower (one leads, others follow)
2. Implement formation error calculation: each drone computes its desired position in formation
3. Add simple PID controller: each drone tries to correct distance/angle errors from neighbors
4. Test formations in Gazebo: hold still formation, then move formation in a circle
5. Optional: Add collision avoidance (basic: keep 1 meter minimum distance from neighbors)

**Formation Mathematics** (simplified):

```
Each drone knows:
- Its current position: p\_i
- Leader's position: p\_leader (if leader-follower)
- Desired formation offset from leader: offset\_i = (0.5, 0.5, 0) meters

Desired position: p\_desired = p\_leader + offset\_i
Error: error = p\_desired - p\_i
Command: move towards error (proportional gain \* error)
```

**Deliverable**: 3-4 drones in simulation maintaining a triangle formation while moving

**Success Metric**: Drones stay within 0.5 meters of their formation positions

**Checkpoint**: If using real hardware, test single-drone waypoint following first before attempting formation with multiple real drones

### Week 6: Hardware Testing \& Tuning (5-7 days)

**Goal**: Transition from simulation to real drones (if you have hardware)

**Activities**:

1. Flash PX4 + your ROS 2 bridge code to one real drone
2. Perform initial tuning: adjust PID gains until drone hovers stably
3. Test single drone waypoint following outdoors/indoors (space permitting)
4. Add second real drone, repeat tuning
5. Test 2-drone formation for 2-3 minutes
6. Document all PID tuning values (you'll need these for remaining drones)

**Critical Safety Steps**:

* Always have props off during ground testing
* Use low battery power first (half charged)
* Test in a large, clear space away from people
* Have a spotter to call out issues
* Know how to manually stabilize drone if code fails (practice in simulation first)

**Deliverable**: 2 real drones successfully flying a simple formation for 30+ seconds

**Success Metric**: Formation holds without operator intervention for 2 full minutes

### Week 7-8: Swarm Behavior \& Resilience (14 days)

**Goal**: Add interesting swarm behaviors and handle communication loss

**Activities**:

1. Implement area coverage: drones collectively search a region (grid pattern)
2. Add obstacle avoidance: drones detect obstacles and replan paths
3. Implement graceful degradation: if one drone communication is lost, others maintain formation
4. Test loss-of-drone scenarios in simulation: kill one drone, verify others stabilize
5. Add mission replay: drones can resume formation if connection briefly drops
6. Experiment with formation changes: drones morph from line to triangle to line

**Important Behavior**:  
Without explicit handling, a drone that loses communication will drop altitude and land (safety feature). You need to decide: should formation persist if leader goes down? You might implement "leaderless" control where all drones average their velocities, so formation can continue even if one drone is offline.

**Deliverable**: Swarm completes a mission (area coverage or formation change) while handling 1 drone communication loss

**Success Metric**: Remaining drones maintain formation even after losing signal from one drone for 5+ seconds

### Week 9-10: Polish \& Competition Preparation (14 days)

**Goal**: Make your swarm robust, reliable, and competition-ready

**Activities**:

1. Extensive testing: run 50+ full-mission flights (in simulation + hardware)
2. Document all parameters in a configuration file (so judges can quickly tune your system)
3. Create visual mission demonstrations:

   * Video of swarm taking off in formation
   * Video of formation flight
   * Video of graceful failure recovery
4. Write a one-page technical summary of your approach
5. Prepare contingency: what if one drone doesn't start? Can remaining drones still score points?
6. Test in competition-like conditions (if you know specifics, practice those scenarios)

**Deliverable**: Fully working swarm, with documented parameters and demonstration videos

**Success Metric**: Your swarm completes its primary mission without human intervention in 9/10 test runs

### Week 11-12: Final Debugging \& Contingency (14 days)

**Goal**: Catch edge cases, practice, prepare backups

**Activities**:

1. Run full mission 20+ times, log every failure
2. Root cause every failure: is it a sensor issue? Communication? Algorithm bug?
3. Prepare backup plan: if one drone is broken on competition day, can you rapidly redeploy with 3 drones instead of 4?
4. Create pre-flight checklist (all drones arm? All connections good? Battery level?)
5. Practice actual competition scenario multiple times with same hardware you'll use at competition
6. Prepare technical presentation: be ready to explain your approach to judges
7. Final system integration: ensure all ROS 2 nodes, firmware, and settings are version-controlled

**Deliverable**: Ready-to-compete swarm with zero known critical bugs

**Success Metric**: You can deploy your swarm, run full mission, recover, and be ready for second run within 15 minutes

\---

## Part 5: Detailed Technology Recommendations

### Getting Started: The Three Possible Paths

#### Path A: ROS 2 + PX4 (Most Flexible, Steeper Learning Curve)

**Recommended for**: Doing custom swarm algorithms, medium technical experience

**Stack**:

* Flight control: PX4
* Coordination: ROS 2 (C++ or Python nodes)
* Simulation: Gazebo + px4\_sitl\_multiple\_run.sh
* Hardware options: Any PX4-compatible drone (Crazyflie, CoDrone, or DIY)

**Pros**:

* ROS 2 ecosystem has answer for almost every robotics problem
* Pub/sub model is natural for multi-drone coordination
* Excellent simulation
* Code is highly reusable

**Cons**:

* Steeper learning curve for beginners
* Takes longer to get first result running
* More files and configurations to manage

**Getting Started**:

1. Follow PX4 ROS 2 User Guide: docs.px4.io/main/en/ros2/
2. Clone PX4\_Swarm\_Controller: github.com/artastier/PX4\_Swarm\_Controller
3. Run the example with 3 simulated drones in Gazebo
4. Modify example to implement your own formation algorithm

#### Path B: Crazyflie SDK (Simplest, Limited to Crazyflie Drones)

**Recommended for**: Getting something working fast, sticking with Crazyflie hardware

**Stack**:

* Flight control: Crazyflie 2.1 firmware
* Coordination: Crazyflie Python SDK (crazyflie-lib-python)
* Simulation: Crazyflie Gazebo plugin (limited options)
* Hardware: Crazyflie 2.1 only

**Pros**:

* Very quick to get first program running (minutes)
* Crazyflie community is large and beginner-friendly
* Excellent swarm examples already published

**Cons**:

* Limited to Crazyflie hardware (can't switch to bigger drones later)
* Fewer advanced features compared to ROS 2
* Simulation less developed than PX4+Gazebo

**Getting Started**:

1. Install Crazyflie Python SDK
2. Explore example scripts in examples/swarm/ folder
3. Modify hello\_world.py to command multiple drones

#### Path C: MAVSDK (Middle Ground, More Accessible than ROS 2)

**Recommended for**: Need more than Crazyflie SDK but ROS 2 is too complex

**Stack**:

* Flight control: PX4
* Coordination: MAVSDK (Python, C++, Java APIs available)
* Simulation: Gazebo + PX4 SITL
* Hardware: Any PX4-compatible drone

**Pros**:

* Simpler API than ROS 2 for basic tasks
* Still works with any PX4 drone
* Good documentation

**Cons**:

* Less flexible than ROS 2 for complex coordination
* Smaller ecosystem compared to ROS

**Getting Started**:

1. Install MAVSDK-Python: `pip install mavsdk`
2. Follow examples: github.com/mavlink/MAVSDK-Python/tree/main/examples
3. Extend examples to handle multiple drones

### Technology Recommendation for Your Situation

**I recommend Path A (ROS 2 + PX4) because**:

* You have 2-3 months (enough time to learn ROS 2)
* You might want to use different hardware later
* ROS 2 is the industry standard – learning it now pays off long-term
* The PX4\_Swarm\_Controller example almost does what you need already

**Implementation specifics**:

* Use Python (easier learning curve than C++) for your coordination algorithms
* Use C++ only for high-speed control if needed later
* Start with Ubuntu 22.04 + ROS 2 Humble + PX4 main branch
* Gazebo Classic (not Garden) for stability
* Hardware: Buy 4 Crazyflie 2.1 units for first month, upgrade to CoDrone if entering RECF competition

\---

## Part 6: Swarm Algorithms (Choose One to Start)

### Leader-Follower (Simplest, Start Here)

How it works: Drone 1 (leader) flies a predefined path. Drones 2-5 (followers) maintain a fixed offset from the leader.

**Pseudocode**:

```
Leader:
  - Execute waypoint mission (fly to waypoint 1, then 2, then 3, etc)
  - Publish its position constantly

Follower:
  - Subscribe to leader's position
  - Calculate desired position = leader\_position + offset
  - Adjust velocity to move toward desired position
  - Keep altitude at leader's altitude
```

**Difficulty**: Easy  
**Implementation time**: 2-3 days  
**Robustness**: Moderate (fails if leader crashes)  
**Good for**: First proof-of-concept swarm

### Consensus Formation (More Advanced, More Robust)

How it works: All drones are equal. Each drone knows its neighbors' positions and tries to maintain formation shape without a designated leader.

**Key insight**: If your desired formation is a triangle with drones at positions A, B, C, each drone can compute "where should I be relative to my neighbors right now?" and move toward that position.

**Pseudocode**:

```
For each drone i:
  - Read positions of nearby drones (neighbors)
  - Compute formation error: how far am I from my desired position in the formation?
  - Adjust velocity to reduce error
  - If one neighbor goes missing, re-distribute the formation
```

**Difficulty**: Moderate  
**Implementation time**: 3-5 days  
**Robustness**: High (works even if one drone drops out)  
**Good for**: Resilient, sophisticated-looking swarms

**Why consensus is better for competitions**: Judges are impressed when you lose one drone and the other drones seamlessly re-form. This shows real distributed autonomy.

### Area Coverage (Collaborative Search)

How it works: Drones divide a region into search zones and sweep through them, maintaining loose formation for safety.

**Pseudocode**:

```
1. Divide area into N zones (one per drone)
2. Each drone assigned to one zone
3. Each drone sweeps its zone in a grid pattern
4. All drones maintain loose formation (stay within 10m of each other for safety)
5. Mark explored regions, communicate findings
```

**Difficulty**: Moderate-Hard  
**Implementation time**: 4-6 days  
**Robustness**: High  
**Good for**: Search-and-rescue style missions, demonstrations

\---

## Part 7: Step-by-Step Getting Started (First 48 Hours)

### Hour 0-1: Laptop Setup

* \[ ] Install Ubuntu 22.04 (or use VM/WSL if you have Windows/Mac)
* \[ ] Run: `sudo apt update \&\& sudo apt upgrade`
* \[ ] Install Git, Python3, pip3

### Hour 1-2: Install ROS 2 Humble

```bash
# Add ROS repository
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | sudo apt-key add -
echo "deb \[arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb\_release -cs) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install
sudo apt update
sudo apt install ros-humble-desktop
echo "source /opt/ros/humble/setup.bash" >> \~/.bashrc
source \~/.bashrc
```

### Hour 2-3: Test ROS 2 Installation

```bash
# Terminal 1: Run a listener
ros2 run demo\_nodes\_cpp listener

# Terminal 2: Run a talker
ros2 run demo\_nodes\_cpp talker

# Should see messages passing between terminals
```

### Hour 3-4: Install PX4

```bash
# Clone PX4
cd \~
git clone https://github.com/PX4/PX4-Autopilot.git --branch main
cd PX4-Autopilot

# Run setup script
bash ./Tools/setup/ubuntu.sh

# Build
make px4\_sitl
```

### Hour 4-5: Install Gazebo

```bash
sudo apt install ros-humble-gazebo-ros
sudo apt install gazebo
```

### Hour 5-6: First Simulation

```bash
cd \~/PX4-Autopilot
# This should launch Gazebo with a drone
make px4\_sitl gazebo-classic
```

You should see Gazebo window open with a drone model. If yes, celebrate – basic setup is done!

### Hour 6-12: Complete One ROS 2 Tutorial

Follow: docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools.html

By end of day 1, you'll have:

* Working ROS 2 installation
* Working PX4 + Gazebo simulation
* Understanding of ROS 2 concepts

By end of day 2, aim to:

* Make a drone takeoff in Gazebo via ROS 2 command
* Understand the complete information flow: your Python script → ROS 2 topic → PX4 → Gazebo → drone moves

\---

## Part 8: Common Mistakes to Avoid

### Mistake 1: Trying to Build Hardware Before Proving Software Works

**What happens**: You spend 3 weeks building 4 drones, then discover your coordination algorithm crashes in Gazebo. Now you have broken hardware and broken software.

**Avoid it**: Prove your algorithm works perfectly in Gazebo simulation with 5 virtual drones for at least one week before building real hardware.

### Mistake 2: Underestimating PID Tuning Time

**What happens**: Algorithm works in simulation, but real drones are too unstable to fly formation. You spend a week tuning PID values on each drone.

**Avoid it**: Plan 1-2 weeks for real hardware tuning. In simulation, dynamics are perfect; real life has noise, wind, calibration errors.

### Mistake 3: Launching 4 Real Drones Simultaneously Without Testing Singles

**What happens**: You power on 4 drones at once, they all take off chaotically, collide, battery dies, you're sad.

**Avoid it**:

1. Test one drone in isolation for 10 flights minimum
2. Add second drone, test formation for 5 flights
3. Add third, test, repeat
4. Only after all are proven, fly as full swarm

### Mistake 4: Not Maintaining Detailed Logs

**What happens**: Drone crashes during mission, you have no idea why. Was it a dead battery? Communication glitch? Bug in your code?

**Avoid it**:

* Use ROS 2 rosbag to record all topics during every flight
* Review logs after every crash: "drone lost GPS signal at 2:34:45, then entered failsafe mode"
* Version control all your code with clear commit messages
* Document every parameter change: "Changed PID gain from 1.0 to 1.5, drone now more responsive"

### Mistake 5: Ignoring Safety

**What happens**: Battery swells up and catches fire, or loose prop flies off and cuts you.

**Avoid it**:

* Always remove propellers before ground testing code
* Use LiPo battery bags during charging/storage
* Inspect props for cracks before every flight
* Never stand in front of or above a spinning drone
* Have a fire extinguisher nearby (not a joke)

\---

## Part 9: Success Criteria \& Competition Readiness

### Minimum Viable Swarm (what you need to be taken seriously)

Your swarm should be able to:

1. **Autonomous Deployment**:

   * All drones arm and take off without human control
   * Can handle minor GPS/sensor noise
2. **Formation Flying**:

   * Maintain formation (triangle, line, or custom shape) for 1+ minutes
   * Formation error (how far from perfect shape) is less than 1 meter
3. **Graceful Degradation**:

   * If one drone loses communication for 5 seconds, others don't crash
   * If one drone is removed from swarm, others adapt formation and continue
4. **Mission Execution**:

   * Drones can complete a pre-planned sequence (move forward, turn, return) without operator intervention
   * Takes less than 2 minutes per mission (battery constraint)
5. **Safe Failure**:

   * If anything goes wrong, drones land automatically (don't crash into people)
   * No single point of failure that causes immediate crash

### Nice-to-Have Features (Impress Judges)

* Obstacle avoidance: swarm detects obstacles and routes around them
* Dynamic formation change: swarm morphs from line to triangle mid-flight
* Leaderless control: formation persists even if leader goes offline
* Area coverage: drones collectively sweep a region
* Multi-layer formation: drones hover at different altitudes while maintaining formation

\---

## Part 10: Resource Links \& Documentation

### Official Documentation

* PX4 Autopilot: docs.px4.io
* ROS 2 Humble: docs.ros.org/en/humble/
* Gazebo: gazebosim.org/docs
* QGroundControl: docs.qgroundcontrol.com
* Crazyflie: crazyflie.io/documentation

### GitHub Repositories to Study

* PX4 Swarm Controller: github.com/artastier/PX4\_Swarm\_Controller
* MAVSDK-Python: github.com/mavlink/MAVSDK-Python
* Crazyflie Firmware: github.com/bitcraze/crazyflie-firmware
* ROS 2 Swarm Examples: Various authors, search "ROS 2 swarm formation"

### YouTube Channels

* ETH Zurich Robotics (especially quadrotor control)
* ROS 2 Tutorials (official)
* RIIS Tutorials (PX4 + ROS 2)
* Crazyflie tutorials (Bitcraze official)

### Academic Papers (Conceptual Understanding)

* Distributed Formation Control: Kumar \& Beard (2005)
* Consensus in Multi-Agent Systems: Olfati-Saber \& Murray (2004)
* Collision Avoidance in Swarms: Hönig et al. (2016)

\---

## Final Advice: You Can Do This

You have 8-12 weeks to build a working swarm drone prototype. That's genuinely achievable if you stay focused and avoid the common pitfalls above.

The biggest risk isn't that the problem is too hard – it's that you'll spend weeks debugging simulation instead of moving to hardware, or trying to implement an advanced algorithm when basic formation would already be impressive.

**Your winning strategy**:

1. Week 1-2: Get software environment working, understand basics
2. Week 3-5: Prove single-drone and 2-drone autonomy in simulation
3. Week 6-7: Transition to real hardware, get formation flying
4. Week 8-10: Polish, test edge cases, add robustness
5. Week 11-12: Practice competition scenario, create backups

Remember: a swarm of 3 reliable drones flying formation beats a swarm of 5 drones that crash every third mission. Start small, build reliability, expand capability.

You've got this. Build something awesome.

\---

**Document Created**: May 2026  
**For**: Beginner autonomous swarm drone competition team  
**Next Action**: Print this out, choose your competition, buy hardware, and start Week 1 setup.

