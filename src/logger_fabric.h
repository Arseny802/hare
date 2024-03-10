#pragma once
#include "hare/hlogger.h"

namespace hare {
class logger_fabric {
 public:
  static hlogger_ptr get_logger();
  static hlogger_ptr get_logger(const std::string& logger_name);
  static hlogger_ptr get_logger(const std::string& project_name, const std::string& module_name);
  static bool register_logger(config_ptr&& config);

 private:

};
} // namespace hare
