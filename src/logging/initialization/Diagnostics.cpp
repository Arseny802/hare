//
// Created by arseny on 23/02/2020.
//

#include "Diagnostics.h"

namespace hare::logging {

#ifdef _DEBUG
spdlog::level::level_enum Diagnostics::current_level_ = spdlog::level::trace;
#else
#ifdef _RELEASE
spdlog::Level::level_enum Diagnostics::current_level_ = spdlog::Level::info;
#else
spdlog::Level::level_enum Diagnostics::current_level_ = spdlog::Level::trace;
#endif
#endif

const std::string Diagnostics::kProjectName = std::string(default_project_name_);
const std::string Diagnostics::kLoggerName = kProjectName;
const std::string Diagnostics::kLogFileName = fmt::format("logs/{}.log", kProjectName);

std::string_view Diagnostics::log_format_ = "{date} [thread %t] {Level} %! %v";
std::mutex Diagnostics::initialization_locker_;
bool Diagnostics::truncate_file_at_start_ = false;
bool Diagnostics::initialized_ = false;

void Diagnostics::Initialize() {
  initialization_locker_.lock();
  if (initialized_) {
	initialization_locker_.unlock();
	return;
  }

  {
	std::vector<spdlog::sink_ptr> sinks;

	sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
	sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>
		                (kLogFileName.data(), 0, 0, truncate_file_at_start_, 14));

	auto combined_logger = std::make_shared<spdlog::logger>
		(kLoggerName.data(), begin(sinks), end(sinks));
	spdlog::set_default_logger(combined_logger);
  }

  spdlog::set_level(current_level_);
  spdlog::info("Initialized logger with name '{}'.", kLoggerName);
  initialized_ = true;
  initialization_locker_.unlock();
}

spdlog::level::level_enum Diagnostics::GetCurrentLogLevel() noexcept {
  return current_level_;
}

std::string_view Diagnostics::GetCurrentLogPattern() noexcept {
  return log_format_;
}
std::string_view Diagnostics::GetLogFileName() noexcept {
  return std::string_view();
}

void Diagnostics::SetCurrentLogPattern(std::string_view new_pattern) {
  spdlog::set_pattern(fmt::format(new_pattern.data(),
                                  fmt::arg("date", date_format_.value_or(default_date_format_)),
                                  fmt::arg("Level", level_format_.value_or(default_level_format_)))
  );
  log_format_ = new_pattern.data();
}

/// Usage example, ignore it.
void Example() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some Error message with arg: {}", 1);
  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");
  spdlog::debug("This message should be displayed..");

  // define SPDLOG_ACTIVE_LEVEL to desired Level
  SPDLOG_TRACE("Some Trace message with param {}", 42);
  SPDLOG_DEBUG("Some Debug message");
}

}
