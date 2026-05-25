// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_swarm:msg/DroneState.idl
// generated code does not contain a copyright notice
#include "sentinel_swarm/msg/detail/drone_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `flight_mode`
#include "rosidl_runtime_c/string_functions.h"

bool
sentinel_swarm__msg__DroneState__init(sentinel_swarm__msg__DroneState * msg)
{
  if (!msg) {
    return false;
  }
  // drone_id
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    sentinel_swarm__msg__DroneState__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__init(&msg->velocity)) {
    sentinel_swarm__msg__DroneState__fini(msg);
    return false;
  }
  // battery_voltage
  // battery_current
  // battery_percentage
  // is_armed
  // is_healthy
  // flight_mode
  if (!rosidl_runtime_c__String__init(&msg->flight_mode)) {
    sentinel_swarm__msg__DroneState__fini(msg);
    return false;
  }
  // gps_hdop
  // connected_satellites
  return true;
}

void
sentinel_swarm__msg__DroneState__fini(sentinel_swarm__msg__DroneState * msg)
{
  if (!msg) {
    return;
  }
  // drone_id
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // velocity
  geometry_msgs__msg__Vector3__fini(&msg->velocity);
  // battery_voltage
  // battery_current
  // battery_percentage
  // is_armed
  // is_healthy
  // flight_mode
  rosidl_runtime_c__String__fini(&msg->flight_mode);
  // gps_hdop
  // connected_satellites
}

bool
sentinel_swarm__msg__DroneState__are_equal(const sentinel_swarm__msg__DroneState * lhs, const sentinel_swarm__msg__DroneState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // drone_id
  if (lhs->drone_id != rhs->drone_id) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // battery_voltage
  if (lhs->battery_voltage != rhs->battery_voltage) {
    return false;
  }
  // battery_current
  if (lhs->battery_current != rhs->battery_current) {
    return false;
  }
  // battery_percentage
  if (lhs->battery_percentage != rhs->battery_percentage) {
    return false;
  }
  // is_armed
  if (lhs->is_armed != rhs->is_armed) {
    return false;
  }
  // is_healthy
  if (lhs->is_healthy != rhs->is_healthy) {
    return false;
  }
  // flight_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->flight_mode), &(rhs->flight_mode)))
  {
    return false;
  }
  // gps_hdop
  if (lhs->gps_hdop != rhs->gps_hdop) {
    return false;
  }
  // connected_satellites
  if (lhs->connected_satellites != rhs->connected_satellites) {
    return false;
  }
  return true;
}

bool
sentinel_swarm__msg__DroneState__copy(
  const sentinel_swarm__msg__DroneState * input,
  sentinel_swarm__msg__DroneState * output)
{
  if (!input || !output) {
    return false;
  }
  // drone_id
  output->drone_id = input->drone_id;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // battery_voltage
  output->battery_voltage = input->battery_voltage;
  // battery_current
  output->battery_current = input->battery_current;
  // battery_percentage
  output->battery_percentage = input->battery_percentage;
  // is_armed
  output->is_armed = input->is_armed;
  // is_healthy
  output->is_healthy = input->is_healthy;
  // flight_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->flight_mode), &(output->flight_mode)))
  {
    return false;
  }
  // gps_hdop
  output->gps_hdop = input->gps_hdop;
  // connected_satellites
  output->connected_satellites = input->connected_satellites;
  return true;
}

sentinel_swarm__msg__DroneState *
sentinel_swarm__msg__DroneState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__DroneState * msg = (sentinel_swarm__msg__DroneState *)allocator.allocate(sizeof(sentinel_swarm__msg__DroneState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_swarm__msg__DroneState));
  bool success = sentinel_swarm__msg__DroneState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_swarm__msg__DroneState__destroy(sentinel_swarm__msg__DroneState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_swarm__msg__DroneState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_swarm__msg__DroneState__Sequence__init(sentinel_swarm__msg__DroneState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__DroneState * data = NULL;

  if (size) {
    data = (sentinel_swarm__msg__DroneState *)allocator.zero_allocate(size, sizeof(sentinel_swarm__msg__DroneState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_swarm__msg__DroneState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_swarm__msg__DroneState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
sentinel_swarm__msg__DroneState__Sequence__fini(sentinel_swarm__msg__DroneState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      sentinel_swarm__msg__DroneState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

sentinel_swarm__msg__DroneState__Sequence *
sentinel_swarm__msg__DroneState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__DroneState__Sequence * array = (sentinel_swarm__msg__DroneState__Sequence *)allocator.allocate(sizeof(sentinel_swarm__msg__DroneState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_swarm__msg__DroneState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_swarm__msg__DroneState__Sequence__destroy(sentinel_swarm__msg__DroneState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_swarm__msg__DroneState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_swarm__msg__DroneState__Sequence__are_equal(const sentinel_swarm__msg__DroneState__Sequence * lhs, const sentinel_swarm__msg__DroneState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_swarm__msg__DroneState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_swarm__msg__DroneState__Sequence__copy(
  const sentinel_swarm__msg__DroneState__Sequence * input,
  sentinel_swarm__msg__DroneState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_swarm__msg__DroneState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_swarm__msg__DroneState * data =
      (sentinel_swarm__msg__DroneState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_swarm__msg__DroneState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_swarm__msg__DroneState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_swarm__msg__DroneState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
