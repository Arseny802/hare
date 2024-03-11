#include "hare/hlogger.h"
#include "hare/details/defs.h"
#include "logger_fabric.h"

#include <string_view>
#include <mutex>
#include <optional>

#ifdef USE_IMPLEMENTATION_SPDLOG

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#ifdef _RELEASE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#endif
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/spdlog.h"

#include "details/config_defaults_spdlog.h"
#else

#endif

namespace {
#ifdef USE_IMPLEMENTATION_SPDLOG
spdlog::level::level_enum hlevel_to_spdlog_level(const hare::hlevels hare_level) {
  switch (hare_level) {
    case hare::hlevels::off: return spdlog::level::off;
    case hare::hlevels::fatal:
    case hare::hlevels::critical: return spdlog::level::critical;
    case hare::hlevels::error: return spdlog::level::err;
    case hare::hlevels::warning: return spdlog::level::warn;
    case hare::hlevels::info: return spdlog::level::info;
    case hare::hlevels::debug: return spdlog::level::debug;
    case hare::hlevels::trace: return spdlog::level::trace;
    default:return spdlog::level::critical;
  }
}

#else

#endif
}

namespace hare {
#ifdef USE_IMPLEMENTATION_SPDLOG
struct hlogger::logger_pimpl {
  logger_pimpl(const std::string &logger_name, const std::vector<spdlog::sink_ptr> &sinks)
      : logger(logger_name, begin(sinks), end(sinks)) {

  }
  ~logger_pimpl() = default;

  spdlog::logger logger;
};
#else
#endif

hlogger::hlogger(config_ptr config)
    : config_(std::move(config)), initialized_(false) {
  initialize();
}
hlogger::~hlogger() = default;

void hlogger::initialize() {
  const auto logger_name = config_->get_logger_name();

  std::lock_guard<std::mutex> lock(initialization_locker_);
  if (logger_fabric::is_logger_registered(logger_name)) {
    logger_fabric::get_logger(logger_name)->warn(
        "Try to initialise inited logger '{}'.", logger_name);
    return;
  }

#ifdef USE_IMPLEMENTATION_SPDLOG
  config_defaults_spdlog defaults;
  const std::string pattern = fmt::vformat(
      config_->get_log_format().has_value() ?
      config_->get_log_format().value() : defaults.log_format,
      fmt::make_format_args(
          fmt::arg("date", config_->get_log_format_date().has_value() ?
                           config_->get_log_format_date().value() : defaults.log_format_date),
          fmt::arg("Level", config_->get_log_format_level().has_value() ?
                            config_->get_log_format_level().value() : defaults.log_format_level)
      )
  );
  const std::string log_filename = config_->get_project_name() + ".log";

  {
    std::vector<spdlog::sink_ptr> sinks;
    const sinks_info& info = config_->get_sinks_info();

    if (config_->get_type_mask() & htypes_mask::console) {
      auto sink_console = std::make_shared<spdlog::sinks::stdout_sink_st>();
      sink_console->set_level(hlevel_to_spdlog_level(config_->get_level()));
      sink_console->set_pattern(pattern);
      sinks.push_back(sink_console);
    }

    if (config_->get_type_mask() & htypes_mask::file_daily) {
      auto sink_file_daily = std::make_shared<spdlog::sinks::daily_file_sink_st>
          (log_filename, info.fs.rotation_hour, info.fs.rotation_minute, info.fs.truncate, info.fs.max_files);
      sink_file_daily->set_level(hlevel_to_spdlog_level(config_->get_level()));
      sink_file_daily->set_pattern(pattern);
      sinks.push_back(sink_file_daily);
    }

    if (config_->get_type_mask() & htypes_mask::file_rotating) {
      auto sink_file_rotating = std::make_shared<spdlog::sinks::rotating_file_sink_st>
          (log_filename, info.fs.max_size, info.fs.max_files, info.fs.truncate);
      sink_file_rotating->set_level(hlevel_to_spdlog_level(config_->get_level()));
      sink_file_rotating->set_pattern(pattern);
      sinks.push_back(sink_file_rotating);
    }

    logger_pimpl_ = std::make_unique<logger_pimpl>(config_->get_module_name(), sinks);
    logger_pimpl_->logger.set_level(hlevel_to_spdlog_level(config_->get_level()));
    logger_pimpl_->logger.set_pattern(pattern);
  }
#else
#endif

  logger_pimpl_->logger.info("Initialized logger with name '{}'.", logger_name);
  initialized_ = true;
}

void hlogger::trace(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.trace(log_message);
#else
#endif
}

void hlogger::debug(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.debug(log_message);
#else
#endif
}

void hlogger::info(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.info(log_message);
#else
#endif
}

void hlogger::warn(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.warn(log_message);
#else
#endif
}

void hlogger::warning(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.warn(log_message);
#else
#endif
}

void hlogger::error(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.error(log_message);
#else
#endif
}

void hlogger::critical(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.critical(log_message);
#else
#endif
}

void hlogger::fatal(const ::std::string_view log_message) noexcept {
#ifdef USE_IMPLEMENTATION_SPDLOG
  logger_pimpl_->logger.critical(log_message);
#else
#endif
}

config_ptr hlogger::get_config_copy() const {
  return config_->clone();
}

constexpr bool hlogger::is_level_enabled(hlevels level) const {
  if (level == hlevels::off) {
    return config_->get_level() == hlevels::off;
  }
  return config_->get_level() >= level;
}
}; // namespace hare
