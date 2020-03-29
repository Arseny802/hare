//
// Created by arseny on 28/03/2020.
//

#ifndef HARE_SRC_LOGGING_HARE_H_
#define HARE_SRC_LOGGING_HARE_H_

#include "Diagnostics.h"
#include "DiagnosticStaticInitialization.h"

namespace hare {
///
/// \param log_message
void trace(const std::string_view log_message) noexcept;
///
/// \param log_message
void debug(const std::string_view log_message) noexcept;
///
/// \param log_message
void info(const std::string_view log_message) noexcept;
///
/// \param log_message
void warn(const std::string_view log_message) noexcept;
///
/// \param log_message
void warning(const std::string_view log_message) noexcept;
///
/// \param log_message
void error(const std::string_view log_message) noexcept;
///
/// \param log_message
void critical(const std::string_view log_message) noexcept;
///
/// \param log_message
void fatal(const std::string_view log_message) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void trace(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void debug(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void info(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void warn(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void warning(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void error(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void critical(const std::string_view log_format_message, T&& args...) noexcept;
///
/// \tparam T
/// \param log_format_message
/// \param args
/// \param ...
template <typename T>
void fatal(const std::string_view log_format_message, T&& args...) noexcept;
}

#include "hare_templates.cc"

#endif //HARE_SRC_LOGGING_HARE_H_
