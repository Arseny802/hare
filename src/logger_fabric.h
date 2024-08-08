#pragma once
#include "hare/hlogger.h"

namespace hare {
class logger_fabric {
 public:
  static hlogger_ptr get_logger();
  static hlogger_ptr get_logger(const std::string& logger_name);
  static hlogger_ptr get_logger(const std::string& project_name, const std::string& module_name);
  static bool is_logger_registered(const std::string& logger_name);
  static bool set_default_logger(const std::string & default_logger_name);
  static bool register_logger(config_ptr&& config);

 private:
  static std::map<std::string, hlogger_ptr> logger_map_;
  static std::shared_mutex data_mutex_;
  static std::string default_logger_name;
};
} // namespace hare
