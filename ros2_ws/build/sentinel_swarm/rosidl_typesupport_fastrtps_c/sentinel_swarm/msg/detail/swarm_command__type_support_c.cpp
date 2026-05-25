// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice
#include "sentinel_swarm/msg/detail/swarm_command__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "sentinel_swarm/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "sentinel_swarm/msg/detail/swarm_command__struct.h"
#include "sentinel_swarm/msg/detail/swarm_command__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "geometry_msgs/msg/detail/point__functions.h"  // target_point
#include "rosidl_runtime_c/string.h"  // command_type, formation_type
#include "rosidl_runtime_c/string_functions.h"  // command_type, formation_type

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_sentinel_swarm
size_t get_serialized_size_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_sentinel_swarm
size_t max_serialized_size_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_sentinel_swarm
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point)();


using _SwarmCommand__ros_msg_type = sentinel_swarm__msg__SwarmCommand;

static bool _SwarmCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SwarmCommand__ros_msg_type * ros_message = static_cast<const _SwarmCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: command_id
  {
    cdr << ros_message->command_id;
  }

  // Field name: command_type
  {
    const rosidl_runtime_c__String * str = &ros_message->command_type;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: target_point
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->target_point, cdr))
    {
      return false;
    }
  }

  // Field name: formation_type
  {
    const rosidl_runtime_c__String * str = &ros_message->formation_type;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: formation_scale
  {
    cdr << ros_message->formation_scale;
  }

  // Field name: mission_timeout
  {
    cdr << ros_message->mission_timeout;
  }

  return true;
}

static bool _SwarmCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SwarmCommand__ros_msg_type * ros_message = static_cast<_SwarmCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: command_id
  {
    cdr >> ros_message->command_id;
  }

  // Field name: command_type
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->command_type.data) {
      rosidl_runtime_c__String__init(&ros_message->command_type);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->command_type,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'command_type'\n");
      return false;
    }
  }

  // Field name: target_point
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->target_point))
    {
      return false;
    }
  }

  // Field name: formation_type
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->formation_type.data) {
      rosidl_runtime_c__String__init(&ros_message->formation_type);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->formation_type,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'formation_type'\n");
      return false;
    }
  }

  // Field name: formation_scale
  {
    cdr >> ros_message->formation_scale;
  }

  // Field name: mission_timeout
  {
    cdr >> ros_message->mission_timeout;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_swarm
size_t get_serialized_size_sentinel_swarm__msg__SwarmCommand(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SwarmCommand__ros_msg_type * ros_message = static_cast<const _SwarmCommand__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name command_id
  {
    size_t item_size = sizeof(ros_message->command_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name command_type
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->command_type.size + 1);
  // field.name target_point

  current_alignment += get_serialized_size_geometry_msgs__msg__Point(
    &(ros_message->target_point), current_alignment);
  // field.name formation_type
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->formation_type.size + 1);
  // field.name formation_scale
  {
    size_t item_size = sizeof(ros_message->formation_scale);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mission_timeout
  {
    size_t item_size = sizeof(ros_message->mission_timeout);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SwarmCommand__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_sentinel_swarm__msg__SwarmCommand(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_swarm
size_t max_serialized_size_sentinel_swarm__msg__SwarmCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: command_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: command_type
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: target_point
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: formation_type
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: formation_scale
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mission_timeout
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = sentinel_swarm__msg__SwarmCommand;
    is_plain =
      (
      offsetof(DataType, mission_timeout) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SwarmCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_sentinel_swarm__msg__SwarmCommand(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SwarmCommand = {
  "sentinel_swarm::msg",
  "SwarmCommand",
  _SwarmCommand__cdr_serialize,
  _SwarmCommand__cdr_deserialize,
  _SwarmCommand__get_serialized_size,
  _SwarmCommand__max_serialized_size
};

static rosidl_message_type_support_t _SwarmCommand__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SwarmCommand,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sentinel_swarm, msg, SwarmCommand)() {
  return &_SwarmCommand__type_support;
}

#if defined(__cplusplus)
}
#endif
