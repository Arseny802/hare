//#define HARE_EXAMPLE_SUB_SHARED_EXPORTS
#include <hare/hare.hpp>
#include "shared_library_example/worker.h"
#include "details/hare_defs.h"

namespace shared_library_example {

const int worker::k_bytes_to_reserve_ = 128;

worker::worker() {
  AUTOLOG_IN("sh_lib_worker");
  hare::debug("Allocating {} bytes of memory...", k_bytes_to_reserve_);
  some_data_ = new uint8_t[k_bytes_to_reserve_];
  for (int index = 0; index < k_bytes_to_reserve_; ++index) {
    some_data_[index] = (index * index / 2);
  }
  hare::trace("Allocating {} bytes of memory OK.", k_bytes_to_reserve_);
}

worker::~worker() {
  hare::debug("worker::worker() called. Deleting some_data_");
  delete some_data_;
}

void worker::some_setter(const std::string_view value) noexcept {
  hare::trace("worker::some_setter() called. Value is '{}'.", value);
  some_string_ = value.data();
}

std::string worker::some_getter() const noexcept {
  hare::trace("worker::some_getter() called. Value is '{}'.", some_string_);
  return some_string_;
}

bool worker::vector_has_repetitions(const std::vector<int> &data) noexcept {
  AUTOLOG_SLE
  for (int element : data) {
    hlog()->trace("Got element '{}' in data.", element);
  }
  return false;
}

} // namespace shared_library_example
