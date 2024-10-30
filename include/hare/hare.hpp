#pragma once
#include "details/auto_tracer.h"

#if __has_include(<format>)
#  include <format>
#else
#  include <fmt/format.h>
#endif

namespace hare {
  ///
  /// \param project_name
  /// \param module_name
  hlogger_ptr get_logger(const std::string& project_name, const std::string& module_name = std::string());
  ///
  /// \param config
  bool register_logger(config_ptr&& config);

  bool set_default_logger(const std::string& default_logger_name);

  /**
   * Logs a message with the `trace` level.
   *
   * @param log_message The message to be logged.
   */
  void trace(std::string_view log_message) noexcept;
  /**
   * Logs a message with the `debug` level.
   *
   * @param log_message The message to be logged.
   */
  void debug(std::string_view log_message) noexcept;
  /**
   * Logs a message with the `info` level.
   *
   * @param log_message The message to be logged.
   */
  void info(std::string_view log_message) noexcept;
  /**
   * Logs a message with the `warn` or `warning` level.
   *
   * @param log_message The message to be logged.
   */
  void warn(std::string_view log_message) noexcept;

  /**
   * Logs a message with the `error`, `critical`, or `fatal` level.
   *
   * @param log_message The message to be logged.
   */
  void error(std::string_view log_message) noexcept;

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void trace(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    trace(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    trace(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void debug(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    debug(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    debug(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void info(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    info(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    info(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void warn(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    warn(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    warn(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void warning(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    warning(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    warning(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void error(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    error(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    error(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// \tparam Args
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void critical(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
    critical(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    critical(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }

  ///
  /// Logs a message with the `fatal` level.
  ///
  /// @param log_format_message The message to be logged.
  /// @param args Arguments to be formatted into the log message.
  template<typename... Args>
  void fatal(const std::string_view log_format_message, Args&&... args) noexcept {
// Call the actual logging function with the formatted message.
#ifdef __cpp_lib_format
    fatal(std::vformat(log_format_message, std::make_format_args(args...)));
#else
    fatal(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
  }
} // namespace hare

/**
 * Automatically logs messages based on the file and line number where this macro is used.
 */
#define AUTOLOG hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__);
/**
 * Automatically logs messages with obj_name based on the file and line number where this macro is used.
 */
#define AUTOLOG4(obj_name) hare::details::auto_tracer obj_name(__FILE__, __FUNCTION__, "", #obj_name);
/**
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOLOG_IN(logger_name) hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__, logger_name);
/**
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOLOG4_IN(logger_name, obj_name) \
  hare::details::auto_tracer obj_name(__FILE__, __FUNCTION__, logger_name, #obj_name);

/**
 * Automatically mesuress how long a block of code takes.
 */
#define AUTOMEASURE hare::details::auto_measure unique_local__tracer(__FILE__, __FUNCTION__);
/**
 * Automatically mesuress with obj_name how long a block of code takes.
 */
#define AUTOMEASURE4(obj_name) hare::details::auto_measure obj_name(__FILE__, __FUNCTION__, "", #obj_name);
/**
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 *
 * @param logger_name The name of the logger.
 */
#define AUTOMEASURE_IN(logger_name) \
  hare::details::auto_measure unique_local__tracer(__FILE__, __FUNCTION__, logger_name);
/**
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 *
 * @param logger_name The name of the logger.
 */
#define AUTOMEASURE4_IN(logger_name, obj_name) \
  hare::details::auto_measure obj_name(__FILE__, __FUNCTION__, logger_name, #obj_name);
