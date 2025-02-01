// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "status_interfaces/msg/detail/system_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace status_interfaces
{

namespace msg
{

namespace builder
{

class Init_SystemStatus_net_recv
{
public:
  explicit Init_SystemStatus_net_recv(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  ::status_interfaces::msg::SystemStatus net_recv(::status_interfaces::msg::SystemStatus::_net_recv_type arg)
  {
    msg_.net_recv = std::move(arg);
    return std::move(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_net_sent
{
public:
  explicit Init_SystemStatus_net_sent(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_net_recv net_sent(::status_interfaces::msg::SystemStatus::_net_sent_type arg)
  {
    msg_.net_sent = std::move(arg);
    return Init_SystemStatus_net_recv(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_available
{
public:
  explicit Init_SystemStatus_memory_available(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_net_sent memory_available(::status_interfaces::msg::SystemStatus::_memory_available_type arg)
  {
    msg_.memory_available = std::move(arg);
    return Init_SystemStatus_net_sent(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_total
{
public:
  explicit Init_SystemStatus_memory_total(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_available memory_total(::status_interfaces::msg::SystemStatus::_memory_total_type arg)
  {
    msg_.memory_total = std::move(arg);
    return Init_SystemStatus_memory_available(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_usage
{
public:
  explicit Init_SystemStatus_memory_usage(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_total memory_usage(::status_interfaces::msg::SystemStatus::_memory_usage_type arg)
  {
    msg_.memory_usage = std::move(arg);
    return Init_SystemStatus_memory_total(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_cpu_usage
{
public:
  explicit Init_SystemStatus_cpu_usage(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_usage cpu_usage(::status_interfaces::msg::SystemStatus::_cpu_usage_type arg)
  {
    msg_.cpu_usage = std::move(arg);
    return Init_SystemStatus_memory_usage(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_hostname
{
public:
  explicit Init_SystemStatus_hostname(::status_interfaces::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_cpu_usage hostname(::status_interfaces::msg::SystemStatus::_hostname_type arg)
  {
    msg_.hostname = std::move(arg);
    return Init_SystemStatus_cpu_usage(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

class Init_SystemStatus_time
{
public:
  Init_SystemStatus_time()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SystemStatus_hostname time(::status_interfaces::msg::SystemStatus::_time_type arg)
  {
    msg_.time = std::move(arg);
    return Init_SystemStatus_hostname(msg_);
  }

private:
  ::status_interfaces::msg::SystemStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::status_interfaces::msg::SystemStatus>()
{
  return status_interfaces::msg::builder::Init_SystemStatus_time();
}

}  // namespace status_interfaces

#endif  // STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_
