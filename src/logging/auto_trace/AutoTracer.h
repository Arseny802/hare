//
// Created by arseny on 25/04/2020.
//

#ifndef HARE_SRC_LOGGING_AUTOTRACER_H_
#define HARE_SRC_LOGGING_AUTOTRACER_H_

#include <string_view>
#include <string>
#include "../initialization/Diagnostics.h"
#include "../DiagnosticLevels.h"

namespace hare {
class AutoTracer {
 public:
  explicit AutoTracer(std::string_view file_name, std::string_view function_signature);
  ~AutoTracer();
 private:
  static std::string GetLocalFileName(std::string_view file_name);
  const std::string file_name_;
  const std::string function_signature_;
};
}
#define AUTOLOG hare::AutoTracer unique_local__tracer(__BASE_FILE__, __PRETTY_FUNCTION__);

#endif //HARE_SRC_LOGGING_AUTOTRACER_H_
