#include "shared_library_example/worker.h"
#include "details/hare_defs.h"

namespace shared_library_example {

const int worker::k_bytes_to_reserve = 128;

worker::worker() {
  AUTOTRACE
  hare::debug("Allocating {} bytes of memory...", k_bytes_to_reserve);
  some_data_ = new uint8_t[k_bytes_to_reserve];
  for (int index = 0; index < k_bytes_to_reserve; ++index) {
    some_data_[index] = (index * index / 2);
  }
  hare::trace("Allocating {} bytes of memory OK.", k_bytes_to_reserve);
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
  hlog()->trace("worker::some_getter() called. Value is '{}'.", some_string_);
  return some_string_;
}

bool worker::vector_has_repetitions(const std::vector<int>& data) noexcept {
  AUTOMEASURE
  for (int element: data) {
    hlog()->trace("Got element '{}' in data.", element);
  }
  return false;
}

} // namespace shared_library_example
