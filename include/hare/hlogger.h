#pragma once
#include "config.h"
#include "details/config_default.h"
#include "hlevels.h"

#if __has_include(<format>)
#  include <format>
#else
#  include <fmt/format.h>
#endif

#include <memory>
#include <mutex>
#include <optional>
#include <string_view>

namespace hare {
  /*!
   * @brief The hlogger class provides logging functionality.
   */
  class hlogger final {
public:
    /**
     * Constructor for the hlogger class, which initializes a logger object with optional configuration.
     * If no configuration is provided, it defaults to using a config_default object.
     *
     * @param config Optional configuration pointer
     */
    explicit hlogger(config_ptr config = std::make_unique<config_default>());
    /**
     * Destructor for the hlogger class. Releases any resources held by the logger object.
     */
    ~hlogger();

    /**
     * Traces a message at the specified log level.
     *
     * @param log_message The message to be logged.
     */
    void trace(std::string_view log_message) noexcept;
    /**
     * Logs a debug-level message.
     *
     * @param log_message The message to be logged.
     */
    void debug(std::string_view log_message) noexcept;
    /**
     * Logs an informational-level message.
     *
     * @param log_message The message to be logged.
     */
    void info(std::string_view log_message) noexcept;
    /**
     * Logs a warning-level message.
     *
     * @param log_message The message to be logged.
     */
    void warn(std::string_view log_message) noexcept;

    /**
     * Logs a warning-level message (alternative name).
     *
     * @param log_message The message to be logged.
     */
    void warning(std::string_view log_message) noexcept;

    /**
     * Logs an error-level message.
     *
     * @param log_message The message to be logged.
     */
    void error(std::string_view log_message) noexcept;

    /**
     * Logs a critical-level message.
     *
     * @param log_message The message to be logged.
     */
    void critical(std::string_view log_message) noexcept;

    /**
     * Logs a fatal-level message.
     *
     * @param log_message The message to be logged.
     */
    void fatal(std::string_view log_message) noexcept;

    /**
     * Overload of the trace method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void trace(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      trace(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      trace(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the debug method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void debug(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      debug(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      debug(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the info method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void info(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      info(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      info(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the warn method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void warn(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      warn(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      warn(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the warning method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void warning(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      warning(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      warning(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the error method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void error(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      error(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      error(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }
    /**
     * Overload of the critical method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void critical(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      critical(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      critical(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }

    /**
     * Overload of the fatal method that accepts a format string and variable arguments.
     *
     * This method uses the `std::format` function to construct the log message.
     * The `...args` syntax is used to capture any number of arguments to be
     * passed to the `std::vformat` function.
     *
     * @tparam T The type of the variable arguments.
     * @param log_format_message A format string that describes the log message.
     * @param args Variable arguments that are used to construct the log message.
     */
    template<typename... Args>
    void fatal(const std::string_view log_format_message, Args&&... args) noexcept {
#ifdef __cpp_lib_format
      fatal(std::vformat(log_format_message, std::make_format_args(args...)));
#else
      fatal(fmt::vformat(log_format_message, std::make_format_args(args...)));
#endif
    }

    /**
     * Returns a copy of the current configuration.
     *
     * This method provides a way to get a snapshot of the current configuration
     * without modifying the original configuration object.
     *
     * @return A shared pointer to the copied configuration.
     */
    [[nodiscard]] config_ptr get_config_copy() const;

private:
    /**
     * Initializes the logger with its settings.
     *
     * This method is called once at startup and sets up the logger's
     * internal state according to its current configuration.
     */
    void initialize();
    /**
     * Checks whether a logging level is enabled or not.
     *
     * @param level The logging level to check for enablement.
     * @return A boolean indicating whether the specified level is enabled.
     */
    [[nodiscard]] constexpr bool is_level_enabled(hlevels level) const;

    /// This member variable stores the current configuration of the logger.
    /// It provides a way to access and manipulate the logger's settings.
    config_ptr config_;

    struct logger_pimpl;
    // This member variable holds the internal implementation details
    // of the logger, allowing for efficient management of log messages
    std::unique_ptr<logger_pimpl> logger_pimpl_;
  };

  using hlogger_ptr = std::shared_ptr<hlogger>; // Defines a shared pointer type alias for the hlogger class.
} // namespace hare
