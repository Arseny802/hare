#pragma once
#include <string>

#include "hlogger.h"

namespace hare {
/// Get registered logger object from all existing instances.
/// \param project_name Name of the current project (first string in logger name).
/// \param module_name Name of the current project's module (second string in logger name).
hlogger_ptr get_logger(const std::string& project_name, const std::string& module_name = std::string());
/// Register logger object after creating it with specified config.
/// \param config Logger options.
/// \returns Was registered or not.
bool register_logger(config_ptr&& config);
/// Set some registered logger as default instance.
/// \param default_logger_name It's name (shuld be known in map).
/// \returns Was registered or not.
bool set_default_logger(const std::string& default_logger_name);
} // namespace hare
