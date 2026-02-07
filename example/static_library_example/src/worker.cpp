#include "static_library_example/worker.h"
#include "details/hare_defs.h"

namespace static_library_example {

const int worker::k_bytes_to_reserve = 1024;

worker::worker() {
  AUTOTRACE;
  hlog()->debug("Allocating {} bytes of memory...", k_bytes_to_reserve);
  some_data_ = new uint8_t[k_bytes_to_reserve];
  for (int index = 0; index < k_bytes_to_reserve; ++index) {
    some_data_[index] = uint8_t(index * index / 2);
  }
  hlog()->trace("Allocating {} bytes of memory OK.", k_bytes_to_reserve);
}

worker::~worker() {
  AUTOTRACEFA
  delete some_data_;
}

void worker::some_setter(const std::string_view value) noexcept {
  hlog()->trace("worker::some_setter() called. Value is '{}'.", value);
  some_string_ = value.data();
}

std::string worker::some_getter() const noexcept {
  hlog()->trace("worker::some_setter() called. Value is '{}'.", some_string_);
  return some_string_;
}

bool worker::vector_has_repetitions(const std::vector<int>& data) noexcept {
  AUTOMEASURE
  for (const int& element: data) {
    hare::trace("Got element '{}' in data.", element);
  }
  return false;
}
} // namespace static_library_example
