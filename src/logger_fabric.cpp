#include "logger_fabric.h"

#include <map>

namespace hare {
namespace {
std::map<std::string, hlogger_ptr> logger_map;
}

hlogger_ptr logger_fabric::get_logger() {
  if (logger_map.empty()) {
    static hlogger_ptr static_logger = std::make_shared<hlogger>();
    return static_logger;
  }
  return logger_map.begin()->second;
}

hlogger_ptr logger_fabric::get_logger(const std::string &logger_name) {
  if (logger_name.empty()) {
    return get_logger();
  }

  const auto logger_iter = logger_map.find(logger_name);
  if (logger_iter != logger_map.cend()) {
    return logger_iter->second;
  }

  std::string project_name;
  std::string module_name;
  if (!hare::config::parse_logger_name(logger_name, project_name, module_name)) {
    project_name = logger_name;
    module_name.clear();
  }

  if (register_logger(std::make_unique<config_default>(project_name, module_name))) {
    return logger_map.find(logger_name)->second;
  }

  return get_logger();
}

hlogger_ptr logger_fabric::get_logger(const std::string& project_name, const std::string& module_name) {
  return get_logger(hare::config::create_logger_name(project_name, module_name));
}

bool logger_fabric::is_logger_registered(const std::string& logger_name) {
  return logger_map.contains(logger_name);
}

bool logger_fabric::register_logger(config_ptr&& config) {
  std::string name = config->get_logger_name();
  const auto logger_iter = logger_map.find(name);
  if (logger_iter == logger_map.cend()) {
    logger_map.emplace(std::move(name), std::make_unique<hlogger>(std::move(config)));
    return true;
  }

  return false;
}
} // namespace hare
