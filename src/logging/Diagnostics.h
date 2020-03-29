//
// Created by arseny on 23/02/2020.
//

#ifndef NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
#define NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#ifdef _RELEASE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#endif

#include <optional>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/spdlog.h"

#define INFO(logger, ...)  logger->info(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define WARNING(logger, ...)  logger->warning(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define ERROR(logger, ...)  logger->error(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define FATAL(logger, ...)  logger->fatal(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define TRACE(logger, ...)  logger->trace(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define DEBUG(...)  spdlog::debug(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);

namespace hare::logging {
/// Diagnostic module for correct logging.
class Diagnostics {
 public:
  Diagnostics() = delete;
  ~Diagnostics() = delete;
  /// Initialisation of diagnostic module.
  /// Should be called before using of any functionality.
  static void Initialize();
  /// Getter for logging level.
  /// \return new current log level
  static spdlog::level::level_enum GetCurrentLogLevel() noexcept;
  /// Setter for logging level.
  /// \param new_level new log level
  static void SetCurrentLogLevel(spdlog::level::level_enum new_level);
  /// Getter for logging format pattern.
  /// \return current format
  static std::string_view GetCurrentLogPattern() noexcept;
  /// Setter for logging format pattern.
  /// \param new_pattern new format
  static void SetCurrentLogPattern(std::string_view new_pattern);
  /// Was Initialize() function called or not.
  static bool truncate_file_at_start;
 protected:
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  const static std::string logger_name;
  /// File name log to.
  const static std::string log_file_name;
  /// Default value for date formatting. Called if date_format is empty.
  const static std::string default_date_format;
  /// Default value for level formatting. Called if level_format is empty.
  const static std::string default_level_format;
  /// Format string for log level. May be empty.
  const static std::optional<std::string> level_format;
  /// Format string for log datetime. May be empty.
  const static std::optional<std::string> date_format;
 private:
  /// Was Initialize() function called or not.
  static bool initialized_;
  static std::mutex initialization_locker_;
  static spdlog::level::level_enum current_level_;
  static std::string log_format_;
};
}

#endif //NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
