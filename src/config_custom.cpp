#pragma once
#include "hare/config_custom.h"

namespace hare {

config_custom::config_custom() = default;
config_custom::~config_custom() = default;

void config_custom::set_log_format(std::string new_log_format) {
  log_format_ = std::move(new_log_format);
}
void config_custom::set_log_format_date(std::string new_log_format_date) {
  log_format_date_ = std::move(new_log_format_date);
}
void config_custom::set_log_format_level(std::string new_log_format_level) {
  log_format_level_ = std::move(new_log_format_level);
}
void config_custom::set_truncate_file_at_start(bool truncate_file_at_start) {
  truncate_file_at_start_ = truncate_file_at_start;
}
} // namespace hare
