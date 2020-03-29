//
// Created by arseny on 29/03/2020.
//

namespace hare {
template<typename T>
void trace(const std::string_view log_format_message, T &&args...) noexcept {
  trace(fmt::format(log_format_message, args));
}

template<typename T>
void debug(const std::string_view log_format_message, T &&args...) noexcept {
  debug(fmt::format(log_format_message, args));
}

template<typename T>
void info(const std::string_view log_format_message, T &&args...) noexcept {
  info(fmt::format(log_format_message, args));
}

template<typename T>
void warn(const std::string_view log_format_message, T &&args...) noexcept {
  warn(fmt::format(log_format_message, args));
}

template<typename T>
void warning(const std::string_view log_format_message, T &&args...) noexcept {
  warn(fmt::format(log_format_message, args));
}

template<typename T>
void error(const std::string_view log_format_message, T &&args...) noexcept {
  error(fmt::format(log_format_message, args));
}

template<typename T>
void critical(const std::string_view log_format_message, T &&args...) noexcept {
  critical(fmt::format(log_format_message, args));
}

template<typename T>
void fatal(const std::string_view log_format_message, T &&args...) noexcept {
  critical(fmt::format(log_format_message, args));
}
}