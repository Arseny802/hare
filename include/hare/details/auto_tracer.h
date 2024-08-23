#pragma once
#include "hare/hlogger.h"
#include <chrono>
#include <string>
#include <string_view>

namespace hare::details {
  class auto_tracer {
public:
    explicit auto_tracer(const std::string& logger_name,
                         std::string_view file_name,
                         std::string_view function_signature);
    explicit auto_tracer(std::string_view file_name, std::string_view function_signature);
    ~auto_tracer();

private:
    inline void on_initialized() noexcept;
    inline void on_deinitialized() const noexcept;

    const hlogger_ptr logger_;

    const std::string file_name_;
    const std::string function_signature_;
  };

  class auto_measure {
public:
    explicit auto_measure(const std::string& logger_name,
                          std::string_view file_name,
                          std::string_view function_signature);
    explicit auto_measure(std::string_view file_name, std::string_view function_signature);
    ~auto_measure();

private:
    inline void on_initialized() noexcept;
    inline void on_deinitialized() const noexcept;

    const hlogger_ptr logger_;

    const std::string file_name_;
    const std::string function_signature_;
    std::chrono::time_point<std::chrono::steady_clock> started_;
  };
} // namespace hare::details
