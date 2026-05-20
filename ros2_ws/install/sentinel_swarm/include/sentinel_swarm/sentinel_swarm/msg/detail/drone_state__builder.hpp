// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_swarm:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_swarm/msg/detail/drone_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_swarm
{

namespace msg
{

namespace builder
{

class Init_DroneState_connected_satellites
{
public:
  explicit Init_DroneState_connected_satellites(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  ::sentinel_swarm::msg::DroneState connected_satellites(::sentinel_swarm::msg::DroneState::_connected_satellites_type arg)
  {
    msg_.connected_satellites = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_gps_hdop
{
public:
  explicit Init_DroneState_gps_hdop(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_connected_satellites gps_hdop(::sentinel_swarm::msg::DroneState::_gps_hdop_type arg)
  {
    msg_.gps_hdop = std::move(arg);
    return Init_DroneState_connected_satellites(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_flight_mode
{
public:
  explicit Init_DroneState_flight_mode(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_gps_hdop flight_mode(::sentinel_swarm::msg::DroneState::_flight_mode_type arg)
  {
    msg_.flight_mode = std::move(arg);
    return Init_DroneState_gps_hdop(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_is_healthy
{
public:
  explicit Init_DroneState_is_healthy(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_flight_mode is_healthy(::sentinel_swarm::msg::DroneState::_is_healthy_type arg)
  {
    msg_.is_healthy = std::move(arg);
    return Init_DroneState_flight_mode(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_is_armed
{
public:
  explicit Init_DroneState_is_armed(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_is_healthy is_armed(::sentinel_swarm::msg::DroneState::_is_armed_type arg)
  {
    msg_.is_armed = std::move(arg);
    return Init_DroneState_is_healthy(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_battery_percentage
{
public:
  explicit Init_DroneState_battery_percentage(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_is_armed battery_percentage(::sentinel_swarm::msg::DroneState::_battery_percentage_type arg)
  {
    msg_.battery_percentage = std::move(arg);
    return Init_DroneState_is_armed(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_battery_current
{
public:
  explicit Init_DroneState_battery_current(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_battery_percentage battery_current(::sentinel_swarm::msg::DroneState::_battery_current_type arg)
  {
    msg_.battery_current = std::move(arg);
    return Init_DroneState_battery_percentage(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_battery_voltage
{
public:
  explicit Init_DroneState_battery_voltage(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_battery_current battery_voltage(::sentinel_swarm::msg::DroneState::_battery_voltage_type arg)
  {
    msg_.battery_voltage = std::move(arg);
    return Init_DroneState_battery_current(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_velocity
{
public:
  explicit Init_DroneState_velocity(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_battery_voltage velocity(::sentinel_swarm::msg::DroneState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_DroneState_battery_voltage(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_position
{
public:
  explicit Init_DroneState_position(::sentinel_swarm::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_velocity position(::sentinel_swarm::msg::DroneState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_DroneState_velocity(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

class Init_DroneState_drone_id
{
public:
  Init_DroneState_drone_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneState_position drone_id(::sentinel_swarm::msg::DroneState::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_DroneState_position(msg_);
  }

private:
  ::sentinel_swarm::msg::DroneState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_swarm::msg::DroneState>()
{
  return sentinel_swarm::msg::builder::Init_DroneState_drone_id();
}

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
