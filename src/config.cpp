#include "pch.h"

#include "hare/config.h"
#include "hare/config_custom.h"
#include "hare/config_default.h"
#include "logger_fabric.h"

namespace hare {

config::config(std::string project_name, htypes_mask_t htypes_mask, hare::hlevels level):
    project_name_(std::move(project_name)),
    logger_min_level_(level),
    htypes_mask_(htypes_mask) { }

config::~config() = default;

std::string config::initialize_logger(const char project[], const char module[], ptr&& config, bool throw_on_error) {
  if (!config) {
    config_custom default_config;
    default_config.set_project_name(project);
    default_config.set_module_name(module);

    hare::sinks_info sinks_info;
    sinks_info.fs.truncate = false;
    sinks_info.synchronize = true;

    default_config.set_sinks_info(std::move(sinks_info));
    config = std::make_unique<hare::config_custom>(default_config);
  } else {
    if (config->get_project_name().empty()) {
      config->set_project_name(project);
    }
    if (config->get_module_name().empty()) {
      config->set_module_name(module);
    }
  }

  auto logger_name = config->get_logger_name();
  const bool result = hare::logger_fabric::register_logger(std::move(config));
  assert(!throw_on_error || (result && "logger registration failed!"));
  return logger_name;
}

std::string config::get_logger_name() const {
  auto name = create_logger_name(project_name_, module_name_);
  while (!name.empty() && name.ends_with('.')) {
    name.pop_back();
  }
  return name;
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

std::string config::create_logger_name(const std::string& project_name, const std::string& module_name) {
  std::string name = project_name.empty() ? config_default::get_default_project_name() : project_name;
  if (module_name.empty()) {
    return name;
  }

  return name + "." + module_name;
}

bool config::parse_logger_name(const std::string& logger_name, std::string& project_name, std::string& module_name) {
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
