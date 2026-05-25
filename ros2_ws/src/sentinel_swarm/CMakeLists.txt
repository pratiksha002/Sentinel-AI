cmake_minimum_required(VERSION 3.8)
project(sentinel_swarm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Generate custom message types
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DroneState.msg"
  "msg/SwarmCommand.msg"
  "msg/FormationReference.msg"
  DEPENDENCIES geometry_msgs sensor_msgs std_msgs
)

# Python setup
find_package(ament_cmake_python REQUIRED)
find_package(Python3 REQUIRED)

ament_python_install_package(swarm_core)

# Install Python executable scripts
install(PROGRAMS
  swarm_core/swarm_coordinator.py
  swarm_core/mission_planner.py
  swarm_core/drone_controller.py
  swarm_core/swarm_monitor.py
  swarm_core/gazebo_bridge.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install config, launch, and other directories
install(DIRECTORY
  config
  launch
  gazebo
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
