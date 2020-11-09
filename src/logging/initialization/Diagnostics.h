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
#include "../configuration/config.h"

namespace hare::logging {
/// Diagnostic module for correct logging.
class Diagnostics {
 public:
  Diagnostics() = delete;
  ~Diagnostics() = delete;
  /// Initialisation of diagnostic module.
  /// Should be called before using of any functionality.
  static void Initialize();
 private:
  /// Getter for logging Level.
  /// \return new current log Level
  static spdlog::level::level_enum GetCurrentLogLevel() noexcept;
  /// Getter for logging format pattern.
  /// \return current format
  static std::string_view GetCurrentLogPattern() noexcept;

  static std::string_view GetLogFileName() noexcept;

  void SetCurrentLogPattern(std::string_view new_pattern);

  /// Default value for date formatting. Called if date_format_ is empty.
  static constexpr std::string_view default_date_format_ = "[%d/%m/%C %H:%M:%S.%F]";
  /// Default value for Level formatting. Called if level_format_ is empty.
  static constexpr std::string_view default_level_format_ = "[%^%=4!l%$]";
#ifdef PROJECT_NAME
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view default_project_name_ = PROJECT_NAME;
#else
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view default_project_name_ =  "hare";
#endif
  static const std::string kProjectName;
  /// Logger name, shown in log message
  static const std::string kLoggerName;
  /// File name log to.
  static const std::string kLogFileName;
  /// Format string for log Level. May be empty.
  const std::optional<std::string_view> level_format_;
  /// Format string for log datetime. May be empty.
  const std::optional<std::string_view> date_format_;

  static Config config_;


  /// Was Initialize() function called or not.
  static bool initialized_;
  /// Was Initialize() function called or not.
  static bool truncate_file_at_start_;
  static std::mutex initialization_locker_;
  static spdlog::level::level_enum current_level_;
  static std::string_view log_format_;
};
}

#endif //NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
