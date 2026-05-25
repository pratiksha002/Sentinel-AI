// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_swarm:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_swarm__msg__DroneState __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_swarm__msg__DroneState __declspec(deprecated)
#endif

namespace sentinel_swarm
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneState_
{
  using Type = DroneState_<ContainerAllocator>;

  explicit DroneState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init),
    velocity(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0l;
      this->battery_voltage = 0.0f;
      this->battery_current = 0.0f;
      this->battery_percentage = 0.0f;
      this->is_armed = false;
      this->is_healthy = false;
      this->flight_mode = "";
      this->gps_hdop = 0.0f;
      this->connected_satellites = 0l;
    }
  }

  explicit DroneState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc, _init),
    velocity(_alloc, _init),
    flight_mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0l;
      this->battery_voltage = 0.0f;
      this->battery_current = 0.0f;
      this->battery_percentage = 0.0f;
      this->is_armed = false;
      this->is_healthy = false;
      this->flight_mode = "";
      this->gps_hdop = 0.0f;
      this->connected_satellites = 0l;
    }
  }

  // field types and members
  using _drone_id_type =
    int32_t;
  _drone_id_type drone_id;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _battery_voltage_type =
    float;
  _battery_voltage_type battery_voltage;
  using _battery_current_type =
    float;
  _battery_current_type battery_current;
  using _battery_percentage_type =
    float;
  _battery_percentage_type battery_percentage;
  using _is_armed_type =
    bool;
  _is_armed_type is_armed;
  using _is_healthy_type =
    bool;
  _is_healthy_type is_healthy;
  using _flight_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _flight_mode_type flight_mode;
  using _gps_hdop_type =
    float;
  _gps_hdop_type gps_hdop;
  using _connected_satellites_type =
    int32_t;
  _connected_satellites_type connected_satellites;

  // setters for named parameter idiom
  Type & set__drone_id(
    const int32_t & _arg)
  {
    this->drone_id = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__battery_voltage(
    const float & _arg)
  {
    this->battery_voltage = _arg;
    return *this;
  }
  Type & set__battery_current(
    const float & _arg)
  {
    this->battery_current = _arg;
    return *this;
  }
  Type & set__battery_percentage(
    const float & _arg)
  {
    this->battery_percentage = _arg;
    return *this;
  }
  Type & set__is_armed(
    const bool & _arg)
  {
    this->is_armed = _arg;
    return *this;
  }
  Type & set__is_healthy(
    const bool & _arg)
  {
    this->is_healthy = _arg;
    return *this;
  }
  Type & set__flight_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->flight_mode = _arg;
    return *this;
  }
  Type & set__gps_hdop(
    const float & _arg)
  {
    this->gps_hdop = _arg;
    return *this;
  }
  Type & set__connected_satellites(
    const int32_t & _arg)
  {
    this->connected_satellites = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_swarm::msg::DroneState_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_swarm::msg::DroneState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::DroneState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::DroneState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_swarm__msg__DroneState
    std::shared_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_swarm__msg__DroneState
    std::shared_ptr<sentinel_swarm::msg::DroneState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneState_ & other) const
  {
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->battery_voltage != other.battery_voltage) {
      return false;
    }
    if (this->battery_current != other.battery_current) {
      return false;
    }
    if (this->battery_percentage != other.battery_percentage) {
      return false;
    }
    if (this->is_armed != other.is_armed) {
      return false;
    }
    if (this->is_healthy != other.is_healthy) {
      return false;
    }
    if (this->flight_mode != other.flight_mode) {
      return false;
    }
    if (this->gps_hdop != other.gps_hdop) {
      return false;
    }
    if (this->connected_satellites != other.connected_satellites) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneState_

// alias to use template instance with default allocator
using DroneState =
  sentinel_swarm::msg::DroneState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
