// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_swarm:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__TRAITS_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_swarm/msg/detail/drone_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace sentinel_swarm
{

namespace msg
{

inline void to_flow_style_yaml(
  const DroneState & msg,
  std::ostream & out)
{
  out << "{";
  // member: drone_id
  {
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    to_flow_style_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: battery_voltage
  {
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << ", ";
  }

  // member: battery_current
  {
    out << "battery_current: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_current, out);
    out << ", ";
  }

  // member: battery_percentage
  {
    out << "battery_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percentage, out);
    out << ", ";
  }

  // member: is_armed
  {
    out << "is_armed: ";
    rosidl_generator_traits::value_to_yaml(msg.is_armed, out);
    out << ", ";
  }

  // member: is_healthy
  {
    out << "is_healthy: ";
    rosidl_generator_traits::value_to_yaml(msg.is_healthy, out);
    out << ", ";
  }

  // member: flight_mode
  {
    out << "flight_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.flight_mode, out);
    out << ", ";
  }

  // member: gps_hdop
  {
    out << "gps_hdop: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_hdop, out);
    out << ", ";
  }

  // member: connected_satellites
  {
    out << "connected_satellites: ";
    rosidl_generator_traits::value_to_yaml(msg.connected_satellites, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DroneState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: drone_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity:\n";
    to_block_style_yaml(msg.velocity, out, indentation + 2);
  }

  // member: battery_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << "\n";
  }

  // member: battery_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_current: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_current, out);
    out << "\n";
  }

  // member: battery_percentage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percentage, out);
    out << "\n";
  }

  // member: is_armed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_armed: ";
    rosidl_generator_traits::value_to_yaml(msg.is_armed, out);
    out << "\n";
  }

  // member: is_healthy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_healthy: ";
    rosidl_generator_traits::value_to_yaml(msg.is_healthy, out);
    out << "\n";
  }

  // member: flight_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flight_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.flight_mode, out);
    out << "\n";
  }

  // member: gps_hdop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_hdop: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_hdop, out);
    out << "\n";
  }

  // member: connected_satellites
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "connected_satellites: ";
    rosidl_generator_traits::value_to_yaml(msg.connected_satellites, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DroneState & msg, bool use_flow_style = false)
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
  const sentinel_swarm::msg::DroneState & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_swarm::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_swarm::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_swarm::msg::DroneState & msg)
{
  return sentinel_swarm::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_swarm::msg::DroneState>()
{
  return "sentinel_swarm::msg::DroneState";
}

template<>
inline const char * name<sentinel_swarm::msg::DroneState>()
{
  return "sentinel_swarm/msg/DroneState";
}

template<>
struct has_fixed_size<sentinel_swarm::msg::DroneState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_swarm::msg::DroneState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_swarm::msg::DroneState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__TRAITS_HPP_
