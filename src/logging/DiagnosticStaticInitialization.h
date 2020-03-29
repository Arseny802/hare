//
// Created by arseny on 29/03/2020.
//

#ifndef HARE_SRC_LOGGING_DIAGNOSTICSTATICINITIALIZATION_H_
#define HARE_SRC_LOGGING_DIAGNOSTICSTATICINITIALIZATION_H_

#include "Diagnostics.h"
#include "hare.h"
namespace hare::logging {
class DiagnosticStaticInitialization {
 public:
  DiagnosticStaticInitialization() {
    Diagnostics::Initialize();
  }
  ~DiagnosticStaticInitialization() = default;
};
}
#endif //HARE_SRC_LOGGING_DIAGNOSTICSTATICINITIALIZATION_H_
