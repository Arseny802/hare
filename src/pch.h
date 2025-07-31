#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <utility>

#if __has_include(<format>)
#include <format>
#else
#include <fmt/format.h>
#endif
