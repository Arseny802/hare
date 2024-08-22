#pragma once
#include <cstdint>
#include <string>

namespace hare {
  struct sinks_info {
    bool synchronize{};

    struct fs_t {
      uint16_t max_files_by_date{};
      uint16_t max_files_by_size{};
      std::size_t max_size{};
      int rotation_hour{};
      int rotation_minute{};
      bool truncate{};
    } fs{};

    struct tcp_t {
      std::string host{};
      uint16_t port{};
    } tcp{};

    struct upd_t {
      std::string host{};
      uint16_t port{};
    } upd{};
  };
} // namespace hare
