// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__BUILDER_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_swarm/msg/detail/formation_reference__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_swarm
{

namespace msg
{

namespace builder
{

class Init_FormationReference_is_formation_valid
{
public:
  explicit Init_FormationReference_is_formation_valid(::sentinel_swarm::msg::FormationReference & msg)
  : msg_(msg)
  {}
  ::sentinel_swarm::msg::FormationReference is_formation_valid(::sentinel_swarm::msg::FormationReference::_is_formation_valid_type arg)
  {
    msg_.is_formation_valid = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_swarm::msg::FormationReference msg_;
};

class Init_FormationReference_formation_error
{
public:
  explicit Init_FormationReference_formation_error(::sentinel_swarm::msg::FormationReference & msg)
  : msg_(msg)
  {}
  Init_FormationReference_is_formation_valid formation_error(::sentinel_swarm::msg::FormationReference::_formation_error_type arg)
  {
    msg_.formation_error = std::move(arg);
    return Init_FormationReference_is_formation_valid(msg_);
  }

private:
  ::sentinel_swarm::msg::FormationReference msg_;
};

class Init_FormationReference_reference_velocities
{
public:
  explicit Init_FormationReference_reference_velocities(::sentinel_swarm::msg::FormationReference & msg)
  : msg_(msg)
  {}
  Init_FormationReference_formation_error reference_velocities(::sentinel_swarm::msg::FormationReference::_reference_velocities_type arg)
  {
    msg_.reference_velocities = std::move(arg);
    return Init_FormationReference_formation_error(msg_);
  }

private:
  ::sentinel_swarm::msg::FormationReference msg_;
};

class Init_FormationReference_reference_positions
{
public:
  explicit Init_FormationReference_reference_positions(::sentinel_swarm::msg::FormationReference & msg)
  : msg_(msg)
  {}
  Init_FormationReference_reference_velocities reference_positions(::sentinel_swarm::msg::FormationReference::_reference_positions_type arg)
  {
    msg_.reference_positions = std::move(arg);
    return Init_FormationReference_reference_velocities(msg_);
  }

private:
  ::sentinel_swarm::msg::FormationReference msg_;
};

class Init_FormationReference_drone_ids
{
public:
  Init_FormationReference_drone_ids()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FormationReference_reference_positions drone_ids(::sentinel_swarm::msg::FormationReference::_drone_ids_type arg)
  {
    msg_.drone_ids = std::move(arg);
    return Init_FormationReference_reference_positions(msg_);
  }

private:
  ::sentinel_swarm::msg::FormationReference msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_swarm::msg::FormationReference>()
{
  return sentinel_swarm::msg::builder::Init_FormationReference_drone_ids();
}

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__BUILDER_HPP_
