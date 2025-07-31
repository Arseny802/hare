#include "pch.h"

#include <fmt/format.h>

#include "../logger_fabric.h"
#include "hare/details/auto_tracer.h"
#include "hare/hlogger.h"

namespace hare::details {
namespace {
inline std::string get_local_file_name(std::string_view file_name) {
  return std::string(file_name.substr(file_name.find_last_of('/') + 1, file_name.size()));
}
}  // namespace

auto_tracer::auto_tracer(std::string_view file_name, std::string_view function_signature,
                         const std::string& logger_name, std::string_view obj_name) noexcept
    : logger_(logger_fabric::get_logger(logger_name)),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature),
      obj_name_(obj_name) {
  on_initialized();
}

auto_tracer::~auto_tracer() {
  on_deinitialized();
}

inline void auto_tracer::on_initialized() noexcept {
  const auto uncaught_exceptions = std::uncaught_exceptions();
  if (uncaught_exceptions > 0) {
    logger_->trace("Function {} entered{} with {} uncaught exceptions in file {}.",
                   function_signature_.c_str(),
                   (obj_name_.empty() ? "" : " on " + obj_name_),
                   uncaught_exceptions,
                   file_name_.c_str());
  } else {
    logger_->trace("Function {} entered{} in file {}.",
                   function_signature_,
                   (obj_name_.empty() ? "" : " on " + obj_name_),
                   file_name_);
  }
}

inline void auto_tracer::on_deinitialized() const noexcept {
  const auto uncaught_exceptions = std::uncaught_exceptions();
  if (uncaught_exceptions > 0) {
    logger_->trace("Function {} left{} with {} uncaught exceptions in file {}.",
                   function_signature_.c_str(),
                   (obj_name_.empty() ? "" : " on " + obj_name_),
                   uncaught_exceptions,
                   file_name_);
  } else {
    logger_->trace("Function {} left{} in file {}.",
                   function_signature_,
                   (obj_name_.empty() ? "" : " on " + obj_name_),
                   file_name_);
  }
}

}  // namespace hare::details
