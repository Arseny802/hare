#pragma once

#include "config.h"

namespace hare {
struct DefaultConfig : public Config {
  DefaultConfig() = default;

 private:
#ifdef PROJECT_NAME
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view default_project_name_ = PROJECT_NAME;
#else
  /// Logger name (e.g. 'http_module' or 'ftp_module')
  static constexpr std::string_view default_project_name_ =  "hare";
#endif
  static const std::string kProjectName;
  /// Logger name, shown in log message
  static const std::string kLoggerName;
  /// File name log to.
  static const std::string kLogFileName;
};
using DefaultConfigPtr = std::unique_ptr<DefaultConfig>;
}
