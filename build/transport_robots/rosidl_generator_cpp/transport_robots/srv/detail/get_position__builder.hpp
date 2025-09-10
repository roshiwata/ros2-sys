// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transport_robots:srv/GetPosition.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__BUILDER_HPP_
#define TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transport_robots/srv/detail/get_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transport_robots
{

namespace srv
{

namespace builder
{

class Init_GetPosition_Request_robot_name
{
public:
  Init_GetPosition_Request_robot_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::transport_robots::srv::GetPosition_Request robot_name(::transport_robots::srv::GetPosition_Request::_robot_name_type arg)
  {
    msg_.robot_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::transport_robots::srv::GetPosition_Request>()
{
  return transport_robots::srv::builder::Init_GetPosition_Request_robot_name();
}

}  // namespace transport_robots


namespace transport_robots
{

namespace srv
{

namespace builder
{

class Init_GetPosition_Response_angular_z
{
public:
  explicit Init_GetPosition_Response_angular_z(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  ::transport_robots::srv::GetPosition_Response angular_z(::transport_robots::srv::GetPosition_Response::_angular_z_type arg)
  {
    msg_.angular_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_linear_y
{
public:
  explicit Init_GetPosition_Response_linear_y(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_angular_z linear_y(::transport_robots::srv::GetPosition_Response::_linear_y_type arg)
  {
    msg_.linear_y = std::move(arg);
    return Init_GetPosition_Response_angular_z(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_linear_x
{
public:
  explicit Init_GetPosition_Response_linear_x(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_linear_y linear_x(::transport_robots::srv::GetPosition_Response::_linear_x_type arg)
  {
    msg_.linear_x = std::move(arg);
    return Init_GetPosition_Response_linear_y(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_yaw
{
public:
  explicit Init_GetPosition_Response_yaw(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_linear_x yaw(::transport_robots::srv::GetPosition_Response::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_GetPosition_Response_linear_x(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_pitch
{
public:
  explicit Init_GetPosition_Response_pitch(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_yaw pitch(::transport_robots::srv::GetPosition_Response::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_GetPosition_Response_yaw(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_roll
{
public:
  explicit Init_GetPosition_Response_roll(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_pitch roll(::transport_robots::srv::GetPosition_Response::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_GetPosition_Response_pitch(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_z
{
public:
  explicit Init_GetPosition_Response_z(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_roll z(::transport_robots::srv::GetPosition_Response::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_GetPosition_Response_roll(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_y
{
public:
  explicit Init_GetPosition_Response_y(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_z y(::transport_robots::srv::GetPosition_Response::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_GetPosition_Response_z(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_x
{
public:
  explicit Init_GetPosition_Response_x(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_y x(::transport_robots::srv::GetPosition_Response::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_GetPosition_Response_y(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_message
{
public:
  explicit Init_GetPosition_Response_message(::transport_robots::srv::GetPosition_Response & msg)
  : msg_(msg)
  {}
  Init_GetPosition_Response_x message(::transport_robots::srv::GetPosition_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_GetPosition_Response_x(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

class Init_GetPosition_Response_success
{
public:
  Init_GetPosition_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetPosition_Response_message success(::transport_robots::srv::GetPosition_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetPosition_Response_message(msg_);
  }

private:
  ::transport_robots::srv::GetPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::transport_robots::srv::GetPosition_Response>()
{
  return transport_robots::srv::builder::Init_GetPosition_Response_success();
}

}  // namespace transport_robots

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__BUILDER_HPP_
