#pragma once

#include <string_view>
#include <mutex>
#include "../configuration/config.h"
#include "../configuration/default_config.h"

#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/spdlog.h"
#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#ifdef _RELEASE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#endif

namespace hare {

///
class Logger {
 public:
  //Logger() = delete;
  explicit Logger(ConfigPtr config = DefaultConfigPtr());
  virtual ~Logger() = default;
  ///
  /// \param log_message
  void Trace(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Debug(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Info(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Warn(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Warning(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Error(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Critical(std::string_view log_message) const noexcept;
  ///
  /// \param log_message
  void Fatal(std::string_view log_message) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Trace(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Debug(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Info(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Warn(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Warning(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Error(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Critical(std::string_view log_format_message, const T &args...) const noexcept;
  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename T>
  void Fatal(std::string_view log_format_message, const T &args...) const noexcept;

 private:
  void InitializeDefaultLogger();
  [[nodiscard]] constexpr bool IsLevelEnabled(Levels level) const;

  /// Default value for date formatting. Called if date_format_ is empty.
  static constexpr std::string_view default_date_format_ = "[%d/%m/%C %H:%M:%S.%F]";
  /// Default value for Level formatting. Called if level_format_ is empty.
  static constexpr std::string_view default_level_format_ = "[%^%=4!l%$]";

  /// Logger name, shown in log message
  const std::string kProjectName;
  /// File name log to.
  const std::string kLogFileName;
  /// Format string for log Level. May be empty.
  const std::optional<std::string> level_format_;
  /// Format string for log datetime. May be empty.
  const std::optional<std::string> date_format_;
  /// Was Initialize() function called or not.
  bool initialized_;
  ///
  bool truncate_file_at_start_;
  std::mutex initialization_locker_;
  spdlog::level::level_enum current_level_;
  Levels current_level2_;
  std::string_view log_format_;
};
}
