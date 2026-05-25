// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__TRAITS_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_swarm/msg/detail/swarm_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'target_point'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace sentinel_swarm
{

namespace msg
{

inline void to_flow_style_yaml(
  const SwarmCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: command_id
  {
    out << "command_id: ";
    rosidl_generator_traits::value_to_yaml(msg.command_id, out);
    out << ", ";
  }

  // member: command_type
  {
    out << "command_type: ";
    rosidl_generator_traits::value_to_yaml(msg.command_type, out);
    out << ", ";
  }

  // member: target_point
  {
    out << "target_point: ";
    to_flow_style_yaml(msg.target_point, out);
    out << ", ";
  }

  // member: formation_type
  {
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << ", ";
  }

  // member: formation_scale
  {
    out << "formation_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_scale, out);
    out << ", ";
  }

  // member: mission_timeout
  {
    out << "mission_timeout: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_timeout, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SwarmCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command_id: ";
    rosidl_generator_traits::value_to_yaml(msg.command_id, out);
    out << "\n";
  }

  // member: command_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command_type: ";
    rosidl_generator_traits::value_to_yaml(msg.command_type, out);
    out << "\n";
  }

  // member: target_point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_point:\n";
    to_block_style_yaml(msg.target_point, out, indentation + 2);
  }

  // member: formation_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << "\n";
  }

  // member: formation_scale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "formation_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_scale, out);
    out << "\n";
  }

  // member: mission_timeout
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_timeout: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_timeout, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SwarmCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace sentinel_swarm

namespace rosidl_generator_traits
{

[[deprecated("use sentinel_swarm::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sentinel_swarm::msg::SwarmCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_swarm::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_swarm::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_swarm::msg::SwarmCommand & msg)
{
  return sentinel_swarm::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_swarm::msg::SwarmCommand>()
{
  return "sentinel_swarm::msg::SwarmCommand";
}

template<>
inline const char * name<sentinel_swarm::msg::SwarmCommand>()
{
  return "sentinel_swarm/msg/SwarmCommand";
}

template<>
struct has_fixed_size<sentinel_swarm::msg::SwarmCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_swarm::msg::SwarmCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_swarm::msg::SwarmCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__TRAITS_HPP_
