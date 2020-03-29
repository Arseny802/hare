//
// Created by arseny on 29/03/2020.
//

#include "hare.h"

namespace hare {

static logging::DiagnosticStaticInitialization diagnostic_static_initialization;

void trace(const std::string_view log_message) noexcept {
  spdlog::trace(log_message);
}

void debug(const std::string_view log_message) noexcept {
  spdlog::debug(log_message);
}

void info(const std::string_view log_message) noexcept {
  spdlog::info(log_message);
}

void warn(const std::string_view log_message) noexcept {
  spdlog::warn(log_message);
}

void warning(const std::string_view log_message) noexcept {
  spdlog::warn(log_message);
}

void error(const std::string_view log_message) noexcept {
  spdlog::error(log_message);
}

void critical(const std::string_view log_message) noexcept {
  spdlog::critical(log_message);
}

void fatal(const std::string_view log_message) noexcept {
  spdlog::critical(log_message);
}
}