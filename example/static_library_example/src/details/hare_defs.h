#pragma once
#ifndef PROJECT_NAME
#  define PROJECT_NAME "hare_example"
#endif
#ifndef MODULE_NAME
#  define MODULE_NAME "st_lib_worker"
#endif
#include <hare/hare.hpp>

namespace static_library_example {
// Default logger object getter, no config provided.
MAKE_GETTER(hlog)
} // namespace static_library_example
