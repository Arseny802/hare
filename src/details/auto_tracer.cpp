#include "pch.h"
#include "hare/details/auto_tracer.h"
#include "hare/hlogger.h"

#include "../logger_fabric.h"

namespace hare::details {

namespace {
std::string get_local_file_name(std::string_view file_name)
{
  return std::string(file_name.substr(file_name.find_last_of('/') + 1, file_name.size()));
}
}

auto_tracer::auto_tracer(
    const std::string &logger_name,
    std::string_view file_name,
    std::string_view function_signature)
    : logger_(logger_fabric::get_logger(logger_name)),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature) {
  on_initialized();
}

auto_tracer::auto_tracer(
    std::string_view file_name,
    std::string_view function_signature)
    : logger_(logger_fabric::get_logger()),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature) {
  on_initialized();
}

auto_tracer::~auto_tracer() {
  if (std::uncaught_exceptions() > 0) {
    logger_->debug("Function {} left with {} uncaught exceptions in file {}.",
                   function_signature_.c_str(), std::uncaught_exceptions(), file_name_);
  } else {
    logger_->debug("Function {} left in file {}.", function_signature_, file_name_);
  }
}

inline void auto_tracer::on_initialized() {
  if (std::uncaught_exceptions() > 0) {
    logger_->debug("Function {} entered with {} uncaught exceptions in file {}.",
                                       function_signature_.c_str(), std::uncaught_exceptions(), file_name_.c_str());
  } else {
    logger_->debug("Function {} entered in file {}.", function_signature_, file_name_);
  }
}

auto_measure::auto_measure(
    const std::string &logger_name,
    std::string_view file_name,
    std::string_view function_signature)
    : logger_(logger_fabric::get_logger(logger_name)),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature) {
  on_initialized();
}

auto_measure::auto_measure(
    std::string_view file_name,
    std::string_view function_signature)
    : logger_(logger_fabric::get_logger()),
      file_name_(get_local_file_name(file_name)),
      function_signature_(function_signature) {
  on_initialized();
}

auto_measure::~auto_measure() {
  if (std::uncaught_exceptions() > 0) {
    logger_->debug("Function {} left with {} uncaught exceptions in file {}.",
                   function_signature_.c_str(), std::uncaught_exceptions(), file_name_);
  } else {
    logger_->debug("Function {} left in file {}.", function_signature_, file_name_);
  }
}

inline void auto_measure::on_initialized() {
  if (std::uncaught_exceptions() > 0) {
    logger_->debug("Function {} entered with {} uncaught exceptions in file {}.",
                                       function_signature_.c_str(), std::uncaught_exceptions(), file_name_.c_str());
  } else {
    logger_->debug("Function {} entered in file {}.", function_signature_, file_name_);
  }
}
} /* namespace hare */
