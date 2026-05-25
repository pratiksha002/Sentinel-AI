// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'target_point'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_swarm__msg__SwarmCommand __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_swarm__msg__SwarmCommand __declspec(deprecated)
#endif

namespace sentinel_swarm
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SwarmCommand_
{
  using Type = SwarmCommand_<ContainerAllocator>;

  explicit SwarmCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_point(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command_id = 0l;
      this->command_type = "";
      this->formation_type = "";
      this->formation_scale = 0.0f;
      this->mission_timeout = 0.0f;
    }
  }

  explicit SwarmCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command_type(_alloc),
    target_point(_alloc, _init),
    formation_type(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command_id = 0l;
      this->command_type = "";
      this->formation_type = "";
      this->formation_scale = 0.0f;
      this->mission_timeout = 0.0f;
    }
  }

  // field types and members
  using _command_id_type =
    int32_t;
  _command_id_type command_id;
  using _command_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _command_type_type command_type;
  using _target_point_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _target_point_type target_point;
  using _formation_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _formation_type_type formation_type;
  using _formation_scale_type =
    float;
  _formation_scale_type formation_scale;
  using _mission_timeout_type =
    float;
  _mission_timeout_type mission_timeout;

  // setters for named parameter idiom
  Type & set__command_id(
    const int32_t & _arg)
  {
    this->command_id = _arg;
    return *this;
  }
  Type & set__command_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->command_type = _arg;
    return *this;
  }
  Type & set__target_point(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->target_point = _arg;
    return *this;
  }
  Type & set__formation_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->formation_type = _arg;
    return *this;
  }
  Type & set__formation_scale(
    const float & _arg)
  {
    this->formation_scale = _arg;
    return *this;
  }
  Type & set__mission_timeout(
    const float & _arg)
  {
    this->mission_timeout = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_swarm__msg__SwarmCommand
    std::shared_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_swarm__msg__SwarmCommand
    std::shared_ptr<sentinel_swarm::msg::SwarmCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SwarmCommand_ & other) const
  {
    if (this->command_id != other.command_id) {
      return false;
    }
    if (this->command_type != other.command_type) {
      return false;
    }
    if (this->target_point != other.target_point) {
      return false;
    }
    if (this->formation_type != other.formation_type) {
      return false;
    }
    if (this->formation_scale != other.formation_scale) {
      return false;
    }
    if (this->mission_timeout != other.mission_timeout) {
      return false;
    }
    return true;
  }
  bool operator!=(const SwarmCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SwarmCommand_

// alias to use template instance with default allocator
using SwarmCommand =
  sentinel_swarm::msg::SwarmCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__STRUCT_HPP_
