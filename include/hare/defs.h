#pragma once
#include "details/autoinit.h"
#include "details/autolog.h"

// Initialize this macros before including file in project to use AUTO* macros
#ifndef PROJECT_NAME
#  define PROJECT_NAME "hare"
#endif
#ifndef MODULE_NAME
#  define MODULE_NAME ""
#  define LOGGER_NAME PROJECT_NAME
#else
#  ifndef LOGGER_NAME
#    define LOGGER_NAME PROJECT_NAME "." MODULE_NAME
#  endif
#endif

#ifndef HARE_ENABLE_STD_FORMAT
#  define HARE_ENABLE_STD_FORMAT 0
#endif

#ifndef HARE_USE_IMPLEMENTATION_SPDLOG
#  define HARE_USE_IMPLEMENTATION_SPDLOG 1
#endif

/**
 * Automatically flushes log buffer in the end of critical function execution
 * for current logger object.
 */
#define AUTOFLUSH hare::details::auto_flusher unique_local__flusher(LOGGER_NAME);
/**
 * Automatically flushes log buffer in the end of critical function execution
 * for all logger objects.
 */
#define AUTOFLUSH_ALL hare::details::auto_flusher_all unique_local__flusher{};

/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACE hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically logs messages with obj_name based on the file and line number where this macro is
 * used.
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACE4(obj_name) \
  hare::details::auto_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME, #obj_name);
/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACEF hare::details::auto_flusing_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically logs messages based on the file and line number where this macro is used.
 * This can be used to distinguish between different modules or components that are logging at the
 * same level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOTRACEFA hare::details::auto_flusing_all_tracer unique_local__tracer(__FILE__, __FUNCTION__, LOGGER_NAME);

/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASURE hare::details::auto_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically mesuress with obj_name how long a block of code takes.
 * Automatically logs messages with a given logger name and obj_name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASURE4(obj_name) \
  hare::details::auto_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME, #obj_name);
/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASUREF hare::details::auto_flusing_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME);
/**
 * Automatically mesuress how long a block of code takes.
 * Automatically logs messages with a given logger name. This can be used to
 * distinguish between different modules or components that are logging at the same
 * level (e.g., both "app" and "network" modules may be warning about something).
 */
#define AUTOMEASUREFA \
  hare::details::auto_flusing_all_measure unique_local__measure(__FILE__, __FUNCTION__, LOGGER_NAME);

namespace hare {
class hlogger;
} // namespace hare

/**
 * Generates a getter for a logger with the given function name.
 * Makes a lazy initilization of logger object.
 */
#define MAKE_GETTER(name)                                             \
  inline std::shared_ptr<hare::hlogger> name() {                      \
    static hare::details::autoinit initer(PROJECT_NAME, MODULE_NAME); \
    return initer.get_logger();                                       \
  }
