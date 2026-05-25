// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__BUILDER_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_swarm/msg/detail/swarm_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_swarm
{

namespace msg
{

namespace builder
{

class Init_SwarmCommand_mission_timeout
{
public:
  explicit Init_SwarmCommand_mission_timeout(::sentinel_swarm::msg::SwarmCommand & msg)
  : msg_(msg)
  {}
  ::sentinel_swarm::msg::SwarmCommand mission_timeout(::sentinel_swarm::msg::SwarmCommand::_mission_timeout_type arg)
  {
    msg_.mission_timeout = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

class Init_SwarmCommand_formation_scale
{
public:
  explicit Init_SwarmCommand_formation_scale(::sentinel_swarm::msg::SwarmCommand & msg)
  : msg_(msg)
  {}
  Init_SwarmCommand_mission_timeout formation_scale(::sentinel_swarm::msg::SwarmCommand::_formation_scale_type arg)
  {
    msg_.formation_scale = std::move(arg);
    return Init_SwarmCommand_mission_timeout(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

class Init_SwarmCommand_formation_type
{
public:
  explicit Init_SwarmCommand_formation_type(::sentinel_swarm::msg::SwarmCommand & msg)
  : msg_(msg)
  {}
  Init_SwarmCommand_formation_scale formation_type(::sentinel_swarm::msg::SwarmCommand::_formation_type_type arg)
  {
    msg_.formation_type = std::move(arg);
    return Init_SwarmCommand_formation_scale(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

class Init_SwarmCommand_target_point
{
public:
  explicit Init_SwarmCommand_target_point(::sentinel_swarm::msg::SwarmCommand & msg)
  : msg_(msg)
  {}
  Init_SwarmCommand_formation_type target_point(::sentinel_swarm::msg::SwarmCommand::_target_point_type arg)
  {
    msg_.target_point = std::move(arg);
    return Init_SwarmCommand_formation_type(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

class Init_SwarmCommand_command_type
{
public:
  explicit Init_SwarmCommand_command_type(::sentinel_swarm::msg::SwarmCommand & msg)
  : msg_(msg)
  {}
  Init_SwarmCommand_target_point command_type(::sentinel_swarm::msg::SwarmCommand::_command_type_type arg)
  {
    msg_.command_type = std::move(arg);
    return Init_SwarmCommand_target_point(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

class Init_SwarmCommand_command_id
{
public:
  Init_SwarmCommand_command_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SwarmCommand_command_type command_id(::sentinel_swarm::msg::SwarmCommand::_command_id_type arg)
  {
    msg_.command_id = std::move(arg);
    return Init_SwarmCommand_command_type(msg_);
  }

private:
  ::sentinel_swarm::msg::SwarmCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_swarm::msg::SwarmCommand>()
{
  return sentinel_swarm::msg::builder::Init_SwarmCommand_command_id();
}

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__BUILDER_HPP_
