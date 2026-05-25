# Document 1: Theory & Learning Foundation
## Understanding the Fundamentals Before Building

---

## Phase 1: Research & Understanding (Weeks 1-6)

This phase is pure learning. No code, no hardware, just understanding how everything works. I learned that rushing through this phase costs time later, so I committed to learning properly first.

---

## Week 1: Quadrotor Dynamics & Control Basics

### What I Needed to Understand

**Why is controlling a drone actually hard?**

I watched the ETH Zurich Quadrotor Control lecture and finally understood: a quadrotor is **underactuated**. It has 4 propellers (inputs) but needs to control 6 degrees of freedom (x, y, z position + roll, pitch, yaw orientation). This means it can't do everything - for example, it can't move purely sideways without tilting.

### The Control Hierarchy

This was the key insight that changed how I thought about drones:

```
Level 3: Mission Planning
         "Go to waypoint X" → compute desired velocity

Level 2: Attitude Control  
         "I need velocity [1, 0, 0]" → compute required roll/pitch angles

Level 1: Motor Control
         "Roll 5 degrees" → output power to motors

(PX4 handles Level 1, we write Level 2-3)
```

When I send a velocity command to PX4, it automatically figures out what angles are needed. I don't have to think about motor control - PX4 handles that. This simplified everything.

### Key Learning Resources

**Video**: ETH Zurich "Quadrotor Control" (YouTube, 45 min)
- Watch this first for intuition
- The animations showing forces and moments made everything click

**Reading**: PX4 Concepts & Architecture (docs.px4.io/main/en/concept/)
- Understand how sensors feed into control loops
- See how commands reach motors
- Know what each mode does (stabilize, altitude hold, position hold, offboard)

### What I Learned About Stability

Drones have natural stability through gyro feedback. When the drone tilts, the gyroscope detects it and automatically corrects. This is built into PX4. So I don't have to worry about low-level stabilization - just send high-level commands and PX4 handles the rest.

### Communication Delays Matter

One thing that surprised me: network latency affects how drones respond. If there's 100ms delay between my command and the drone executing it, the swarm can oscillate. Understanding this helped me later when tuning control gains.

### Success Criteria for Week 1

I knew I understood this when I could:
- [ ] Explain why drones are underactuated
- [ ] Draw the control hierarchy without looking
- [ ] Describe what each control loop does
- [ ] Understand why communication delays matter for swarms

---

## Week 2: PID Control Theory

### The Problem I Was Trying to Solve

I kept reading "tune the PID parameters" but didn't understand what P, I, and D actually did. So I looked up Brian Douglas' Control Systems Lectures and everything made sense.

### PID Control Fundamentals

**The Basic Formula**:
```
Output = Kp × Error + Ki × Integral(Error) + Kd × dError/dt
```

**What Each Part Does**:

**P (Proportional)**: Responds immediately to error
- Error = 2 meters away → Push with force 2×Kp
- Too high: overshoots target, oscillates
- Too low: slow to respond

**I (Integral)**: Removes steady-state error over time
- If you're consistently 1 meter away, integral keeps pushing
- Solves problems where proportional alone isn't enough
- Too high: slow oscillations
- Too low: never quite reaches target

**D (Derivative)**: Dampens the system
- Measures how fast error is changing
- If you're moving toward target too fast, apply brake
- Prevents overshooting
- Too high: sluggish response
- Too low: overshoots

### Applying This to Drones

For formation flying, each drone runs a PID controller where the error is "distance from desired formation position":

```python
error = desired_position - current_position
command_velocity = Kp * error + Ki * sum_of_errors + Kd * rate_of_error_change
```

If all drones have the same PID gains, they naturally converge to formation. If one drone has different gains, the swarm oscillates. This is why tuning is critical.

### Learning Resources

**Videos**: Brian Douglas "Control Systems Lectures" (YouTube)
- Part 1: What is feedback control? (why we need it)
- Part 2: The proportional term (Kp)
- Part 3: The integral term (Ki)
- Part 4: The derivative term (Kd)
- Each video ~15 minutes, watch them in order

