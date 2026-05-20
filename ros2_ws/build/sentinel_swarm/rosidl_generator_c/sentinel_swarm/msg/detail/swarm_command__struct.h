// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_H_
#define SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'command_type'
// Member 'formation_type'
#include "rosidl_runtime_c/string.h"
// Member 'target_point'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/SwarmCommand in the package sentinel_swarm.
/**
  * SwarmCommand.msg - Published by mission planner to coordinator
 */
typedef struct sentinel_swarm__msg__SwarmCommand
{
  int32_t command_id;
  rosidl_runtime_c__String command_type;
  geometry_msgs__msg__Point target_point;
  rosidl_runtime_c__String formation_type;
  float formation_scale;
  float mission_timeout;
} sentinel_swarm__msg__SwarmCommand;

// Struct for a sequence of sentinel_swarm__msg__SwarmCommand.
typedef struct sentinel_swarm__msg__SwarmCommand__Sequence
{
  sentinel_swarm__msg__SwarmCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_swarm__msg__SwarmCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_H_
