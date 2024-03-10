#pragma once
#include <string>

namespace hare {
struct config_defaults_spdlog {
  std::string log_format = "{date} [T%t] {Level} %! %v";
  std::string log_format_named = "{date} [T%t] {Level} [%n] %! %v";
  std::string log_format_date = "[%d/%m/%C %H:%M:%S.%F]";
  std::string log_format_level = "[%^%=4!l%$]";
};
}