**Practice**: Interactive PID simulator online (Khan Academy or EveryEng)
- Adjust Kp, see what happens
- Adjust Ki, see what happens
- Adjust Kd, see what happens
- Understand the trade-offs

### Key Insight

PID is everywhere in robotics. Understanding it deeply meant I could debug control problems later instead of just randomly adjusting numbers.

### Success Criteria for Week 2

I knew I got it when I could:
- [ ] Tune a PID controller in online simulator without oscillating
- [ ] Predict what happens when I increase Kp (too fast, overshoots)
- [ ] Explain why derivative term prevents overshoot
- [ ] Understand why swarms need matched PID gains

---

## Week 3: Distributed Algorithms

### Why This Matters for Swarms

I realized: in a real swarm, one drone doesn't know where ALL other drones are. It only knows about neighbors within radio range. So I needed algorithms that work with **incomplete information**.

### Consensus Algorithms

**The Key Insight**: All drones can reach agreement without a leader.

Simple example:
```
Each drone has preferred direction: [North, North, East, South]

Round 1:
  Drone 1 hears: North, East, South → averages → NorthEast
  Drone 2 hears: North, North, South → averages → North
  Drone 3 hears: North, North, East → averages → North
  Drone 4 hears: North, North, East → averages → North

Round 2 (repeat)
  Direction converges: All say North

Result: Agreement without anyone being leader!
```

This is how leaderless swarms work. No central authority, just local interactions.

### Formation Control

**Without consensus**: One drone leads, others follow (easy but fragile)

**With consensus**: All drones are equal, maintain formation shape

Formula:
```
Each drone knows:
  - Its position
  - Neighbors' positions  
  - Desired formation shape

Computes:
  desired_position = own_position + formation_offset_relative_to_neighbors
  
Commands:
  move_towards(desired_position)
```

If one drone fails, others automatically adjust because they're computing based on what they can see, not a predefined leader.

### Learning Resources

**Paper**: "Consensus Problems in Networks of Agents with Switching Topology" (Olfati-Saber & Murray)
- Read sections 1-3 (skip proofs)
- Focus on algorithm description
- Understand the pseudocode

**Video**: Search YouTube for "Consensus Algorithms Explained"
- Find ones with animations
- See how agents reach agreement over time

### What I Realized

Distributed algorithms are fundamentally about:
1. Each agent has limited information
2. Agents do simple local computations
3. Complex global behavior emerges
4. No single point of failure

### Success Criteria for Week 3

I knew I understood when I could:
- [ ] Explain consensus algorithm on paper
- [ ] Understand why it works even with communication loss
- [ ] Describe formation control without a leader
- [ ] Predict what happens when one drone fails

---

## Week 4: ROS 2 Fundamentals

### What is ROS 2?

ROS 2 is a **communication system** for robots. Instead of writing code to handle networking between drones, ROS 2 does it for me.

### The Pub/Sub Model

**Key Concept**: Imagine a bulletin board in the middle of a room.

```
Drone 1 (Publisher):
  "Here's my position: (1.5, 2.0, 3.0)"
  → Posts on bulletin board at topic "/drone1/position"

Swarm Coordinator (Subscriber):
  Reads from bulletin board at "/drone1/position"
  Reads from bulletin board at "/drone2/position"
  Reads from bulletin board at "/drone3/position"
  → Gets all drone positions instantly

Swarm Coordinator (Publisher):
  "Here's drone 1's command: velocity (0.5, 0.2, 0)"
  → Posts on bulletin board at topic "/drone1/command"

Drone 1 (Subscriber):
  Reads from bulletin board at "/drone1/command"
  → Executes the command
```

No direct connections, no complex networking - just publish and subscribe to topics. ROS 2 handles the rest.

### Why This Matters

Without ROS 2:
```python
# Connect to drone 1
drone1_connection = serial.Serial('/dev/ttyUSB0')
# Read position
pos1 = parse_message(drone1_connection.read())
# Connect to drone 2
drone2_connection = socket.socket()
# Read position
pos2 = parse_message(drone2_connection.recv())
# ... repeat for all drones, all message types
# Spaghetti code nightmare
```

