#pragma once
#include <cassert>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <utility>

#ifndef HARE_ENABLE_STD_FORMAT
#  define HARE_ENABLE_STD_FORMAT 0
#endif

#if HARE_ENABLE_STD_FORMAT && __has_include(<format>)
#  include <format>
#else
#  include <fmt/format.h>
#endif
