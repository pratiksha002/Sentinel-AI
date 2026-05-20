// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_H_
#define SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'drone_ids'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'reference_positions'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'reference_velocities'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/FormationReference in the package sentinel_swarm.
/**
  * FormationReference.msg - Published by coordinator
 */
typedef struct sentinel_swarm__msg__FormationReference
{
  rosidl_runtime_c__int32__Sequence drone_ids;
  geometry_msgs__msg__Point__Sequence reference_positions;
  geometry_msgs__msg__Vector3__Sequence reference_velocities;
  float formation_error;
  bool is_formation_valid;
} sentinel_swarm__msg__FormationReference;

// Struct for a sequence of sentinel_swarm__msg__FormationReference.
typedef struct sentinel_swarm__msg__FormationReference__Sequence
{
  sentinel_swarm__msg__FormationReference * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_swarm__msg__FormationReference__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_H_
