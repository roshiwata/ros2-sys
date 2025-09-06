// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from transport_robots:srv/GetPosition.idl
// generated code does not contain a copyright notice

#ifndef TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__TRAITS_HPP_
#define TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "transport_robots/srv/detail/get_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace transport_robots
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetPosition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_name
  {
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetPosition_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetPosition_Request & msg, bool use_flow_style = false)
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
  const transport_robots::srv::GetPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transport_robots::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transport_robots::srv::to_yaml() instead")]]
inline std::string to_yaml(const transport_robots::srv::GetPosition_Request & msg)
{
  return transport_robots::srv::to_yaml(msg);
}

template<>
inline const char * data_type<transport_robots::srv::GetPosition_Request>()
{
  return "transport_robots::srv::GetPosition_Request";
}

template<>
inline const char * name<transport_robots::srv::GetPosition_Request>()
{
  return "transport_robots/srv/GetPosition_Request";
}

template<>
struct has_fixed_size<transport_robots::srv::GetPosition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transport_robots::srv::GetPosition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transport_robots::srv::GetPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transport_robots
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetPosition_Response & msg,
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

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: linear_x
  {
    out << "linear_x: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_x, out);
    out << ", ";
  }

  // member: linear_y
  {
    out << "linear_y: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_y, out);
    out << ", ";
  }

  // member: angular_z
  {
    out << "angular_z: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetPosition_Response & msg,
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

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
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

  // member: linear_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linear_x: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_x, out);
    out << "\n";
  }

  // member: linear_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linear_y: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_y, out);
    out << "\n";
  }

  // member: angular_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_z: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetPosition_Response & msg, bool use_flow_style = false)
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
  const transport_robots::srv::GetPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transport_robots::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transport_robots::srv::to_yaml() instead")]]
inline std::string to_yaml(const transport_robots::srv::GetPosition_Response & msg)
{
  return transport_robots::srv::to_yaml(msg);
}

template<>
inline const char * data_type<transport_robots::srv::GetPosition_Response>()
{
  return "transport_robots::srv::GetPosition_Response";
}

template<>
inline const char * name<transport_robots::srv::GetPosition_Response>()
{
  return "transport_robots/srv/GetPosition_Response";
}

template<>
struct has_fixed_size<transport_robots::srv::GetPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transport_robots::srv::GetPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transport_robots::srv::GetPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transport_robots::srv::GetPosition>()
{
  return "transport_robots::srv::GetPosition";
}

template<>
inline const char * name<transport_robots::srv::GetPosition>()
{
  return "transport_robots/srv/GetPosition";
}

template<>
struct has_fixed_size<transport_robots::srv::GetPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<transport_robots::srv::GetPosition_Request>::value &&
    has_fixed_size<transport_robots::srv::GetPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<transport_robots::srv::GetPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<transport_robots::srv::GetPosition_Request>::value &&
    has_bounded_size<transport_robots::srv::GetPosition_Response>::value
  >
{
};

template<>
struct is_service<transport_robots::srv::GetPosition>
  : std::true_type
{
};

template<>
struct is_service_request<transport_robots::srv::GetPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transport_robots::srv::GetPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TRANSPORT_ROBOTS__SRV__DETAIL__GET_POSITION__TRAITS_HPP_
