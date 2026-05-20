// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_swarm:msg/FormationReference.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_HPP_
#define SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'reference_positions'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'reference_velocities'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_swarm__msg__FormationReference __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_swarm__msg__FormationReference __declspec(deprecated)
#endif

namespace sentinel_swarm
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FormationReference_
{
  using Type = FormationReference_<ContainerAllocator>;

  explicit FormationReference_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->formation_error = 0.0f;
      this->is_formation_valid = false;
    }
  }

  explicit FormationReference_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->formation_error = 0.0f;
      this->is_formation_valid = false;
    }
  }

  // field types and members
  using _drone_ids_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _drone_ids_type drone_ids;
  using _reference_positions_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _reference_positions_type reference_positions;
  using _reference_velocities_type =
    std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>>;
  _reference_velocities_type reference_velocities;
  using _formation_error_type =
    float;
  _formation_error_type formation_error;
  using _is_formation_valid_type =
    bool;
  _is_formation_valid_type is_formation_valid;

  // setters for named parameter idiom
  Type & set__drone_ids(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->drone_ids = _arg;
    return *this;
  }
  Type & set__reference_positions(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->reference_positions = _arg;
    return *this;
  }
  Type & set__reference_velocities(
    const std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>> & _arg)
  {
    this->reference_velocities = _arg;
    return *this;
  }
  Type & set__formation_error(
    const float & _arg)
  {
    this->formation_error = _arg;
    return *this;
  }
  Type & set__is_formation_valid(
    const bool & _arg)
  {
    this->is_formation_valid = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_swarm::msg::FormationReference_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_swarm::msg::FormationReference_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::FormationReference_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_swarm::msg::FormationReference_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_swarm__msg__FormationReference
    std::shared_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_swarm__msg__FormationReference
    std::shared_ptr<sentinel_swarm::msg::FormationReference_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FormationReference_ & other) const
  {
    if (this->drone_ids != other.drone_ids) {
      return false;
    }
    if (this->reference_positions != other.reference_positions) {
      return false;
    }
    if (this->reference_velocities != other.reference_velocities) {
      return false;
    }
    if (this->formation_error != other.formation_error) {
      return false;
    }
    if (this->is_formation_valid != other.is_formation_valid) {
      return false;
    }
    return true;
  }
  bool operator!=(const FormationReference_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FormationReference_

// alias to use template instance with default allocator
using FormationReference =
  sentinel_swarm::msg::FormationReference_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_swarm

#endif  // SENTINEL_SWARM__MSG__DETAIL__FORMATION_REFERENCE__STRUCT_HPP_
