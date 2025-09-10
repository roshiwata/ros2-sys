// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from transport_robots:srv/GetPosition.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__STRUCT_H_
#define TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetPosition in the package transport_robots.
typedef struct transport_robots__srv__GetPosition_Request
{
  /// ロボット名 (robot_1, robot_2, etc.)
  rosidl_runtime_c__String robot_name;
} transport_robots__srv__GetPosition_Request;

// Struct for a sequence of transport_robots__srv__GetPosition_Request.
typedef struct transport_robots__srv__GetPosition_Request__Sequence
{
  transport_robots__srv__GetPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transport_robots__srv__GetPosition_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetPosition in the package transport_robots.
typedef struct transport_robots__srv__GetPosition_Response
{
  /// 成功/失敗
  bool success;
  /// 結果メッセージ
  rosidl_runtime_c__String message;
  /// 現在X座標 (m)
  double x;
  /// 現在Y座標 (m)
  double y;
  /// 現在Z座標 (m)
  double z;
  /// ロール角 (rad)
  double roll;
  /// ピッチ角 (rad)
  double pitch;
  /// ヨー角 (rad)
  double yaw;
  /// 線形速度X (m/s)
  double linear_x;
  /// 線形速度Y (m/s)
  double linear_y;
  /// 角速度Z (rad/s)
  double angular_z;
} transport_robots__srv__GetPosition_Response;

// Struct for a sequence of transport_robots__srv__GetPosition_Response.
typedef struct transport_robots__srv__GetPosition_Response__Sequence
{
  transport_robots__srv__GetPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transport_robots__srv__GetPosition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__STRUCT_H_
