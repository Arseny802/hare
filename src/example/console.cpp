//
// Created by arseny on 28/03/2020.
//

#include <src/logging/hare.h>
#include "sub_example_so/Worker.h"
#include "sub_example_a/Worker.h"

int UseSumExampleStatic() {
  AUTOLOG
  sub_example_a::Worker worker;
  hare::info("Called worker.SomeGetter(), result is '{}'.", worker.SomeGetter());
  hare::info("Called worker.SomeSetter(), with value \"example new value\".");
  worker.SomeSetter("example new value");
  hare::info("Called worker.SomeGetter(), result is '{}'.", worker.SomeGetter());

  std::vector<int> data{
	  1, 2, 3, 3, 4, 5, 6, 7, 8
  };
  if (worker.VectorHasRepetitions(data)) {
	hare::debug("worker.VectorHasRepetitions(data) returned true.");
  } else {
	hare::warn("worker.VectorHasRepetitions(data) returned false.");
  }
  return 0;
}

void SomeExceptionVoid(bool throw_exception = true) {
  AUTOLOG
  if (throw_exception) {
    throw std::runtime_error("Expected exception.");
  }
}

void SomeExceptionVoidWrapper() {
  AUTOLOG
  SomeExceptionVoid(true);
}

int UseSumExampleShred() {
  AUTOLOG
  sub_example_so::Worker worker;
  hare::info("Called worker.SomeGetter(), result is '{}'.", worker.SomeGetter());
  hare::info("Called worker.SomeSetter(), with value \"example new value\".");
  worker.SomeSetter("example new value");
  hare::info("Called worker.SomeGetter(), result is '{}'.", worker.SomeGetter());

  try {
    SomeExceptionVoidWrapper();
  } catch (std::runtime_error& exception) {
    hare::info("Got runtime_error: {}", exception.what());
  }

  std::vector<int> data{
	  1, 2, 3, 3, 4, 5, 6, 7, 8
  };
  if (worker.VectorHasRepetitions(data)) {
	hare::debug("worker.VectorHasRepetitions(data) returned true.");
  } else {
	hare::warn("worker.VectorHasRepetitions(data) returned false.");
  }
  return 0;
}

int main() {
  AUTOLOG
  hare::MemoryTracer::FixStart();
  int return_result = 0;

  hare::debug("Executing submodule function from shared library...");
  if (!UseSumExampleShred()) {
	hare::critical("UseSumExampleShred() return non-zero result.");
	return_result = 1;
  }

  hare::debug("Executing submodule function from static library...");
  if (!UseSumExampleStatic()) {
	hare::critical("UseSumExampleStatic() return non-zero result.");
	return_result = 2;
  }

  hare::debug("Executing submodule function finished.");
  if (return_result) {
	hare::fatal("Program result code is not zero!");
  }

  hare::trace("Returning 0, it's OK.");
  hare::MemoryTracer::FixFinish();
  return return_result;
}
