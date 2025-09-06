// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from transport_robots:srv/SetGoal.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__TRAITS_HPP_
#define TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "transport_robots/srv/detail/set_goal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace transport_robots
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_name
  {
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace transport_robots

namespace rosidl_generator_traits
{

[[deprecated("use transport_robots::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transport_robots::srv::SetGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transport_robots::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transport_robots::srv::to_yaml() instead")]]
inline std::string to_yaml(const transport_robots::srv::SetGoal_Request & msg)
{
  return transport_robots::srv::to_yaml(msg);
}

template<>
inline const char * data_type<transport_robots::srv::SetGoal_Request>()
{
  return "transport_robots::srv::SetGoal_Request";
}

template<>
inline const char * name<transport_robots::srv::SetGoal_Request>()
{
  return "transport_robots/srv/SetGoal_Request";
}

template<>
struct has_fixed_size<transport_robots::srv::SetGoal_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transport_robots::srv::SetGoal_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transport_robots::srv::SetGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transport_robots
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace transport_robots

namespace rosidl_generator_traits
{

[[deprecated("use transport_robots::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transport_robots::srv::SetGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transport_robots::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transport_robots::srv::to_yaml() instead")]]
inline std::string to_yaml(const transport_robots::srv::SetGoal_Response & msg)
{
  return transport_robots::srv::to_yaml(msg);
}

template<>
inline const char * data_type<transport_robots::srv::SetGoal_Response>()
{
  return "transport_robots::srv::SetGoal_Response";
}

template<>
inline const char * name<transport_robots::srv::SetGoal_Response>()
{
  return "transport_robots/srv/SetGoal_Response";
}

template<>
struct has_fixed_size<transport_robots::srv::SetGoal_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transport_robots::srv::SetGoal_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transport_robots::srv::SetGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transport_robots::srv::SetGoal>()
{
  return "transport_robots::srv::SetGoal";
}

template<>
inline const char * name<transport_robots::srv::SetGoal>()
{
  return "transport_robots/srv/SetGoal";
}

template<>
struct has_fixed_size<transport_robots::srv::SetGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<transport_robots::srv::SetGoal_Request>::value &&
    has_fixed_size<transport_robots::srv::SetGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<transport_robots::srv::SetGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<transport_robots::srv::SetGoal_Request>::value &&
    has_bounded_size<transport_robots::srv::SetGoal_Response>::value
  >
{
};

template<>
struct is_service<transport_robots::srv::SetGoal>
  : std::true_type
{
};

template<>
struct is_service_request<transport_robots::srv::SetGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transport_robots::srv::SetGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__SET_GOAL__TRAITS_HPP_
