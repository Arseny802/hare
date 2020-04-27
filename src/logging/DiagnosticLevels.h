//
// Created by arseny on 28/03/2020.
//

#ifndef HARE_SRC_LOGGING_DIAGNOSTICLEVELS_H_
#define HARE_SRC_LOGGING_DIAGNOSTICLEVELS_H_

#include <cstdint>
namespace hare {
/// Type for diagnostic level enumeration value.
using level = uint8_t;
/// Diagnostic levels, from 'fatal' (0) to 'trace' (6).
enum class levels : level {
  /// Highest level, error for program exit / restart.
  fatal = 0,
  /// Serious unexpected error, important to read.
  critical = 1,
  /// Any error occurred while program executing.
  error = 2,
  /// Expected behaviour, but not OK for execution.
  warning = 3,
  /// Status message to trace program strategy work.
  info = 4,
  /// Checkout message for program debugging.
  /// May be similar with TRACE message level.
  debug = 5,
  /// Lowest level, any helpful text for debug.
  /// May be similar with DEBUG message level.
  trace = 6,
  /// Disable logging at all.
  off = 7
};
}
#endif //HARE_SRC_LOGGING_DIAGNOSTICLEVELS_H_
