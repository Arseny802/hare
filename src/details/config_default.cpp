#include "pch.h"
#include "hare/details/config_default.h"
#include "hare/details/defs.h"

#include "config_defaults_spdlog.h"

namespace hare {

namespace {

constexpr std::string_view default_project_name = "hare";
constexpr htypes_mask_t default_htypes_mask = htypes_mask::console | htypes_mask::file_daily;
constexpr hlevels default_hlevel = hlevels::trace;
}

config_default::config_default(std::string project_name, std::string module_name)
    : config(project_name.empty() ? default_project_name.data() : std::move(project_name),
             default_htypes_mask,
             default_hlevel) {
  module_name_ = std::move(module_name);

#ifdef USE_IMPLEMENTATION_SPDLOG
  config_defaults_spdlog defaults;
  if (module_name_.empty()) {
    log_format_ = defaults.log_format;
  } else {
    log_format_ = defaults.log_format_named;
  }
  log_format_date_ = defaults.log_format_date;
  log_format_level_ = defaults.log_format_level;
#else
  static_assert(false, "No logger implementation enabled - default logger cannot be constructed.");
#endif

  sinks_info_.synchronize = false;

  sinks_info_.fs.truncate = true;
  sinks_info_.fs.max_size = 100 * 1024 * 1024;
  sinks_info_.fs.rotation_hour = 0;
  sinks_info_.fs.rotation_minute = 0;
  sinks_info_.fs.max_files_by_size = 10;
  sinks_info_.fs.max_files_by_date = 21;
}

config_default::~config_default() = default;

void config_default::set_project_name(std::string new_logger_name) {
  project_name_ = std::move(new_logger_name);
}

void config_default::set_hlevel(hlevels new_hlevel) {
  logger_min_level_ = new_hlevel;
}

std::unique_ptr<config> config_default::clone() const {
  return std::make_unique<config_default>(*this);
}

void config_default::set_module_name(std::string new_module_name) {
  module_name_ = std::move(new_module_name);
#ifdef USE_IMPLEMENTATION_SPDLOG
  config_defaults_spdlog defaults;
  if (module_name_.empty()) {
    log_format_ = defaults.log_format;
  } else {
    log_format_ = defaults.log_format_named;
  }
#else
  static_assert(false, "No logger implementation enabled - default logger cannot be constructed.");
#endif
}

std::string config_default::get_default_project_name() {
  return std::string(default_project_name);
}
} // namespace hare
