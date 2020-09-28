#pragma once

#include "Diagnostics.h"
#include "../hare/hare.h"

namespace hare::logging {
class StaticInitialization {
 public:
  StaticInitialization() {
    if (!IsInitialized()) {
      IsInitialized() = true;
      Diagnostics::Initialize();
    }
  }
  ~StaticInitialization() = default;
  static bool &IsInitialized() {
    static bool initialized = false;
    return initialized;
  }
};
}