With ROS 2:
```python
def position_callback(self, msg):
    self.drone_pos = msg

self.subscriber = self.create_subscription(Point, '/drone1/position', self.position_callback)
# Done. ROS 2 handles connection, parsing, everything.
```

### Learning Resources

**Official**: docs.ros.org/en/humble/Concepts.html
- Read "Nodes", "Topics", "Messages"
- Understanding these 3 concepts is 80% of ROS 2

**Video**: Search YouTube for "ROS 2 Concepts Explained"
- Watch one that shows pub/sub visually

**Practice**: Follow ROS 2 Humble Beginner Tutorials
- Actually run the talker/listener demo
- See pub/sub work in real time

### Namespaces (Critical for Multi-Robot)

With multiple drones, topics need to be separate:
```
/drone1/position
/drone1/velocity_command
/drone1/battery_level

/drone2/position
/drone2/velocity_command
/drone2/battery_level
```

Each drone's topics are in its own namespace. This prevents conflicts and makes code reusable.

### Success Criteria for Week 4

I knew I understood when I could:
- [ ] Explain pub/sub without looking
- [ ] Understand why ROS 2 is better than manual networking
- [ ] Use namespaces correctly for multi-robot systems
- [ ] Design topic structure for 5-drone swarm

---

## Week 5: PX4 Flight Control System

### What is PX4?

PX4 is **flight control software** that runs on the drone's flight controller board. It reads sensors and outputs motor commands continuously (50-100 times per second).

### PX4 Architecture

I visualized it like this:

```
Sensors Input:
  ├─ IMU (acceleration, rotation)
  ├─ GPS (position)
  ├─ Barometer (altitude)
  ├─ Magnetometer (heading)
  └─ Optical flow (motion)

PX4 Core:
  ├─ State Estimation (where am I? what's my velocity?)
  ├─ Attitude Control (what angles do I need?)
  └─ Motor Mixing (which motors get what power?)

Motor Output:
  └─ PWM signals to 4 ESCs
```

### What I Don't Have to Write

The beauty is: **PX4 already does all this**. I don't write state estimation, I don't write motor control. I just send it "go to this velocity" and it figures out the motors.

### Offboard Mode (How I Command Drones)

By default, PX4 follows internal logic. But I can switch it to **Offboard Mode** which means "listen to external commands from my laptop".

Two modes of offboard control:
- **Position Mode**: "Go to this point"
- **Velocity Mode**: "Move at this velocity"

I use velocity mode because it's smoother for swarm control.

### uORB Messages (PX4's Internal Language)

PX4 uses "uORB" messages internally. These get translated to ROS 2 messages by the bridge.

Key messages I need to know:
- `vehicle_status`: Is it armed? Which mode? Battery level?
- `vehicle_odometry`: Current position and velocity
- `offboard_control_mode`: Tell PX4 what I'm sending
- `trajectory_setpoint`: My velocity commands

### Learning Resources

**Official**: docs.px4.io/main/en/concept/
- Architecture overview
- Flight modes explanation
- Offboard control mode details

**Video**: Search YouTube "PX4 System Architecture"
- See sensors → control loops → motors visually

### How I'll Use PX4 in My Code

```
1. Tell PX4: "Be ready for external commands" (offboard mode)
2. Send: "Move at velocity (0.5, 0.2, 0)"
3. PX4 does: sensor fusion → attitude calculation → motor commands
4. Drone moves
5. PX4 sends back: "My position is now (1.5, 2.0, 3.0)"
6. Repeat 50 times per second
```

I don't have to think about steps 3 and 5 - PX4 handles them.

### Success Criteria for Week 5

I knew I understood when I could:
- [ ] Draw PX4 architecture
- [ ] List key messages needed
- [ ] Explain offboard mode
- [ ] Understand the difference between position and velocity control

---

## Week 6: System Integration & Implementation Planning

### Putting It All Together

By week 6, I had learned:
- Quadrotors work through control hierarchy
- PID control is how drones stay stable
- Distributed algorithms enable leaderless swarms
- ROS 2 handles robot communication
- PX4 handles flight control

Now I needed to understand **how they all connect**.

### Complete System Architecture

