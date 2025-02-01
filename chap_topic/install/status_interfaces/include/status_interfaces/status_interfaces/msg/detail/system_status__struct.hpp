// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'time'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__status_interfaces__msg__SystemStatus __attribute__((deprecated))
#else
# define DEPRECATED__status_interfaces__msg__SystemStatus __declspec(deprecated)
#endif

namespace status_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SystemStatus_
{
  using Type = SystemStatus_<ContainerAllocator>;

  explicit SystemStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hostname = "";
      this->cpu_usage = 0.0f;
      this->memory_usage = 0.0f;
      this->memory_total = 0.0f;
      this->memory_available = 0.0f;
      this->net_sent = 0.0;
      this->net_recv = 0.0;
    }
  }

  explicit SystemStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time(_alloc, _init),
    hostname(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hostname = "";
      this->cpu_usage = 0.0f;
      this->memory_usage = 0.0f;
      this->memory_total = 0.0f;
      this->memory_available = 0.0f;
      this->net_sent = 0.0;
      this->net_recv = 0.0;
    }
  }

  // field types and members
  using _time_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _time_type time;
  using _hostname_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _hostname_type hostname;
  using _cpu_usage_type =
    float;
  _cpu_usage_type cpu_usage;
  using _memory_usage_type =
    float;
  _memory_usage_type memory_usage;
  using _memory_total_type =
    float;
  _memory_total_type memory_total;
  using _memory_available_type =
    float;
  _memory_available_type memory_available;
  using _net_sent_type =
    double;
  _net_sent_type net_sent;
  using _net_recv_type =
    double;
  _net_recv_type net_recv;

  // setters for named parameter idiom
  Type & set__time(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->time = _arg;
    return *this;
  }
  Type & set__hostname(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->hostname = _arg;
    return *this;
  }
  Type & set__cpu_usage(
    const float & _arg)
  {
    this->cpu_usage = _arg;
    return *this;
  }
  Type & set__memory_usage(
    const float & _arg)
  {
    this->memory_usage = _arg;
    return *this;
  }
  Type & set__memory_total(
    const float & _arg)
  {
    this->memory_total = _arg;
    return *this;
  }
  Type & set__memory_available(
    const float & _arg)
  {
    this->memory_available = _arg;
    return *this;
  }
  Type & set__net_sent(
    const double & _arg)
  {
    this->net_sent = _arg;
    return *this;
  }
  Type & set__net_recv(
    const double & _arg)
  {
    this->net_recv = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    status_interfaces::msg::SystemStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const status_interfaces::msg::SystemStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      status_interfaces::msg::SystemStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      status_interfaces::msg::SystemStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__status_interfaces__msg__SystemStatus
    std::shared_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__status_interfaces__msg__SystemStatus
    std::shared_ptr<status_interfaces::msg::SystemStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SystemStatus_ & other) const
  {
    if (this->time != other.time) {
      return false;
    }
    if (this->hostname != other.hostname) {
      return false;
    }
    if (this->cpu_usage != other.cpu_usage) {
      return false;
    }
    if (this->memory_usage != other.memory_usage) {
      return false;
    }
    if (this->memory_total != other.memory_total) {
      return false;
    }
    if (this->memory_available != other.memory_available) {
      return false;
    }
    if (this->net_sent != other.net_sent) {
      return false;
    }
    if (this->net_recv != other.net_recv) {
      return false;
    }
    return true;
  }
  bool operator!=(const SystemStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SystemStatus_

// alias to use template instance with default allocator
using SystemStatus =
  status_interfaces::msg::SystemStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace status_interfaces

#endif  // STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_HPP_
