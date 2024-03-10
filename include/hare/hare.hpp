#pragma once
#include "details/auto_tracer.h"
#include <format>

namespace hare {
///
/// \param project_name
/// \param module_name
hlogger_ptr get_logger(const std::string& project_name,
                       const std::string& module_name = std::string());
///
/// \param config
bool register_logger(config_ptr&& config);

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
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void trace(const std::string_view log_format_message, Args&&... args) noexcept {
    trace(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void debug(const std::string_view log_format_message, Args&&... args) noexcept {
    debug(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void info(const std::string_view log_format_message, Args&&... args) noexcept {
    info(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void warn(const std::string_view log_format_message, Args&&... args) noexcept {
    warn(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void warning(const std::string_view log_format_message, Args&&... args) noexcept {
    warn(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void error(const std::string_view log_format_message, Args&&... args) noexcept {
    error(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void critical(const std::string_view log_format_message, Args&&... args) noexcept {
    critical(std::vformat(log_format_message, std::make_format_args(args...)));
}

///
/// \tparam Args
/// \param log_format_message
/// \param args
template<typename... Args>
void fatal(const std::string_view log_format_message, Args&&... args) noexcept {
    fatal(std::vformat(log_format_message, std::make_format_args(args...)));
}

} // namespace hare

#define AUTOLOG hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__);
#define AUTOLOG_IN(logger_name) hare::details::auto_tracer unique_local__tracer(logger_name, __FILE__, __FUNCTION__);

#define AUTOMEASURE hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__);
#define AUTOMEASURE_IN(logger_name) hare::details::auto_tracer unique_local__tracer(logger_name, __FILE__, __FUNCTION__);