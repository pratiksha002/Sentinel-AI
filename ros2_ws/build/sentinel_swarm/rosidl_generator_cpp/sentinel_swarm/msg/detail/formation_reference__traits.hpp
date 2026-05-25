// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__TRAITS_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_swarm/msg/detail/formation_reference__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'reference_positions'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'reference_velocities'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace sentinel_swarm
{

namespace msg
{

inline void to_flow_style_yaml(
  const FormationReference & msg,
  std::ostream & out)
{
  out << "{";
  // member: drone_ids
  {
    if (msg.drone_ids.size() == 0) {
      out << "drone_ids: []";
    } else {
      out << "drone_ids: [";
      size_t pending_items = msg.drone_ids.size();
      for (auto item : msg.drone_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: reference_positions
  {
    if (msg.reference_positions.size() == 0) {
      out << "reference_positions: []";
    } else {
      out << "reference_positions: [";
      size_t pending_items = msg.reference_positions.size();
      for (auto item : msg.reference_positions) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: reference_velocities
  {
    if (msg.reference_velocities.size() == 0) {
      out << "reference_velocities: []";
    } else {
      out << "reference_velocities: [";
      size_t pending_items = msg.reference_velocities.size();
      for (auto item : msg.reference_velocities) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: formation_error
  {
    out << "formation_error: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_error, out);
    out << ", ";
  }

  // member: is_formation_valid
  {
    out << "is_formation_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.is_formation_valid, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FormationReference & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: drone_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.drone_ids.size() == 0) {
      out << "drone_ids: []\n";
    } else {
      out << "drone_ids:\n";
      for (auto item : msg.drone_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: reference_positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.reference_positions.size() == 0) {
      out << "reference_positions: []\n";
    } else {
      out << "reference_positions:\n";
      for (auto item : msg.reference_positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: reference_velocities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.reference_velocities.size() == 0) {
      out << "reference_velocities: []\n";
    } else {
      out << "reference_velocities:\n";
      for (auto item : msg.reference_velocities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: formation_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "formation_error: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_error, out);
    out << "\n";
  }

  // member: is_formation_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_formation_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.is_formation_valid, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FormationReference & msg, bool use_flow_style = false)
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
  const sentinel_swarm::msg::FormationReference & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_swarm::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_swarm::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_swarm::msg::FormationReference & msg)
{
  return sentinel_swarm::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_swarm::msg::FormationReference>()
{
  return "sentinel_swarm::msg::FormationReference";
}

template<>
inline const char * name<sentinel_swarm::msg::FormationReference>()
{
  return "sentinel_swarm/msg/FormationReference";
}

template<>
struct has_fixed_size<sentinel_swarm::msg::FormationReference>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_swarm::msg::FormationReference>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_swarm::msg::FormationReference>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__TRAITS_HPP_
