#pragma once
#include <string>
#include <cstdint>

namespace hare {
struct sinks_info {
  struct fs_t {
    uint16_t max_files;
    std::size_t max_size;
    int rotation_hour;
    int rotation_minute;
    bool truncate;
  } fs{};

  struct tcp_t {
    std::string host;
    uint16_t port;
  } tcp{};

  struct upd_t {
    std::string host;
    uint16_t port;
  } upd{};
};
} // namespace hare
