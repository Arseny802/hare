#include "pch.h"

#include <algorithm>

#include "logger_fabric.h"

namespace hare {
std::map<std::string, hlogger_ptr> logger_fabric::logger_map_{};
std::shared_mutex logger_fabric::data_mutex_{};
std::string logger_fabric::default_logger_name;

namespace {
inline std::string fix_name(std::string_view name) {
  while (!name.empty() && name.ends_with('.')) {
    name.remove_suffix(1);
  }
  return name.data();
}
} // namespace

hlogger_ptr logger_fabric::get_logger() {
  std::shared_lock lock(data_mutex_);
  if (logger_map_.empty()) {
    static hlogger_ptr static_logger = std::make_shared<hlogger>();
    return static_logger;
  }
  if (!default_logger_name.empty()) {
    auto found_default_logger = logger_map_.find(default_logger_name);
    if (found_default_logger != logger_map_.end()) {
      return found_default_logger->second;
    }
  }

  return logger_map_.begin()->second;
}

hlogger_ptr logger_fabric::get_logger(const std::string& logger_name) {
  if (logger_name.empty()) {
    return get_logger();
  }

  const auto fixed_name = fix_name(logger_name);
  {
    std::shared_lock lock(data_mutex_);
    auto logger_iter = logger_map_.find(logger_name);
    if (logger_iter != logger_map_.cend()) {
      return logger_iter->second;
    }
    logger_iter = logger_map_.find(fixed_name);
    if (logger_iter != logger_map_.cend()) {
      return logger_iter->second;
    }
  }

  std::string project_name;
  std::string module_name;
  if (!hare::config::parse_logger_name(fixed_name, project_name, module_name)) {
    project_name = fixed_name;
    module_name.clear();
  }

  if (register_logger(std::make_unique<config_default>(project_name, module_name))) {
    std::shared_lock lock(data_mutex_);
    return logger_map_.find(fixed_name)->second;
  }

  return get_logger();
}

hlogger_ptr logger_fabric::get_logger(const std::string& project_name, const std::string& module_name) {
  return get_logger(hare::config::create_logger_name(project_name, module_name));
}

bool logger_fabric::is_logger_registered(const std::string& logger_name) {
  const auto fixed_name = fix_name(logger_name);
  std::shared_lock lock(data_mutex_);
  return logger_map_.contains(logger_name) || logger_map_.contains(fixed_name);
}

bool logger_fabric::set_default_logger(const std::string& logger_name) {
  const auto fixed_name = fix_name(logger_name);
  if (!is_logger_registered(fixed_name)) {
    return false;
  }

  default_logger_name = fixed_name;
  return true;
}

bool logger_fabric::register_logger(config_ptr&& config) {
  if (is_logger_registered(config->get_logger_name())) {
    return false;
  }

  std::string name = fix_name(config->get_logger_name());
  auto new_logger_ptr = std::make_unique<hlogger>(std::move(config));

  std::unique_lock lock(data_mutex_);
  logger_map_.emplace(std::move(name), std::move(new_logger_ptr));
  return true;
}

void logger_fabric::do_for_all(std::function<void(const hlogger_ptr)>&& task) {
  std::shared_lock lock(data_mutex_);
  for (const auto& [_, logger]: logger_map_) {
    task(logger);
  }
}
} // namespace hare
