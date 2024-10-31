#include "pch.h"

#include "hare/hare.hpp"
#include "hare/hlogger.h"
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

  void trace(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->trace(log_message);
  }

  void debug(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->debug(log_message);
  }

  void info(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->info(log_message);
  }

  void warn(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->warn(log_message);
  }

  void warning(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->warning(log_message);
  }

  void error(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->error(log_message);
  }

  void critical(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->critical(log_message);
  }

  void fatal(const std::string_view log_message) noexcept {
    logger_fabric::get_logger()->critical(log_message);
  }
} // namespace hare
