#pragma once
#include "auto_flusher.h"
#include "auto_measure.h"
#include "auto_tracer.h"

namespace hare::details {

template <class WriterT, class Finalizer>
class autolog final {
 public:
  autolog(std::string_view file_name, std::string_view function_signature,
          const std::string& logger_name = "", std::string_view obj_name = "") noexcept;
  ~autolog();

 private:
  const Finalizer flusher_;
  const WriterT tracer_;
};

using auto_flusing_tracer = autolog<auto_tracer, auto_flusher>;
using auto_flusing_measure = autolog<auto_measure, auto_flusher>;
using auto_flusing_all_tracer = autolog<auto_tracer, auto_flusher_all>;
using auto_flusing_all_measure = autolog<auto_measure, auto_flusher_all>;

}  // namespace hare::details