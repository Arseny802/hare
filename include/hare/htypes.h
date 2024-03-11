#pragma once

#include <cstdint>
namespace hare {

using htypes_mask_t = uint16_t;

enum htypes_mask : htypes_mask_t {
  none = 0,
  console = 1,
  file_daily = 2,
  //file_weekly = 4,
  //file_monthly = 8,
  //file_yearly = 16,
  file_rotating = 32,
  //syslog_eventlog = 64,
  //network_tcp = 128,
  //network_udp = 256,
  //android = 512,
  //db_mongo = 1024,
};

struct htypes_mask_default {
  static constexpr htypes_mask_t console_daily = htypes_mask::console | htypes_mask::file_daily;
  //static constexpr htypes_mask_t console_monthly = htypes_mask::console | htypes_mask::file_monthly;
  static constexpr htypes_mask_t console_rotating = htypes_mask::console | htypes_mask::file_rotating;
  //static constexpr htypes_mask_t rotating_syslog_eventlog = htypes_mask::file_rotating | htypes_mask::syslog_eventlog;
  //static constexpr htypes_mask_t rotating_tcp = htypes_mask::file_rotating | htypes_mask::network_tcp;
  //static constexpr htypes_mask_t rotating_udp = htypes_mask::file_rotating | htypes_mask::network_udp;
  //static constexpr htypes_mask_t rotating_android = htypes_mask::file_rotating | htypes_mask::android;
};
} // namespace hare
