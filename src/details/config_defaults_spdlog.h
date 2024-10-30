#pragma once
#include "config_defaults_base.h"

#if __has_include(<format>)
#  include <format>
#else
#  include <fmt/format.h>
#endif

namespace hare {
  struct config_defaults_spdlog: config_defaults_base {
    std::string log_format =
#ifdef __cpp_lib_format
        std::format
#else
        fmt::format
#endif
        ("\{{0}\} [T%t] \{{1}\} %! %v", log_format_argument_date.c_str(), log_format_argument_level.c_str());

    std::string log_format_named =
#ifdef __cpp_lib_format
        std::format
#else
        fmt::format
#endif
        ("\{{0}\} [T%t] \{{1}\} [%n] %! %v", log_format_argument_date.c_str(), log_format_argument_level.c_str());
    std::string log_format_date = "[%d/%m/%C %H:%M:%S.%F]";
    std::string log_format_level = "[%^%=4!l%$]";
  };
} // namespace hare
