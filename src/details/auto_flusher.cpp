#include "pch.h"

#include "../logger_fabric.h"
#include "hare/details/auto_flusher.h"
#include "hare/hlogger.h"

namespace hare::details {

auto_flusher::auto_flusher(const std::string& logger_name) noexcept
    : logger_(logger_fabric::get_logger(logger_name)) {
}

auto_flusher::~auto_flusher() {
  logger_->flush();
}

auto_flusher_all::auto_flusher_all() noexcept = default;

auto_flusher_all::~auto_flusher_all() {
  logger_fabric::do_for_all([](const hlogger_ptr& logger) { logger->flush(); });
}

}  // namespace hare::details
