// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "sentinel_swarm/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "sentinel_swarm/msg/detail/formation_reference__struct.hpp"

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

#include "fastcdr/Cdr.h"

namespace sentinel_swarm
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sentinel_swarm
cdr_serialize(
  const sentinel_swarm::msg::FormationReference & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sentinel_swarm
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  sentinel_swarm::msg::FormationReference & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sentinel_swarm
get_serialized_size(
  const sentinel_swarm::msg::FormationReference & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sentinel_swarm
max_serialized_size_FormationReference(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace sentinel_swarm

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sentinel_swarm
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, sentinel_swarm, msg, FormationReference)();

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
