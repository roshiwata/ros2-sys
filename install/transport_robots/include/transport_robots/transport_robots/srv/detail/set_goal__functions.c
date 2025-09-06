// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice
#include "transport_robots/srv/detail/set_goal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `robot_name`
#include "rosidl_runtime_c/string_functions.h"

bool
transport_robots__srv__SetGoal_Request__init(transport_robots__srv__SetGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__init(&msg->robot_name)) {
    transport_robots__srv__SetGoal_Request__fini(msg);
    return false;
  }
  // x
  // y
  // yaw
  return true;
}

void
transport_robots__srv__SetGoal_Request__fini(transport_robots__srv__SetGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // robot_name
  rosidl_runtime_c__String__fini(&msg->robot_name);
  // x
  // y
  // yaw
}

bool
transport_robots__srv__SetGoal_Request__are_equal(const transport_robots__srv__SetGoal_Request * lhs, const transport_robots__srv__SetGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_name), &(rhs->robot_name)))
  {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  return true;
}

bool
transport_robots__srv__SetGoal_Request__copy(
  const transport_robots__srv__SetGoal_Request * input,
  transport_robots__srv__SetGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_name), &(output->robot_name)))
  {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // yaw
  output->yaw = input->yaw;
  return true;
}

transport_robots__srv__SetGoal_Request *
transport_robots__srv__SetGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Request * msg = (transport_robots__srv__SetGoal_Request *)allocator.allocate(sizeof(transport_robots__srv__SetGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transport_robots__srv__SetGoal_Request));
  bool success = transport_robots__srv__SetGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transport_robots__srv__SetGoal_Request__destroy(transport_robots__srv__SetGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transport_robots__srv__SetGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transport_robots__srv__SetGoal_Request__Sequence__init(transport_robots__srv__SetGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Request * data = NULL;

  if (size) {
    data = (transport_robots__srv__SetGoal_Request *)allocator.zero_allocate(size, sizeof(transport_robots__srv__SetGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transport_robots__srv__SetGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transport_robots__srv__SetGoal_Request__fini(&data[i - 1]);
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
transport_robots__srv__SetGoal_Request__Sequence__fini(transport_robots__srv__SetGoal_Request__Sequence * array)
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
      transport_robots__srv__SetGoal_Request__fini(&array->data[i]);
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

transport_robots__srv__SetGoal_Request__Sequence *
transport_robots__srv__SetGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Request__Sequence * array = (transport_robots__srv__SetGoal_Request__Sequence *)allocator.allocate(sizeof(transport_robots__srv__SetGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transport_robots__srv__SetGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transport_robots__srv__SetGoal_Request__Sequence__destroy(transport_robots__srv__SetGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transport_robots__srv__SetGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transport_robots__srv__SetGoal_Request__Sequence__are_equal(const transport_robots__srv__SetGoal_Request__Sequence * lhs, const transport_robots__srv__SetGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transport_robots__srv__SetGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transport_robots__srv__SetGoal_Request__Sequence__copy(
  const transport_robots__srv__SetGoal_Request__Sequence * input,
  transport_robots__srv__SetGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transport_robots__srv__SetGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transport_robots__srv__SetGoal_Request * data =
      (transport_robots__srv__SetGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transport_robots__srv__SetGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transport_robots__srv__SetGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transport_robots__srv__SetGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
transport_robots__srv__SetGoal_Response__init(transport_robots__srv__SetGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    transport_robots__srv__SetGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
transport_robots__srv__SetGoal_Response__fini(transport_robots__srv__SetGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
transport_robots__srv__SetGoal_Response__are_equal(const transport_robots__srv__SetGoal_Response * lhs, const transport_robots__srv__SetGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
transport_robots__srv__SetGoal_Response__copy(
  const transport_robots__srv__SetGoal_Response * input,
  transport_robots__srv__SetGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

transport_robots__srv__SetGoal_Response *
transport_robots__srv__SetGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Response * msg = (transport_robots__srv__SetGoal_Response *)allocator.allocate(sizeof(transport_robots__srv__SetGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transport_robots__srv__SetGoal_Response));
  bool success = transport_robots__srv__SetGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transport_robots__srv__SetGoal_Response__destroy(transport_robots__srv__SetGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transport_robots__srv__SetGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transport_robots__srv__SetGoal_Response__Sequence__init(transport_robots__srv__SetGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Response * data = NULL;

  if (size) {
    data = (transport_robots__srv__SetGoal_Response *)allocator.zero_allocate(size, sizeof(transport_robots__srv__SetGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transport_robots__srv__SetGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transport_robots__srv__SetGoal_Response__fini(&data[i - 1]);
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
transport_robots__srv__SetGoal_Response__Sequence__fini(transport_robots__srv__SetGoal_Response__Sequence * array)
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
      transport_robots__srv__SetGoal_Response__fini(&array->data[i]);
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

transport_robots__srv__SetGoal_Response__Sequence *
transport_robots__srv__SetGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transport_robots__srv__SetGoal_Response__Sequence * array = (transport_robots__srv__SetGoal_Response__Sequence *)allocator.allocate(sizeof(transport_robots__srv__SetGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transport_robots__srv__SetGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transport_robots__srv__SetGoal_Response__Sequence__destroy(transport_robots__srv__SetGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transport_robots__srv__SetGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transport_robots__srv__SetGoal_Response__Sequence__are_equal(const transport_robots__srv__SetGoal_Response__Sequence * lhs, const transport_robots__srv__SetGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transport_robots__srv__SetGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transport_robots__srv__SetGoal_Response__Sequence__copy(
  const transport_robots__srv__SetGoal_Response__Sequence * input,
  transport_robots__srv__SetGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transport_robots__srv__SetGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transport_robots__srv__SetGoal_Response * data =
      (transport_robots__srv__SetGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transport_robots__srv__SetGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transport_robots__srv__SetGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transport_robots__srv__SetGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
