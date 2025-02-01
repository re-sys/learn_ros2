// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_
#define STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'time'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'hostname'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SystemStatus in the package status_interfaces.
typedef struct status_interfaces__msg__SystemStatus
{
  /// recored the time when the status is updated
  builtin_interfaces__msg__Time time;
  /// the hostname of the system
  rosidl_runtime_c__String hostname;
  /// the percentage of CPU usage
  float cpu_usage;
  /// the percentage of memory usage
  float memory_usage;
  /// the total memory of the system
  float memory_total;
  /// the available memory of the system
  float memory_available;
  /// the amount of data sent through the network
  double net_sent;
  /// the amount of data received through the network
  double net_recv;
} status_interfaces__msg__SystemStatus;

// Struct for a sequence of status_interfaces__msg__SystemStatus.
typedef struct status_interfaces__msg__SystemStatus__Sequence
{
  status_interfaces__msg__SystemStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} status_interfaces__msg__SystemStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_
