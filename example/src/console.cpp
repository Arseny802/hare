#include <hare/hare.hpp>
#include "static_library_example/worker.h"
#include "shared_library_example/worker.h"
#include "details/hare_defs.h"

#include <vector>

int use_sum_example_shared() {
  AUTOMEASURE_HE
  shared_library_example::worker worker;
  hare::info("Called worker.some_getter(), result is '{}'.", worker.some_getter());
  hare::info("Called worker.some_setter(), with value \"example new value\".");
  worker.some_setter("example new value");
  hare::info("Called worker.some_getter(), result is '{}'.", worker.some_getter());

  std::vector<int> data{
	  1, 2, 3, 3, 4, 5, 6, 7, 8
  };
  if (shared_library_example::worker::vector_has_repetitions(data)) {
	hare::debug("worker.vector_has_repetitions(data) returned true.");
  } else {
	hare::warn("worker.vector_has_repetitions(data) returned false.");
  }
  return 0;
}

int use_sum_example_static() {
  AUTOMEASURE_HE
  static_library_example::worker worker;
  hare::info("Called worker.some_getter(), result is '{}'.", worker.some_getter());
  hare::info("Called worker.some_setter(), with value \"example new value\".");
  worker.some_setter("example new value");
  hare::info("Called worker.some_getter(), result is '{}'.", worker.some_getter());

  std::vector<int> data{
      1, 2, 3, 3, 4, 5, 6, 7, 8
  };
  if (static_library_example::worker::vector_has_repetitions(data)) {
    hare::debug("worker.vector_has_repetitions(data) returned true.");
  } else {
    hare::warn("worker.vector_has_repetitions(data) returned false.");
  }
  return 0;
}

void some_exception_void(bool throw_exception = true) {
  AUTOLOG
  if (throw_exception) {
    throw std::runtime_error("Expected exception.");
  }
}

void some_exception_void_wrapper() {
  AUTOLOG
  some_exception_void(true);
}

int main() {
  AUTOLOG_HE
  int return_result = 0;

  try {
    some_exception_void_wrapper();
  } catch (std::runtime_error& exception) {
    hlog()->info("Got runtime_error: {}", exception.what());
  }

  hlog()->debug("Executing submodule function from static library...");
  if (!use_sum_example_static()) {
    hlog()->critical("use_sum_example_static() return non-zero result.");
	return_result = 1;
  }

  hlog()->debug("Executing submodule function from shared library...");
  if (!use_sum_example_shared()) {
    hlog()->critical("use_sum_example_shared() return non-zero result.");
	return_result = 2;
  }

  hlog()->debug("Executing submodule function finished.");
  if (return_result) {
    hlog()->fatal("Program result code is not zero!");
  }

  hlog()->trace("Returning 0, it's OK.");
  return return_result;
}
