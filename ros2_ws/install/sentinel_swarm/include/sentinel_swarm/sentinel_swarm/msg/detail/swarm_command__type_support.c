// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sentinel_swarm/msg/detail/swarm_command__rosidl_typesupport_introspection_c.h"
#include "sentinel_swarm/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sentinel_swarm/msg/detail/swarm_command__functions.h"
#include "sentinel_swarm/msg/detail/swarm_command__struct.h"


// Include directives for member types
// Member `command_type`
// Member `formation_type`
#include "rosidl_runtime_c/string_functions.h"
// Member `target_point`
#include "geometry_msgs/msg/point.h"
// Member `target_point`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sentinel_swarm__msg__SwarmCommand__init(message_memory);
}

void sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_fini_function(void * message_memory)
{
  sentinel_swarm__msg__SwarmCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_member_array[6] = {
  {
    "command_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, command_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "command_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, command_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_point",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, target_point),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "formation_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, formation_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "formation_scale",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, formation_scale),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mission_timeout",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm__msg__SwarmCommand, mission_timeout),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_members = {
  "sentinel_swarm__msg",  // message namespace
  "SwarmCommand",  // message name
  6,  // number of fields
  sizeof(sentinel_swarm__msg__SwarmCommand),
  sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_member_array,  // message members
  sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_type_support_handle = {
  0,
  &sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sentinel_swarm
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sentinel_swarm, msg, SwarmCommand)() {
  sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_type_support_handle.typesupport_identifier) {
    sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sentinel_swarm__msg__SwarmCommand__rosidl_typesupport_introspection_c__SwarmCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
