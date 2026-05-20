// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sentinel_swarm/msg/detail/formation_reference__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace sentinel_swarm
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void FormationReference_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sentinel_swarm::msg::FormationReference(_init);
}

void FormationReference_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sentinel_swarm::msg::FormationReference *>(message_memory);
  typed_message->~FormationReference();
}

size_t size_function__FormationReference__drone_ids(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__FormationReference__drone_ids(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__FormationReference__drone_ids(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__FormationReference__drone_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__FormationReference__drone_ids(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__FormationReference__drone_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__FormationReference__drone_ids(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

void resize_function__FormationReference__drone_ids(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__FormationReference__reference_positions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return member->size();
}

const void * get_const_function__FormationReference__reference_positions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void * get_function__FormationReference__reference_positions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void fetch_function__FormationReference__reference_positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Point *>(
    get_const_function__FormationReference__reference_positions(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Point *>(untyped_value);
  value = item;
}

void assign_function__FormationReference__reference_positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Point *>(
    get_function__FormationReference__reference_positions(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Point *>(untyped_value);
  item = value;
}

void resize_function__FormationReference__reference_positions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  member->resize(size);
}

size_t size_function__FormationReference__reference_velocities(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Vector3> *>(untyped_member);
  return member->size();
}

const void * get_const_function__FormationReference__reference_velocities(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Vector3> *>(untyped_member);
  return &member[index];
}

void * get_function__FormationReference__reference_velocities(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Vector3> *>(untyped_member);
  return &member[index];
}

void fetch_function__FormationReference__reference_velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Vector3 *>(
    get_const_function__FormationReference__reference_velocities(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Vector3 *>(untyped_value);
  value = item;
}

void assign_function__FormationReference__reference_velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Vector3 *>(
    get_function__FormationReference__reference_velocities(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Vector3 *>(untyped_value);
  item = value;
}

void resize_function__FormationReference__reference_velocities(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Vector3> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember FormationReference_message_member_array[5] = {
  {
    "drone_ids",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm::msg::FormationReference, drone_ids),  // bytes offset in struct
    nullptr,  // default value
    size_function__FormationReference__drone_ids,  // size() function pointer
    get_const_function__FormationReference__drone_ids,  // get_const(index) function pointer
    get_function__FormationReference__drone_ids,  // get(index) function pointer
    fetch_function__FormationReference__drone_ids,  // fetch(index, &value) function pointer
    assign_function__FormationReference__drone_ids,  // assign(index, value) function pointer
    resize_function__FormationReference__drone_ids  // resize(index) function pointer
  },
  {
    "reference_positions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Point>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm::msg::FormationReference, reference_positions),  // bytes offset in struct
    nullptr,  // default value
    size_function__FormationReference__reference_positions,  // size() function pointer
    get_const_function__FormationReference__reference_positions,  // get_const(index) function pointer
    get_function__FormationReference__reference_positions,  // get(index) function pointer
    fetch_function__FormationReference__reference_positions,  // fetch(index, &value) function pointer
    assign_function__FormationReference__reference_positions,  // assign(index, value) function pointer
    resize_function__FormationReference__reference_positions  // resize(index) function pointer
  },
  {
    "reference_velocities",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Vector3>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm::msg::FormationReference, reference_velocities),  // bytes offset in struct
    nullptr,  // default value
    size_function__FormationReference__reference_velocities,  // size() function pointer
    get_const_function__FormationReference__reference_velocities,  // get_const(index) function pointer
    get_function__FormationReference__reference_velocities,  // get(index) function pointer
    fetch_function__FormationReference__reference_velocities,  // fetch(index, &value) function pointer
    assign_function__FormationReference__reference_velocities,  // assign(index, value) function pointer
    resize_function__FormationReference__reference_velocities  // resize(index) function pointer
  },
  {
    "formation_error",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm::msg::FormationReference, formation_error),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "is_formation_valid",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_swarm::msg::FormationReference, is_formation_valid),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers FormationReference_message_members = {
  "sentinel_swarm::msg",  // message namespace
  "FormationReference",  // message name
  5,  // number of fields
  sizeof(sentinel_swarm::msg::FormationReference),
  FormationReference_message_member_array,  // message members
  FormationReference_init_function,  // function to initialize message memory (memory has to be allocated)
  FormationReference_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t FormationReference_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &FormationReference_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace sentinel_swarm


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<sentinel_swarm::msg::FormationReference>()
{
  return &::sentinel_swarm::msg::rosidl_typesupport_introspection_cpp::FormationReference_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sentinel_swarm, msg, FormationReference)() {
  return &::sentinel_swarm::msg::rosidl_typesupport_introspection_cpp::FormationReference_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
