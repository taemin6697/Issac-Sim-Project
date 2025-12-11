// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from duckie_interfaces:srv/SetColor.idl
// generated code does not contain a copyright notice

#ifndef DUCKIE_INTERFACES__SRV__DETAIL__SET_COLOR__TRAITS_HPP_
#define DUCKIE_INTERFACES__SRV__DETAIL__SET_COLOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "duckie_interfaces/srv/detail/set_color__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace duckie_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetColor_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetColor_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetColor_Request & msg, bool use_flow_style = false)
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

}  // namespace duckie_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use duckie_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const duckie_interfaces::srv::SetColor_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  duckie_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use duckie_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const duckie_interfaces::srv::SetColor_Request & msg)
{
  return duckie_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<duckie_interfaces::srv::SetColor_Request>()
{
  return "duckie_interfaces::srv::SetColor_Request";
}

template<>
inline const char * name<duckie_interfaces::srv::SetColor_Request>()
{
  return "duckie_interfaces/srv/SetColor_Request";
}

template<>
struct has_fixed_size<duckie_interfaces::srv::SetColor_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<duckie_interfaces::srv::SetColor_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<duckie_interfaces::srv::SetColor_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace duckie_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetColor_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetColor_Response & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetColor_Response & msg, bool use_flow_style = false)
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

}  // namespace duckie_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use duckie_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const duckie_interfaces::srv::SetColor_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  duckie_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use duckie_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const duckie_interfaces::srv::SetColor_Response & msg)
{
  return duckie_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<duckie_interfaces::srv::SetColor_Response>()
{
  return "duckie_interfaces::srv::SetColor_Response";
}

template<>
inline const char * name<duckie_interfaces::srv::SetColor_Response>()
{
  return "duckie_interfaces/srv/SetColor_Response";
}

template<>
struct has_fixed_size<duckie_interfaces::srv::SetColor_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<duckie_interfaces::srv::SetColor_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<duckie_interfaces::srv::SetColor_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<duckie_interfaces::srv::SetColor>()
{
  return "duckie_interfaces::srv::SetColor";
}

template<>
inline const char * name<duckie_interfaces::srv::SetColor>()
{
  return "duckie_interfaces/srv/SetColor";
}

template<>
struct has_fixed_size<duckie_interfaces::srv::SetColor>
  : std::integral_constant<
    bool,
    has_fixed_size<duckie_interfaces::srv::SetColor_Request>::value &&
    has_fixed_size<duckie_interfaces::srv::SetColor_Response>::value
  >
{
};

template<>
struct has_bounded_size<duckie_interfaces::srv::SetColor>
  : std::integral_constant<
    bool,
    has_bounded_size<duckie_interfaces::srv::SetColor_Request>::value &&
    has_bounded_size<duckie_interfaces::srv::SetColor_Response>::value
  >
{
};

template<>
struct is_service<duckie_interfaces::srv::SetColor>
  : std::true_type
{
};

template<>
struct is_service_request<duckie_interfaces::srv::SetColor_Request>
  : std::true_type
{
};

template<>
struct is_service_response<duckie_interfaces::srv::SetColor_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DUCKIE_INTERFACES__SRV__DETAIL__SET_COLOR__TRAITS_HPP_
