#pragma once

#include "logger.h"
namespace hare {
//static logging::StaticInitialization diagnostic_static_initialization;
static Logger static_logger;
///
/// \param log_message
void trace(std::string_view log_message) noexcept;
///
/// \param log_message
void debug(std::string_view log_message) noexcept;
///
/// \param log_message
void info(std::string_view log_message) noexcept;
///
/// \param log_message
void warn(std::string_view log_message) noexcept;
///
/// \param log_message
void warning(std::string_view log_message) noexcept;
///
/// \param log_message
void error(std::string_view log_message) noexcept;
///
/// \param log_message
void critical(std::string_view log_message) noexcept;
///
/// \param log_message
void fatal(std::string_view log_message) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void trace(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void debug(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void info(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void warn(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void warning(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void error(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void critical(std::string_view log_format_message, const T& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void fatal(std::string_view log_format_message, const T& args...) noexcept;
}

#include "hare.hpp"
#include "../autolog/AutoTracer.h"

#endif //HARE_SRC_LOGGING_HARE_H_
