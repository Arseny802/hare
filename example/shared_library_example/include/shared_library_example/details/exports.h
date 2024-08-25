#pragma once
#ifndef _WIN32
#  define HARE_EXAMPLE_SUB_API
#else
#  ifdef HARE_EXAMPLE_SUB_SHARED_EXPORTS
#    define HARE_EXAMPLE_SUB_API __declspec(dllexport)
#  else
#    define HARE_EXAMPLE_SUB_API __declspec(dllimport)
#  endif
#endif