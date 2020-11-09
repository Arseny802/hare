//
// Created by arseny on 02/05/2020.
//

#include <vector>
#include "logger.h"

namespace hare {
Logger::Logger(ConfigPtr config)
	: initialized_(false){
  InitializeDefaultLogger();
}

void Logger::InitializeDefaultLogger() {
  std::lock_guard<std::mutex> lock(initialization_locker_);
  if (initialized_) {
	return;
  }

  {
	std::vector<spdlog::sink_ptr> sinks;

	sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
	sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>
		                (kLogFileName, 0, 0, truncate_file_at_start_, 14));

	auto combined_logger = std::make_shared<spdlog::logger>
		(kProjectName, begin(sinks), end(sinks));
	spdlog::set_default_logger(combined_logger);
  }

  spdlog::set_level(current_level_);
  spdlog::set_pattern(fmt::format(log_format_.data(),
                                  fmt::arg("date", date_format_.has_value() ? date_format_.value() : default_date_format_),
                                  fmt::arg("Level", level_format_.has_value() ? level_format_.value() : default_level_format_))
  );
  Info("Initialized logger with name '{}'.", kProjectName);
  initialized_ = true;
}

void Logger::Trace(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::trace)) {
	spdlog::trace(log_message);
  }
}
void Logger::Debug(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::debug)) {
    spdlog::debug(log_message);
  }
}
void Logger::Info(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::info)) {
    spdlog::info(log_message);
  }
}
void Logger::Warn(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::warning)) {
    spdlog::warn(log_message);
  }
}
void Logger::Warning(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::warning)) {
    spdlog::warn(log_message);
  }
}
void Logger::Error(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::error)) {
    spdlog::error(log_message);
  }
}
void Logger::Critical(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::critical)) {
    spdlog::critical(log_message);
  }
}
void Logger::Fatal(std::string_view log_message) const noexcept {
  if (IsLevelEnabled(Levels::fatal)) {
    spdlog::critical(log_message);
  }
}
template<typename T>
void Logger::Trace(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Debug(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Info(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Warn(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Warning(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Error(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Critical(std::string_view log_format_message, const T &args, ...) const noexcept {

}
template<typename T>
void Logger::Fatal(std::string_view log_format_message, const T &args, ...) const noexcept {

}
constexpr bool Logger::IsLevelEnabled(Levels level) const {
  return current_level2_ >= level;
}
}
