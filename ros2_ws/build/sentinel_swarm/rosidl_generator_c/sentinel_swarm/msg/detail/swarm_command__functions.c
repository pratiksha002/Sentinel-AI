// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice
#include "sentinel_swarm/msg/detail/swarm_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `command_type`
// Member `formation_type`
#include "rosidl_runtime_c/string_functions.h"
// Member `target_point`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
sentinel_swarm__msg__SwarmCommand__init(sentinel_swarm__msg__SwarmCommand * msg)
{
  if (!msg) {
    return false;
  }
  // command_id
  // command_type
  if (!rosidl_runtime_c__String__init(&msg->command_type)) {
    sentinel_swarm__msg__SwarmCommand__fini(msg);
    return false;
  }
  // target_point
  if (!geometry_msgs__msg__Point__init(&msg->target_point)) {
    sentinel_swarm__msg__SwarmCommand__fini(msg);
    return false;
  }
  // formation_type
  if (!rosidl_runtime_c__String__init(&msg->formation_type)) {
    sentinel_swarm__msg__SwarmCommand__fini(msg);
    return false;
  }
  // formation_scale
  // mission_timeout
  return true;
}

void
sentinel_swarm__msg__SwarmCommand__fini(sentinel_swarm__msg__SwarmCommand * msg)
{
  if (!msg) {
    return;
  }
  // command_id
  // command_type
  rosidl_runtime_c__String__fini(&msg->command_type);
  // target_point
  geometry_msgs__msg__Point__fini(&msg->target_point);
  // formation_type
  rosidl_runtime_c__String__fini(&msg->formation_type);
  // formation_scale
  // mission_timeout
}

bool
sentinel_swarm__msg__SwarmCommand__are_equal(const sentinel_swarm__msg__SwarmCommand * lhs, const sentinel_swarm__msg__SwarmCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // command_id
  if (lhs->command_id != rhs->command_id) {
    return false;
  }
  // command_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->command_type), &(rhs->command_type)))
  {
    return false;
  }
  // target_point
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->target_point), &(rhs->target_point)))
  {
    return false;
  }
  // formation_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->formation_type), &(rhs->formation_type)))
  {
    return false;
  }
  // formation_scale
  if (lhs->formation_scale != rhs->formation_scale) {
    return false;
  }
  // mission_timeout
  if (lhs->mission_timeout != rhs->mission_timeout) {
    return false;
  }
  return true;
}

bool
sentinel_swarm__msg__SwarmCommand__copy(
  const sentinel_swarm__msg__SwarmCommand * input,
  sentinel_swarm__msg__SwarmCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // command_id
  output->command_id = input->command_id;
  // command_type
  if (!rosidl_runtime_c__String__copy(
      &(input->command_type), &(output->command_type)))
  {
    return false;
  }
  // target_point
  if (!geometry_msgs__msg__Point__copy(
      &(input->target_point), &(output->target_point)))
  {
    return false;
  }
  // formation_type
  if (!rosidl_runtime_c__String__copy(
      &(input->formation_type), &(output->formation_type)))
  {
    return false;
  }
  // formation_scale
  output->formation_scale = input->formation_scale;
  // mission_timeout
  output->mission_timeout = input->mission_timeout;
  return true;
}

sentinel_swarm__msg__SwarmCommand *
sentinel_swarm__msg__SwarmCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__SwarmCommand * msg = (sentinel_swarm__msg__SwarmCommand *)allocator.allocate(sizeof(sentinel_swarm__msg__SwarmCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_swarm__msg__SwarmCommand));
  bool success = sentinel_swarm__msg__SwarmCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_swarm__msg__SwarmCommand__destroy(sentinel_swarm__msg__SwarmCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_swarm__msg__SwarmCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_swarm__msg__SwarmCommand__Sequence__init(sentinel_swarm__msg__SwarmCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__SwarmCommand * data = NULL;

  if (size) {
    data = (sentinel_swarm__msg__SwarmCommand *)allocator.zero_allocate(size, sizeof(sentinel_swarm__msg__SwarmCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_swarm__msg__SwarmCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_swarm__msg__SwarmCommand__fini(&data[i - 1]);
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
sentinel_swarm__msg__SwarmCommand__Sequence__fini(sentinel_swarm__msg__SwarmCommand__Sequence * array)
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
      sentinel_swarm__msg__SwarmCommand__fini(&array->data[i]);
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

sentinel_swarm__msg__SwarmCommand__Sequence *
sentinel_swarm__msg__SwarmCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_swarm__msg__SwarmCommand__Sequence * array = (sentinel_swarm__msg__SwarmCommand__Sequence *)allocator.allocate(sizeof(sentinel_swarm__msg__SwarmCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_swarm__msg__SwarmCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_swarm__msg__SwarmCommand__Sequence__destroy(sentinel_swarm__msg__SwarmCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_swarm__msg__SwarmCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_swarm__msg__SwarmCommand__Sequence__are_equal(const sentinel_swarm__msg__SwarmCommand__Sequence * lhs, const sentinel_swarm__msg__SwarmCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_swarm__msg__SwarmCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_swarm__msg__SwarmCommand__Sequence__copy(
  const sentinel_swarm__msg__SwarmCommand__Sequence * input,
  sentinel_swarm__msg__SwarmCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_swarm__msg__SwarmCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_swarm__msg__SwarmCommand * data =
      (sentinel_swarm__msg__SwarmCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_swarm__msg__SwarmCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_swarm__msg__SwarmCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_swarm__msg__SwarmCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
