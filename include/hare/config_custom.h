#pragma once
#include "hare/details/config_default.h"

namespace hare {

struct config_custom : config_default {
  config_custom();
  ~config_custom() override;

  void set_log_format(std::string new_log_format);
  void set_log_format_date(std::string new_log_format_date);
  void set_log_format_level(std::string new_log_format_level);
  void set_sinks_info(sinks_info new_sinks_info);
};

} // namespace hare
