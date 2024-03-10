#pragma once

#include <cstdint>
namespace hare {
/// Type for diagnostic Level enumeration value.
using hlevels_t = uint8_t;
/// Diagnostic Levels, from 'Fatal' (0) to 'Trace' (6).
enum class hlevels : hlevels_t {
  /// Disable logging at all.
  off = 0,
  /// Highest Level, Error for program exit / restart.
  fatal = 1,
  /// Serious unexpected Error, important to read.
  critical = 2,
  /// Any Error occurred while program executing.
  error = 3,
  /// Expected behaviour, but not OK for execution.
  warning = 4,
  /// Status message to Trace program strategy work.
  info = 5,
  /// Checkout message for program debugging.
  /// May be similar with TRACE message Level.
  debug = 6,
  /// Lowest Level, any helpful text for Debug.
  /// May be similar with DEBUG message Level.
  trace = 7
};
} // namespace hare
