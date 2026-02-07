#pragma once
#include <string_view>
#include <utility>

#if HARE_ENABLE_STD_FORMAT && __has_include(<format>)
#  include <format>
namespace fmt_impl = std;
#else
#  include <fmt/format.h>
namespace fmt_impl = fmt;
#endif

namespace hare {
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
 * Logs a message with the `fatal` level.
 *
 * @param log_message The message to be logged.
 */
void fatal(const std::string_view log_message) noexcept;

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void trace(const std::string_view log_format_message, Args&&... args) noexcept {
  trace(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void debug(const std::string_view log_format_message, Args&&... args) noexcept {
  debug(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void info(const std::string_view log_format_message, Args&&... args) noexcept {
  info(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void warn(const std::string_view log_format_message, Args&&... args) noexcept {
  warn(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void warning(const std::string_view log_format_message, Args&&... args) noexcept {
  warning(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void error(const std::string_view log_format_message, Args&&... args) noexcept {
  error(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// \param log_format_message Format of the message to be logged.
/// \param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void critical(const std::string_view log_format_message, Args&&... args) noexcept {
  critical(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}

/// Logs a message with the `fatal` level.
/// @param log_format_message Format of the message to be logged.
/// @param args Arguments of log message, passed to fmt::vformat.
template<typename... Args>
inline void fatal(const std::string_view log_format_message, Args&&... args) noexcept {
  // Call the actual logging function with the formatted message.
  fatal(fmt_impl::vformat(log_format_message, fmt_impl::make_format_args(std::forward<Args...>(args...))));
}
} // namespace hare