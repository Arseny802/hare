//
// Created by arseny on 24/04/2020.
//

#include "MemoryTracer.h"
#include "../logging/hare.h"

void *operator new(size_t size) {
  hare::MemoryTracer::AcceptAllocation(size);
  return malloc(size);
}
void operator delete(void *pointer, size_t size) {
  hare::MemoryTracer::AcceptReleasing(size);
  free(pointer);
}

namespace hare {
bool MemoryTracer::enabled_ = false;
uint64_t MemoryTracer::memory_allocated_ = 0;
uint64_t MemoryTracer::memory_released_ = 0;

void MemoryTracer::AcceptAllocation(size_t size) {
  memory_allocated_ += size;
  if (!enabled_) {
	return;
  }
  static thread_local bool tracing_guard = false;
  static thread_local std::mutex tracing_mutex{};
  if (tracing_guard) {
	return;
  }
  std::lock_guard<std::mutex> lk(tracing_mutex);
  tracing_guard = true;
  hare::trace(fmt::format("Allocated {} bytes. Total allocated: {} bytes.",
                          size, memory_allocated_));
  LogMemoryUsage();
  tracing_guard = false;
}

void MemoryTracer::AcceptReleasing(size_t size) {
  memory_released_ += size;
  if (!enabled_) {
	return;
  }
  static thread_local bool tracing_guard = false;
  static thread_local std::mutex tracing_mutex{};
  if (tracing_guard) {
	return;
  }
  std::lock_guard<std::mutex> lk(tracing_mutex);
  tracing_guard = true;
  hare::trace(fmt::format("Released {} bytes. Total released: {} bytes.",
                          size, memory_released_));
  LogMemoryUsage();
  tracing_guard = false;
}

void MemoryTracer::LogMemoryUsage() {
  hare::trace("Using {} bytes of heap.",
              memory_allocated_ - memory_released_);
}

void MemoryTracer::FixStart() {
  AUTOLOG
  memory_allocated_ = 0;
  memory_released_ = 0;
}

void MemoryTracer::FixFinish() {
  AUTOLOG
  hare::trace(fmt::format("Released {} allocated. Total released: {} bytes. Difference: {} bytes.",
                          memory_allocated_, memory_released_, memory_allocated_ - memory_released_));
}

void MemoryTracer::Enable() {
  AUTOLOG
  enabled_ = true;
}

void MemoryTracer::Disable() {
  AUTOLOG
  enabled_ = false;
}

}
