#pragma once

namespace hare {
template<typename T>
void trace(const std::string_view log_format_message, const T &args...) noexcept {
  trace(fmt::format(log_format_message, args));
  //spdlog::Trace(log_format_message, args);
}

template<typename T>
void debug(const std::string_view log_format_message, const T &args...) noexcept {
  //Debug(fmt::format(log_format_message, args));
  spdlog::debug(log_format_message, args);
}

template<typename T>
void info(const std::string_view log_format_message, const T &args...) noexcept {
  info(fmt::format(log_format_message, args));
}

template<typename T>
void warn(const std::string_view log_format_message, const T &args...) noexcept {
  warn(fmt::format(log_format_message, args));
}

template<typename T>
void warning(const std::string_view log_format_message, const T &args...) noexcept {
  warn(fmt::format(log_format_message, args));
}

template<typename T>
void error(const std::string_view log_format_message, const T &args...) noexcept {
  error(fmt::format(log_format_message, args));
}

template<typename T>
void critical(const std::string_view log_format_message, const T &args...) noexcept {
  critical(fmt::format(log_format_message, args));
}

template<typename T>
void fatal(const std::string_view log_format_message, const T &args...) noexcept {
  critical(fmt::format(log_format_message, args));
}
}