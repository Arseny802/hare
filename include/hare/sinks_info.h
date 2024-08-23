#pragma once
#include <cstdint>
#include <string>

namespace hare {
  /// @brief A sinks information.
  struct sinks_info {
    bool synchronize{}; // Whether sink data should be synchronized with other nodes in the network

    struct fs_t {                   // Filesystem settings
      uint16_t max_files_by_date{}; // Maximum number of files per date to store
      uint16_t max_files_by_size{}; // Maximum number of files by size to store
      std::size_t max_size{};       // Maximum file size to store
      int rotation_hour{};          // Hourly backup frequency (0-23)
      int rotation_minute{};        // Minute-based backup frequency (0-59)
      bool truncate{};              // Whether to truncate files to fit within storage limits
    } fs;

    struct tcp_t {        // TCP settings
      std::string host{}; // Hostname or IP address of the TCP server
      uint16_t port{};    // Port number for TCP connections
    } tcp;

    struct upd_t {        // UDP settings
      std::string host{}; // Hostname or IP address of the UDP server
      uint16_t port{};    // Port number for UDP connections
    } upd;
  };
} // namespace hare
