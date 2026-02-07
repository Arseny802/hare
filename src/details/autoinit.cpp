
#include "pch.h"
#include "hare/details/autoinit.h"
#include "../logger_fabric.h"
#include <hare/hlogger.h>

namespace hare::details {

autoinit::autoinit(const char project[], const char module[]) noexcept:
    name_(hare::config::initialize_logger(project, module, nullptr, false)) { }
autoinit::~autoinit() = default;

hlogger_ptr autoinit::get_logger() const {
  return hare::logger_fabric::get_logger(name_);
}

} // namespace hare::details
