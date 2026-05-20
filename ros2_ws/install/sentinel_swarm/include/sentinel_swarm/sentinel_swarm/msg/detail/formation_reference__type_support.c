// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sentinel_swarm/msg/detail/formation_reference__rosidl_typesupport_introspection_c.h"
#include "sentinel_swarm/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sentinel_swarm/msg/detail/formation_reference__functions.h"
#include "sentinel_swarm/msg/detail/formation_reference__struct.h"


// Include directives for member types
// Member `drone_ids`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `reference_positions`
#include "geometry_msgs/msg/point.h"
// Member `reference_positions`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `reference_velocities`
#include "geometry_msgs/msg/vector3.h"
// Member `reference_velocities`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sentinel_swarm__msg__FormationReference__init(message_memory);
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_fini_function(void * message_memory)
{
  sentinel_swarm__msg__FormationReference__fini(message_memory);
}

size_t sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__drone_ids(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__drone_ids(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__drone_ids(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__drone_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__drone_ids(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__drone_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__drone_ids(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__drone_ids(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__reference_positions(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_positions(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_positions(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__reference_positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_positions(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__reference_positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_positions(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__reference_positions(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

size_t sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__reference_velocities(
  const void * untyped_member)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return member->size;
}

const void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_velocities(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_velocities(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__reference_velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Vector3 * item =
    ((const geometry_msgs__msg__Vector3 *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_velocities(untyped_member, index));
  geometry_msgs__msg__Vector3 * value =
    (geometry_msgs__msg__Vector3 *)(untyped_value);
  *value = *item;
}

void sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__reference_velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Vector3 * item =
    ((geometry_msgs__msg__Vector3 *)
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_velocities(untyped_member, index));
  const geometry_msgs__msg__Vector3 * value =
    (const geometry_msgs__msg__Vector3 *)(untyped_value);
  *item = *value;
}

bool sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__reference_velocities(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  geometry_msgs__msg__Vector3__Sequence__fini(member);
  return geometry_msgs__msg__Vector3__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_member_array[5] = {
  {
    "drone_ids",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__FormationReference, drone_ids),  // bytes offset in struct
    NULL,  // default value
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__drone_ids,  // size() function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__drone_ids,  // get_const(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__drone_ids,  // get(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__drone_ids,  // fetch(index, &value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__drone_ids,  // assign(index, value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__drone_ids  // resize(index) function pointer
  },
  {
    "reference_positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__FormationReference, reference_positions),  // bytes offset in struct
    NULL,  // default value
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__reference_positions,  // size() function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_positions,  // get_const(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_positions,  // get(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__reference_positions,  // fetch(index, &value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__reference_positions,  // assign(index, value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__reference_positions  // resize(index) function pointer
  },
  {
    "reference_velocities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__FormationReference, reference_velocities),  // bytes offset in struct
    NULL,  // default value
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__size_function__FormationReference__reference_velocities,  // size() function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_const_function__FormationReference__reference_velocities,  // get_const(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__get_function__FormationReference__reference_velocities,  // get(index) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__fetch_function__FormationReference__reference_velocities,  // fetch(index, &value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__assign_function__FormationReference__reference_velocities,  // assign(index, value) function pointer
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__resize_function__FormationReference__reference_velocities  // resize(index) function pointer
  },
  {
    "formation_error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__FormationReference, formation_error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_formation_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__FormationReference, is_formation_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_members = {
  "sentinel_swarm__msg",  // message namespace
  "FormationReference",  // message name
  5,  // number of fields
  sizeof(sentinel_swarm__msg__FormationReference),
  sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_member_array,  // message members
  sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_init_function,  // function to initialize message memory (memory has to be allocated)
  sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_type_support_handle = {
  0,
  &sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sentinel_swarm
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sentinel_swarm, msg, FormationReference)() {
  sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_type_support_handle.typesupport_identifier) {
    sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sentinel_swarm__msg__FormationReference__rosidl_typesupport_introspection_c__FormationReference_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
