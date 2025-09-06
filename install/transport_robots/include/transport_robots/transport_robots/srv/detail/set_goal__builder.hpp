// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__BUILDER_HPP_
#define TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transport_robots/srv/detail/set_goal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transport_robots
{

namespace srv
{

namespace builder
{

class Init_SetGoal_Request_yaw
{
public:
  explicit Init_SetGoal_Request_yaw(::transport_robots::srv::SetGoal_Request & msg)
  : msg_(msg)
  {}
  ::transport_robots::srv::SetGoal_Request yaw(::transport_robots::srv::SetGoal_Request::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Request msg_;
};

class Init_SetGoal_Request_y
{
public:
  explicit Init_SetGoal_Request_y(::transport_robots::srv::SetGoal_Request & msg)
  : msg_(msg)
  {}
  Init_SetGoal_Request_yaw y(::transport_robots::srv::SetGoal_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_SetGoal_Request_yaw(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Request msg_;
};

class Init_SetGoal_Request_x
{
public:
  explicit Init_SetGoal_Request_x(::transport_robots::srv::SetGoal_Request & msg)
  : msg_(msg)
  {}
  Init_SetGoal_Request_y x(::transport_robots::srv::SetGoal_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_SetGoal_Request_y(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Request msg_;
};

class Init_SetGoal_Request_robot_name
{
public:
  Init_SetGoal_Request_robot_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetGoal_Request_x robot_name(::transport_robots::srv::SetGoal_Request::_robot_name_type arg)
  {
    msg_.robot_name = std::move(arg);
    return Init_SetGoal_Request_x(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::transport_robots::srv::SetGoal_Request>()
{
  return transport_robots::srv::builder::Init_SetGoal_Request_robot_name();
}

}  // namespace transport_robots


namespace transport_robots
{

namespace srv
{

namespace builder
{

class Init_SetGoal_Response_message
{
public:
  explicit Init_SetGoal_Response_message(::transport_robots::srv::SetGoal_Response & msg)
  : msg_(msg)
  {}
  ::transport_robots::srv::SetGoal_Response message(::transport_robots::srv::SetGoal_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Response msg_;
};

class Init_SetGoal_Response_success
{
public:
  Init_SetGoal_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetGoal_Response_message success(::transport_robots::srv::SetGoal_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetGoal_Response_message(msg_);
  }

private:
  ::transport_robots::srv::SetGoal_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::transport_robots::srv::SetGoal_Response>()
{
  return transport_robots::srv::builder::Init_SetGoal_Response_success();
}

}  // namespace transport_robots

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__BUILDER_HPP_
