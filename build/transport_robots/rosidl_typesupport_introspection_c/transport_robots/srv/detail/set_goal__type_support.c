// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "transport_robots/srv/detail/set_goal__rosidl_typesupport_introspection_c.h"
#include "transport_robots/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "transport_robots/srv/detail/set_goal__functions.h"
#include "transport_robots/srv/detail/set_goal__struct.h"


// Include directives for member types
// Member `robot_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transport_robots__srv__SetGoal_Request__init(message_memory);
}

void transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_fini_function(void * message_memory)
{
  transport_robots__srv__SetGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_member_array[4] = {
  {
    "robot_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Request, robot_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Request, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Request, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Request, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_members = {
  "transport_robots__srv",  // message namespace
  "SetGoal_Request",  // message name
  4,  // number of fields
  sizeof(transport_robots__srv__SetGoal_Request),
  transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_member_array,  // message members
  transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_type_support_handle = {
  0,
  &transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transport_robots
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Request)() {
  if (!transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_type_support_handle.typesupport_identifier) {
    transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transport_robots__srv__SetGoal_Request__rosidl_typesupport_introspection_c__SetGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transport_robots/srv/detail/set_goal__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transport_robots/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transport_robots/srv/detail/set_goal__functions.h"
// already included above
// #include "transport_robots/srv/detail/set_goal__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transport_robots__srv__SetGoal_Response__init(message_memory);
}

void transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_fini_function(void * message_memory)
{
  transport_robots__srv__SetGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transport_robots__srv__SetGoal_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_members = {
  "transport_robots__srv",  // message namespace
  "SetGoal_Response",  // message name
  2,  // number of fields
  sizeof(transport_robots__srv__SetGoal_Response),
  transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_member_array,  // message members
  transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_type_support_handle = {
  0,
  &transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transport_robots
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Response)() {
  if (!transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_type_support_handle.typesupport_identifier) {
    transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transport_robots__srv__SetGoal_Response__rosidl_typesupport_introspection_c__SetGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transport_robots/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "transport_robots/srv/detail/set_goal__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_members = {
  "transport_robots__srv",  // service namespace
  "SetGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_Request_message_type_support_handle,
  NULL  // response message
  // transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_type_support_handle = {
  0,
  &transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transport_robots
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal)() {
  if (!transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_type_support_handle.typesupport_identifier) {
    transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transport_robots, srv, SetGoal_Response)()->data;
  }

  return &transport_robots__srv__detail__set_goal__rosidl_typesupport_introspection_c__SetGoal_service_type_support_handle;
}
