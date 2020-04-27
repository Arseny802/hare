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

/*
#define INFO(logger, ...)  logger->info(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define WARNING(logger, ...)  logger->warning(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define ERROR(logger, ...)  logger->error(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define FATAL(logger, ...)  logger->fatal(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define TRACE(logger, ...)  logger->trace(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
#define DEBUG(...)  spdlog::debug(__FILE__ ## " line " ## SPDLOG_STR(__LINE__) ## ": " ## __VA_ARGS__);
*/

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
#ifdef PROJECT_NAME
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view logger_name = PROJECT_NAME;
  /// File name log to.
  static constexpr std::string_view log_file_name = "logs/" PROJECT_NAME ".log";
#else
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view logger_name =  "hare";
  /// File name log to.
  static constexpr std::string_view log_file_name = "logs/hare";
#endif
  /// Default value for date formatting. Called if date_format is empty.
  static constexpr std::string_view default_date_format = "[%c]";
  /// Default value for level formatting. Called if level_format is empty.
  static constexpr std::string_view default_level_format = "[%l]";
  /// Format string for log level. May be empty.
  static constexpr std::optional<std::string_view> level_format = "[%^%=4!l%$]";
  /// Format string for log datetime. May be empty.
  static constexpr std::optional<std::string_view> date_format = "[%d/%m/%C %H:%M:%S.%F]";

 private:
  /// Was Initialize() function called or not.
  static bool initialized_;
  static std::mutex initialization_locker_;
  static spdlog::level::level_enum current_level_;
  static std::string_view log_format_;
};
}

#endif //NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
