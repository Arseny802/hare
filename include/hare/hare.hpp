#pragma once
#include "details/autolog.h"

#if __has_include(<format>)
#include <format>
namespace fmt_impl = std;
#else
#include <fmt/format.h>
namespace fmt_impl = fmt;
#endif

namespace hare {
///
/// \param project_name
/// \param module_name
hlogger_ptr get_logger(const std::string& project_name,
                       const std::string& module_name = std::string());
///
/// \param config
bool register_logger(config_ptr&& config);

bool set_default_logger(const std::string& default_logger_name);

/**
 * Logs a message with the `trace` level.
 *
 * @param log_message The message to be logged.
 */
void trace(const std::string_view log_message) noexcept;
/**
 * Logs a message with the `debug` level.
 *
 * @param log_message The message to be logged.
 */
void debug(const std::string_view log_message) noexcept;
/**
 * Logs a message with the `info` level.
 *
 * @param log_message The message to be logged.
 */
void info(const std::string_view log_message) noexcept;
/**
 * Logs a message with the `warn` or `warning` level.
 *
 * @param log_message The message to be logged.
 */
void warn(const std::string_view log_message) noexcept;
/**
 * Logs a message with the `warn` or `warning` level.
 *
 * @param log_message The message to be logged.
 */
void warning(const std::string_view log_message) noexcept;

/**
 * Logs a message with the `error` level.
 *
 * @param log_message The message to be logged.
 */
void error(const std::string_view log_message) noexcept;

/**
 * Logs a message with the `critical` level.
 *
 * @param log_message The message to be logged.
 */
void critical(const std::string_view log_message) noexcept;

/**
 * Logs a message with the ``fatal` level.
 *
 * @param log_message The message to be logged.
 */
void fatal(const std::string_view log_message) noexcept;

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void trace(const std::string_view log_format_message, Args&&... args) noexcept {
  trace(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void debug(const std::string_view log_format_message, Args&&... args) noexcept {
  debug(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void info(const std::string_view log_format_message, Args&&... args) noexcept {
  info(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void warn(const std::string_view log_format_message, Args&&... args) noexcept {
  warn(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void warning(const std::string_view log_format_message, Args&&... args) noexcept {
  warning(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void error(const std::string_view log_format_message, Args&&... args) noexcept {
  error(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template <typename... Args>
void critical(const std::string_view log_format_message, Args&&... args) noexcept {
  critical(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}

///
/// Logs a message with the `fatal` level.
///
/// @param log_format_message The message to be logged.
/// @param args Arguments to be formatted into the log message.
template <typename... Args>
void fatal(const std::string_view log_format_message, Args&&... args) noexcept {
  // Call the actual logging function with the formatted message.
  fatal(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(args...)));
}
}  // namespace hare

// Initialize this macros before including file in project to use AUTO* macros
#ifndef PROJECT_NAME
#define PROJECT_NAME "hare"
#endif
#ifndef MODULE_NAME
#define MODULE_NAME ""
#endif
#ifndef LOGGER_NAME
#define LOGGER_NAME PROJECT_NAME "." MODULE_NAME
#endif

/**
 * Automatically flushes log buffer in the end of critical function execution
 * for current logger object.
 */
#define AUTOFLUSH hare::details::auto_flusher unique_local__flusher(LOGGER_NAME);
/**
 * Automatically flushes log buffer in the end of critical function execution
 * for all logger objects.
 */
#define AUTOFLUSH_ALL hare::details::auto_flusher_all unique_local__flusher{};

/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACE \
  hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically logs messages with obj_name based on the file and line number where this macro is
 * used.
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACE4(obj_name) \
  hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME, #obj_name);
/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACEF \
  hare::details::auto_flusing_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACEFA \
  hare::details::auto_flusing_all_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);

/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASURE \
  hare::details::auto_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically mesuress with obj_name how long a block of code takes.
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASURE4(obj_name) \
  hare::details::auto_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME, #obj_name);
/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASUREF \
  hare::details::auto_flusing_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASUREFA                                                         \
  hare::details::auto_flusing_all_measure unique_local__measure(__FILE__,     \
                                                                __FUNCTION__, \
                                                                LOGGER_NAME);
