// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__STRUCT_HPP_
#define TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__transport_robots__srv__SetGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__transport_robots__srv__SetGoal_Request __declspec(deprecated)
#endif

namespace transport_robots
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetGoal_Request_
{
  using Type = SetGoal_Request_<ContainerAllocator>;

  explicit SetGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->x = 0.0;
      this->y = 0.0;
      this->yaw = 0.0;
    }
  }

  explicit SetGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->x = 0.0;
      this->y = 0.0;
      this->yaw = 0.0;
    }
  }

  // field types and members
  using _robot_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_name_type robot_name;
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _yaw_type =
    double;
  _yaw_type yaw;

  // setters for named parameter idiom
  Type & set__robot_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_name = _arg;
    return *this;
  }
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transport_robots::srv::SetGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const transport_robots::srv::SetGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transport_robots::srv::SetGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transport_robots::srv::SetGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transport_robots__srv__SetGoal_Request
    std::shared_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transport_robots__srv__SetGoal_Request
    std::shared_ptr<transport_robots::srv::SetGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetGoal_Request_ & other) const
  {
    if (this->robot_name != other.robot_name) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetGoal_Request_

// alias to use template instance with default allocator
using SetGoal_Request =
  transport_robots::srv::SetGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace transport_robots


#ifndef _WIN32
# define DEPRECATED__transport_robots__srv__SetGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__transport_robots__srv__SetGoal_Response __declspec(deprecated)
#endif

namespace transport_robots
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetGoal_Response_
{
  using Type = SetGoal_Response_<ContainerAllocator>;

  explicit SetGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transport_robots::srv::SetGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const transport_robots::srv::SetGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transport_robots::srv::SetGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transport_robots::srv::SetGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transport_robots__srv__SetGoal_Response
    std::shared_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transport_robots__srv__SetGoal_Response
    std::shared_ptr<transport_robots::srv::SetGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetGoal_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetGoal_Response_

// alias to use template instance with default allocator
using SetGoal_Response =
  transport_robots::srv::SetGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace transport_robots

namespace transport_robots
{

namespace srv
{

struct SetGoal
{
  using Request = transport_robots::srv::SetGoal_Request;
  using Response = transport_robots::srv::SetGoal_Response;
};

}  // namespace srv

}  // namespace transport_robots

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__STRUCT_HPP_
