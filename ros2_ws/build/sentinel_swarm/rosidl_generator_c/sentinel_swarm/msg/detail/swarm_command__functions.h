// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sentinel_swarm:msg/SwarmCommand.idl
// generated code does not contain a copyright notice

#ifndef SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__FUNCTIONS_H_
#define SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sentinel_swarm/msg/rosidl_generator_c__visibility_control.h"

#include "sentinel_swarm/msg/detail/swarm_command__struct.h"

/// Initialize msg/SwarmCommand message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sentinel_swarm__msg__SwarmCommand
 * )) before or use
 * sentinel_swarm__msg__SwarmCommand__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__init(sentinel_swarm__msg__SwarmCommand * msg);

/// Finalize msg/SwarmCommand message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
void
sentinel_swarm__msg__SwarmCommand__fini(sentinel_swarm__msg__SwarmCommand * msg);

/// Create msg/SwarmCommand message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sentinel_swarm__msg__SwarmCommand__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
sentinel_swarm__msg__SwarmCommand *
sentinel_swarm__msg__SwarmCommand__create();

/// Destroy msg/SwarmCommand message.
/**
 * It calls
 * sentinel_swarm__msg__SwarmCommand__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
void
sentinel_swarm__msg__SwarmCommand__destroy(sentinel_swarm__msg__SwarmCommand * msg);

/// Check for msg/SwarmCommand message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__are_equal(const sentinel_swarm__msg__SwarmCommand * lhs, const sentinel_swarm__msg__SwarmCommand * rhs);

/// Copy a msg/SwarmCommand message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__copy(
  const sentinel_swarm__msg__SwarmCommand * input,
  sentinel_swarm__msg__SwarmCommand * output);

/// Initialize array of msg/SwarmCommand messages.
/**
 * It allocates the memory for the number of elements and calls
 * sentinel_swarm__msg__SwarmCommand__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__Sequence__init(sentinel_swarm__msg__SwarmCommand__Sequence * array, size_t size);

/// Finalize array of msg/SwarmCommand messages.
/**
 * It calls
 * sentinel_swarm__msg__SwarmCommand__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
void
sentinel_swarm__msg__SwarmCommand__Sequence__fini(sentinel_swarm__msg__SwarmCommand__Sequence * array);

/// Create array of msg/SwarmCommand messages.
/**
 * It allocates the memory for the array and calls
 * sentinel_swarm__msg__SwarmCommand__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
sentinel_swarm__msg__SwarmCommand__Sequence *
sentinel_swarm__msg__SwarmCommand__Sequence__create(size_t size);

/// Destroy array of msg/SwarmCommand messages.
/**
 * It calls
 * sentinel_swarm__msg__SwarmCommand__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
void
sentinel_swarm__msg__SwarmCommand__Sequence__destroy(sentinel_swarm__msg__SwarmCommand__Sequence * array);

/// Check for msg/SwarmCommand message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__Sequence__are_equal(const sentinel_swarm__msg__SwarmCommand__Sequence * lhs, const sentinel_swarm__msg__SwarmCommand__Sequence * rhs);

/// Copy an array of msg/SwarmCommand messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sentinel_swarm
bool
sentinel_swarm__msg__SwarmCommand__Sequence__copy(
  const sentinel_swarm__msg__SwarmCommand__Sequence * input,
  sentinel_swarm__msg__SwarmCommand__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_SWARM__MSG__DETAIL__SWARM_COMMAND__FUNCTIONS_H_
