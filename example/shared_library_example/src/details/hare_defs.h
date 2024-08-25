#pragma once
#include <hare/hare.hpp>

#define SHARED_LIBRARY_EXAMPLE_PROJECT_NAME "sh_lib_worker"
#define SHARED_LIBRARY_EXAMPLE_MODULE_NAME ""
#define SHARED_LIBRARY_EXAMPLE_LOGGER_NAME SHARED_LIBRARY_EXAMPLE_PROJECT_NAME

#define AUTOLOG_SLE AUTOLOG_IN(SHARED_LIBRARY_EXAMPLE_LOGGER_NAME);
#define AUTOMEASURE_SLE AUTOMEASURE_IN(SHARED_LIBRARY_EXAMPLE_LOGGER_NAME);

namespace shared_library_example {
  inline hare::hlogger_ptr hlog() {
    return hare::get_logger(SHARED_LIBRARY_EXAMPLE_LOGGER_NAME);
  }
} // namespace shared_library_example
