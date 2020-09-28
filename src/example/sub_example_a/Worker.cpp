//
// Created by arseny on 28/03/2020.
//

#include <src/logging/hare/hare.h>
#include "Worker.h"

namespace sub_example_a {

const int Worker::kBytesToReserve = 128;

Worker::Worker() {
  AUTOLOG
  hare::debug("Allocating {} bytes of memory...", kBytesToReserve);
  some_data_ = new uint8_t[kBytesToReserve];
  for (int index = 0; index < kBytesToReserve; ++index) {
    some_data_[index] = (index * index / 2);
  }
  hare::trace("Allocating {} bytes of memory OK.", kBytesToReserve);
}

Worker::~Worker() {
  hare::debug("Worker::~Worker() called. Deleting some_data_");
  delete some_data_;
}

void Worker::SomeSetter(const std::string_view value) noexcept {
  hare::trace("Worker::SomeSetter() called. Value is '{}'.", value);
  some_string_ = value.data();
}

std::string Worker::SomeGetter() const noexcept {
  hare::trace("Worker::SomeSetter() called. Value is '{}'.", some_string_);
  return some_string_;
}

//template <class T>
bool Worker::VectorHasRepetitions(const std::vector<int> &data) const noexcept {
  AUTOLOG
  for (int element : data) {
    hare::trace("Got element '{}' in data.", element);
  }
  return false;
}

}