```
┌─────────────────────────────────────────────────┐
│  YOUR PYTHON CODE (ROS 2 Node)                 │
│  ├─ Reads drone positions via ROS 2 topics     │
│  ├─ Computes formation control commands (PID)  │
│  └─ Sends velocity via ROS 2 topics            │
└────────────────┬────────────────────────────────┘
                 │ (ROS 2 Topics)
┌────────────────▼────────────────────────────────┐
│  ROS 2 Middleware (DDS Protocol)               │
│  Converts ROS 2 messages to network packets    │
└────────────────┬────────────────────────────────┘
                 │ (WiFi or USB)
        ┌────────┴────────┬──────────┬─────────┐
        │                 │          │         │
┌───────▼──┐  ┌──────────▼──┐  ┌───▼────┐  ┌─▼────┐
│  PX4     │  │   PX4       │  │  PX4   │  │ PX4  │
│ Drone 1  │  │  Drone 2    │  │ Drone 3│  │ Drone│
│          │  │             │  │        │  │  4   │
└──────────┘  └─────────────┘  └────────┘  └──────┘
```

### The 5-Layer Stack

When I understood this, everything clicked:

**Layer 1: Your Algorithm (Python)**
- You write this (~1000-1500 lines)
- Formation control, swarm logic

**Layer 2: ROS 2 Middleware**
- Pre-built, you just use it
- Pub/Sub messaging system

**Layer 3: PX4-ROS 2 Bridge**
- Pre-built, already installed
- Translates ROS 2 ↔ PX4 messages

**Layer 4: PX4 Autopilot**
- Pre-built, already in drones
- Flight control, motor commands

**Layer 5: Hardware**
- Drones, motors, batteries
- Physical reality

Your code is Layer 1. Everything else exists already.

### Implementation Strategy

I realized I should:
1. **Week 7-8**: Install everything, verify each layer works
2. **Week 9-12**: Develop code in simulation (test algorithm)
3. **Week 13-16**: Test code with real drones (tune parameters)
4. **Week 17-18**: Practice competition, document

This order minimizes risk. Algorithm problems found in simulation, hardware problems found with real drones.

### Key Insight for Implementation

**Simulation is your insurance policy.**

Spend weeks 9-12 testing every edge case in Gazebo. When you move to real drones week 13, you're confident it works. Real drones are for tuning, not debugging.

### Success Criteria for Week 6

I knew I was ready when I could:
- [ ] Draw complete system architecture
- [ ] Explain how ROS 2 and PX4 work together
- [ ] Understand what I need to code vs. what's pre-built
- [ ] Explain the 5-layer stack without looking

---

## Understanding PID Tuning (Will Come Later)

During weeks 13-16, I'll be tuning PID parameters on real drones. The theory I learned will help me understand what's happening:

- If drones oscillate: increase D term (derivative dampens)
- If drones respond too slowly: increase P term (proportional accelerates)
- If drones never quite reach position: increase I term (integral removes offset)

But this is practical knowledge from weeks 1-6 theory.

---

## Looking Back at Research Phase

By the end of week 6, I had deep understanding but zero implemented code. This felt slow at the time, but:

- Week 9: I wrote control code in hours (not days) because I understood the problem
- Week 13: Tuning was systematic (not random) because I understood PID
- Week 17: I could explain my system to judges because I understood every layer

Rushing through weeks 1-6 would have cost me weeks 9-18.

---

## Recommended Reading Order

If I'm starting fresh:

1. **ETH Zurich Quadrotor Control** (YouTube, 45 min) - Get intuition
2. **PX4 Concepts docs** (1-2 hours) - Understand flight control
3. **Brian Douglas PID videos** (YouTube, 1 hour) - Understand control
4. **Consensus papers** (2-3 hours) - Understand swarm algorithms
5. **ROS 2 Humble tutorials** (2-3 hours) - Hands-on with messaging
6. **PX4 ROS 2 integration docs** (1 hour) - See how they connect

Total: ~12-15 hours of learning for week 1-6 commitment of 15-20 hours/week.

The remaining time in weeks 1-6 was spent:
- Taking detailed notes
- Drawing diagrams
- Writing summaries
- Reflecting on what I learned

This note-taking and reflection is what moved knowledge from "watched a video" to "actually understand".
