#pragma once
#ifndef PROJECT_NAME
#  define PROJECT_NAME "hare_example"
#endif
#ifndef MODULE_NAME
#  define MODULE_NAME ""
#  define LOGGER_NAME PROJECT_NAME
#endif
#include <hare/hare.hpp>

// Default logger object getter, no config provided.
MAKE_GETTER(hlog)
