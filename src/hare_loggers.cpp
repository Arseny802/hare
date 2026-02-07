#include "pch.h"

#include "hare/hare_loggers.h"
#include "logger_fabric.h"

namespace hare {
hlogger_ptr get_logger(const std::string& project_name, const std::string& module_name) {
  return logger_fabric::get_logger(project_name, module_name);
}

bool register_logger(config_ptr&& config) {
  return logger_fabric::register_logger(std::move(config));
}

bool set_default_logger(const std::string& default_logger_name) {
  return logger_fabric::set_default_logger(default_logger_name);
}
} // namespace hare
