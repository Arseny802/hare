#include "hare/config.h"
#include "hare/details/config_default.h"

#include <utility>


namespace hare {

config::config(std::string project_name, hare::hlevels level) {
  project_name_ = std::move(project_name);
  logger_min_level_ = level;
}

config::~config() = default;

std::string config::get_logger_name() const {
  return create_logger_name(project_name_, module_name_);
}

std::string config::get_project_name() const {
  return project_name_;
}

std::string config::get_module_name() const {
  return module_name_;
}

htypes_mask_t config::get_type_mask() const {
  return htypes_mask_;
}

hlevels config::get_level() const {
  return logger_min_level_;
}

std::optional<std::string> config::get_log_format() const {
  return log_format_;
}

std::optional<std::string> config::get_log_format_date() const {
  return log_format_date_;
}

std::optional<std::string> config::get_log_format_level() const {
  return log_format_level_;
}

const sinks_info& config::get_sinks_info() const {
  return sinks_info_;
}

std::string config::create_logger_name(const std::string &project_name, const std::string &module_name) {
  std::string name = project_name.empty() ? config_default::get_default_project_name() : project_name;
  if (module_name.empty()) {
    return name;
  }

  return name + "." + module_name;
}

bool config::parse_logger_name(const std::string &logger_name, std::string &project_name, std::string &module_name) {
  project_name.clear();
  module_name.clear();

  if (logger_name.empty()) {
    return false;
  }

  const auto delim_pos = logger_name.find('.');
  if (delim_pos == std::string::npos) {
    project_name = logger_name;
    return true;
  }

  project_name = logger_name.substr(0, delim_pos);
  module_name = logger_name.substr(delim_pos + 1);

  return true;
}
} // namespace hare
