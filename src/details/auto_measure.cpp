#include "pch.h"

#include <fmt/format.h>

#include "../logger_fabric.h"
#include "hare/details/auto_measure.h"
#include "hare/hlogger.h"

namespace hare::details {
namespace {
inline std::string get_local_file_name(std::string_view file_name) {
  return std::string(file_name.substr(file_name.find_last_of('/') + 1, file_name.size()));
}
}  // namespace

auto_measure::auto_measure(std::string_view file_name, std::string_view function_signature,
                           const std::string& logger_name, std::string_view obj_name) noexcept
    : logger_(logger_fabric::get_logger(logger_name)),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature),
      obj_name_(obj_name) {
  on_initialized();
}

auto_measure::~auto_measure() {
  on_deinitialized();
}

inline void auto_measure::on_initialized() noexcept {
  if (std::uncaught_exceptions() > 0) {
    logger_->trace("Function {} mesure startered{} with {} uncaught exceptions in file {}.",
                   function_signature_.c_str(),
                   (obj_name_.empty() ? "" : " for " + obj_name_),
                   std::uncaught_exceptions(),
                   file_name_.c_str());
  } else {
    logger_->trace("Function {} mesure startered{} in file {}.",
                   function_signature_,
                   (obj_name_.empty() ? "" : " for " + obj_name_),
                   file_name_);
  }
  started_ = {std::chrono::steady_clock::now()};
}

inline void auto_measure::on_deinitialized() const noexcept {
  const auto end = std::chrono::steady_clock::now();

  std::string elapsed_output;
  if constexpr (enable_measure_pretty_format) {
    const auto elapsed_nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - started_).count();
    if (elapsed_nanoseconds / 1000000 > 1) {
      const auto elapsed_milliseconds =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - started_).count();
      if (elapsed_milliseconds / 10000 > 1) {
        const auto elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(end - started_).count();
        elapsed_output =
            fmt::format("{} seconds ({} milliseconds)", elapsed_seconds, elapsed_milliseconds);
      } else {
        const auto elapsed_microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(end - started_).count();
        elapsed_output = fmt::format("{} milliseconds ({} microseconds)",
                                     elapsed_milliseconds,
                                     elapsed_microseconds);
      }
    } else {
      elapsed_output = fmt::format("{} nanoseconds", elapsed_nanoseconds);
    }
  } else {
    elapsed_output =
        fmt::format("{} ms",
                    std::chrono::duration_cast<std::chrono::milliseconds>(end - started_).count());
  }

  if (std::uncaught_exceptions() > 0) {
    logger_->trace(
        "Function {} mesure finished{} with {} uncaught exceptions in file {}. Elapsed {}.",
        function_signature_.c_str(),
        (obj_name_.empty() ? "" : " for " + obj_name_),
        std::uncaught_exceptions(),
        file_name_,
        elapsed_output);
  } else {
    logger_->trace("Function {} mesure finished{} in file {}. Elapsed {}.",
                   function_signature_,
                   (obj_name_.empty() ? "" : " for " + obj_name_),
                   file_name_,
                   elapsed_output);
  }
}

}  // namespace hare::details
