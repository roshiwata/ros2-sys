// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__FUNCTIONS_H_
#define TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "transport_robots/msg/rosidl_generator_c__visibility_control.h"

#include "transport_robots/srv/detail/set_goal__struct.h"

/// Initialize srv/SetGoal message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * transport_robots__srv__SetGoal_Request
 * )) before or use
 * transport_robots__srv__SetGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__init(transport_robots__srv__SetGoal_Request * msg);

/// Finalize srv/SetGoal message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Request__fini(transport_robots__srv__SetGoal_Request * msg);

/// Create srv/SetGoal message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * transport_robots__srv__SetGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
transport_robots__srv__SetGoal_Request *
transport_robots__srv__SetGoal_Request__create();

/// Destroy srv/SetGoal message.
/**
 * It calls
 * transport_robots__srv__SetGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Request__destroy(transport_robots__srv__SetGoal_Request * msg);

/// Check for srv/SetGoal message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__are_equal(const transport_robots__srv__SetGoal_Request * lhs, const transport_robots__srv__SetGoal_Request * rhs);

/// Copy a srv/SetGoal message.
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
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__copy(
  const transport_robots__srv__SetGoal_Request * input,
  transport_robots__srv__SetGoal_Request * output);

/// Initialize array of srv/SetGoal messages.
/**
 * It allocates the memory for the number of elements and calls
 * transport_robots__srv__SetGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__Sequence__init(transport_robots__srv__SetGoal_Request__Sequence * array, size_t size);

/// Finalize array of srv/SetGoal messages.
/**
 * It calls
 * transport_robots__srv__SetGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Request__Sequence__fini(transport_robots__srv__SetGoal_Request__Sequence * array);

/// Create array of srv/SetGoal messages.
/**
 * It allocates the memory for the array and calls
 * transport_robots__srv__SetGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
transport_robots__srv__SetGoal_Request__Sequence *
transport_robots__srv__SetGoal_Request__Sequence__create(size_t size);

/// Destroy array of srv/SetGoal messages.
/**
 * It calls
 * transport_robots__srv__SetGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Request__Sequence__destroy(transport_robots__srv__SetGoal_Request__Sequence * array);

/// Check for srv/SetGoal message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__Sequence__are_equal(const transport_robots__srv__SetGoal_Request__Sequence * lhs, const transport_robots__srv__SetGoal_Request__Sequence * rhs);

/// Copy an array of srv/SetGoal messages.
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
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Request__Sequence__copy(
  const transport_robots__srv__SetGoal_Request__Sequence * input,
  transport_robots__srv__SetGoal_Request__Sequence * output);

/// Initialize srv/SetGoal message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * transport_robots__srv__SetGoal_Response
 * )) before or use
 * transport_robots__srv__SetGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__init(transport_robots__srv__SetGoal_Response * msg);

/// Finalize srv/SetGoal message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Response__fini(transport_robots__srv__SetGoal_Response * msg);

/// Create srv/SetGoal message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * transport_robots__srv__SetGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
transport_robots__srv__SetGoal_Response *
transport_robots__srv__SetGoal_Response__create();

/// Destroy srv/SetGoal message.
/**
 * It calls
 * transport_robots__srv__SetGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Response__destroy(transport_robots__srv__SetGoal_Response * msg);

/// Check for srv/SetGoal message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__are_equal(const transport_robots__srv__SetGoal_Response * lhs, const transport_robots__srv__SetGoal_Response * rhs);

/// Copy a srv/SetGoal message.
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
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__copy(
  const transport_robots__srv__SetGoal_Response * input,
  transport_robots__srv__SetGoal_Response * output);

/// Initialize array of srv/SetGoal messages.
/**
 * It allocates the memory for the number of elements and calls
 * transport_robots__srv__SetGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__Sequence__init(transport_robots__srv__SetGoal_Response__Sequence * array, size_t size);

/// Finalize array of srv/SetGoal messages.
/**
 * It calls
 * transport_robots__srv__SetGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Response__Sequence__fini(transport_robots__srv__SetGoal_Response__Sequence * array);

/// Create array of srv/SetGoal messages.
/**
 * It allocates the memory for the array and calls
 * transport_robots__srv__SetGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
transport_robots__srv__SetGoal_Response__Sequence *
transport_robots__srv__SetGoal_Response__Sequence__create(size_t size);

/// Destroy array of srv/SetGoal messages.
/**
 * It calls
 * transport_robots__srv__SetGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
void
transport_robots__srv__SetGoal_Response__Sequence__destroy(transport_robots__srv__SetGoal_Response__Sequence * array);

/// Check for srv/SetGoal message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__Sequence__are_equal(const transport_robots__srv__SetGoal_Response__Sequence * lhs, const transport_robots__srv__SetGoal_Response__Sequence * rhs);

/// Copy an array of srv/SetGoal messages.
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
ROSIDL_GENERATOR_C_PUBLIC_transport_robots
bool
transport_robots__srv__SetGoal_Response__Sequence__copy(
  const transport_robots__srv__SetGoal_Response__Sequence * input,
  transport_robots__srv__SetGoal_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__FUNCTIONS_H_
