#pragma once
#ifdef HARE_EXAMPLE_SUB_SHARED_EXPORTS
#define HARE_EXAMPLE_SUB_API __declspec(dllexport)
#else
#define HARE_EXAMPLE_SUB_API __declspec(dllimport)
#endif