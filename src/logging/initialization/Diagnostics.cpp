//
// Created by arseny on 23/02/2020.
//

#include "Diagnostics.h"
#include "../../memory_tracer/MemoryTracer.h"

namespace hare::logging {

#ifdef _DEBUG
spdlog::level::level_enum Diagnostics::current_level_ = spdlog::level::trace;
std::string_view Diagnostics::log_format_ = "{date} [thread %t] {level} %! %v";

#else
#ifdef _RELEASE
spdlog::level::level_enum Diagnostics::current_level_ = spdlog::level::info;

#ifdef PROJECT_NAME
std::string Diagnostics::log_format_ = "{date} [thread %t] {level} [%n] %v";
#else
std::string Diagnostics::log_format_ = "{date} [thread %t] {level} %v";
#endif

#else
spdlog::level::level_enum Diagnostics::current_level_ = spdlog::level::trace;

#ifdef PROJECT_NAME
std::string Diagnostics::log_format_ = "{date} [thread %t] {level} [%n] %! %v";
#else
std::string Diagnostics::log_format_ = "{date} [thread %t] {level} %! %v";
#endif

#endif
#endif

std::mutex Diagnostics::initialization_locker_;
bool Diagnostics::truncate_file_at_start = false;
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
		                (log_file_name.data(), 0, 0, truncate_file_at_start, 14));

	auto combined_logger = std::make_shared<spdlog::logger>
		(logger_name.data(), begin(sinks), end(sinks));
	spdlog::set_default_logger(combined_logger);
  }

  spdlog::set_level(current_level_);
  spdlog::set_pattern(fmt::format(log_format_.data(),
                                  fmt::arg("date", date_format.value_or(default_date_format)),
                                  fmt::arg("level", level_format.value_or(default_level_format)))
  );
  spdlog::info("Initialized logger with name '{}'.", logger_name);
  initialized_ = true;
  initialization_locker_.unlock();
  hare::MemoryTracer::Enable();
}

spdlog::level::level_enum Diagnostics::GetCurrentLogLevel() noexcept {
  return current_level_;
}

void Diagnostics::SetCurrentLogLevel(spdlog::level::level_enum new_level) {
  spdlog::set_level(new_level);
  current_level_ = new_level;
}

std::string_view Diagnostics::GetCurrentLogPattern() noexcept {
  return log_format_;
}

void Diagnostics::SetCurrentLogPattern(std::string_view new_pattern) {
  spdlog::set_pattern(fmt::format(new_pattern.data(),
                                  fmt::arg("date", date_format.value_or(default_date_format)),
                                  fmt::arg("level", level_format.value_or(default_level_format)))
  );
  log_format_ = new_pattern.data();
}

/// Usage example, ignore it.
void Example() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);
  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");
  spdlog::debug("This message should be displayed..");

  // define SPDLOG_ACTIVE_LEVEL to desired level
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");
}

}
