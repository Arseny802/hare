#include "hare/details/config_default.h"
#include "hare/details/defs.h"

#include "config_defaults_spdlog.h"

namespace hare {

namespace {

constexpr std::string_view default_project_name_ = "hare";
}

config_default::config_default(std::string project_name, std::string module_name) :
    config(project_name.empty() ? default_project_name_.data() : std::move(project_name)) {
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

  truncate_file_at_start_ = true;
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
  return std::string(default_project_name_);
}
} // namespace hare
