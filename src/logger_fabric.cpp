#include "pch.h"
#include "logger_fabric.h"

namespace hare {
std::map<std::string, hlogger_ptr> logger_fabric::logger_map_{};
std::shared_mutex logger_fabric::data_mutex_{};

hlogger_ptr logger_fabric::get_logger() {
  std::shared_lock lock(data_mutex_);
  if (logger_map_.empty()) {
    static hlogger_ptr static_logger = std::make_shared<hlogger>();
    return static_logger;
  }
  return logger_map_.begin()->second;
}

hlogger_ptr logger_fabric::get_logger(const std::string &logger_name) {
  if (logger_name.empty()) {
    return get_logger();
  }

  {
    std::shared_lock lock(data_mutex_);
    const auto logger_iter = logger_map_.find(logger_name);
    if (logger_iter != logger_map_.cend()) {
      return logger_iter->second;
    }
  }

  std::string project_name;
  std::string module_name;
  if (!hare::config::parse_logger_name(logger_name, project_name, module_name)) {
    project_name = logger_name;
    module_name.clear();
  }

  if (register_logger(std::make_unique<config_default>(project_name, module_name))) {
    std::shared_lock lock(data_mutex_);
    return logger_map_.find(logger_name)->second;
  }

  return get_logger();
}

hlogger_ptr logger_fabric::get_logger(const std::string &project_name, const std::string &module_name) {
  return get_logger(hare::config::create_logger_name(project_name, module_name));
}

bool logger_fabric::is_logger_registered(const std::string &logger_name) {
  std::shared_lock lock(data_mutex_);
  return logger_map_.contains(logger_name);
}

bool logger_fabric::register_logger(config_ptr &&config) {
  std::string name = config->get_logger_name();
  if (is_logger_registered(name)) {
    return false;
  }

  auto new_logger_ptr = std::make_unique<hlogger>(std::move(config));

  std::unique_lock lock(data_mutex_);
  logger_map_.emplace(std::move(name), std::move(new_logger_ptr));
  return true;
}
} // namespace hare
