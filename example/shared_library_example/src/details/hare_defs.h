#pragma once
#ifndef PROJECT_NAME
#  define PROJECT_NAME "sh_lib_worker"
#endif
#ifndef MODULE_NAME
#  define MODULE_NAME ""
#  define LOGGER_NAME PROJECT_NAME
#endif
#include <hare/hare.hpp>

namespace shared_library_example {
// Default logger object getter, no config provided.
MAKE_GETTER(hlog)
} // namespace shared_library_example
