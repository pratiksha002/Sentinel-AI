// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_swarm:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_H_
#define SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'flight_mode'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DroneState in the package sentinel_swarm.
/**
  * DroneState.msg - Published by each drone controller
 */
typedef struct sentinel_swarm__msg__DroneState
{
  int32_t drone_id;
  geometry_msgs__msg__Point position;
  geometry_msgs__msg__Vector3 velocity;
  float battery_voltage;
  float battery_current;
  float battery_percentage;
  bool is_armed;
  bool is_healthy;
  rosidl_runtime_c__String flight_mode;
  float gps_hdop;
  int32_t connected_satellites;
} sentinel_swarm__msg__DroneState;

// Struct for a sequence of sentinel_swarm__msg__DroneState.
typedef struct sentinel_swarm__msg__DroneState__Sequence
{
  sentinel_swarm__msg__DroneState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_swarm__msg__DroneState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_H_
