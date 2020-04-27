//
// Created by arseny on 24/04/2020.
//

#ifndef HARE_SRC_LOGGING_MEMORYTRACER_H_
#define HARE_SRC_LOGGING_MEMORYTRACER_H_

#include <iostream>
void* operator new(size_t size);
void operator delete(void *pointer, size_t size);

namespace hare {
class MemoryTracer {
 public:
  static void Enable();
  static void Disable();
  static void FixStart();
  static void FixFinish();
  static void AcceptAllocation(size_t size);
  static void AcceptReleasing(size_t size);
  static void LogMemoryUsage();

 private:
  static bool enabled_;
  static thread_local bool tracing_guard_;
  static uint64_t memory_allocated_;
  static uint64_t memory_released_;
};
}

#endif //HARE_SRC_LOGGING_MEMORYTRACER_H_
