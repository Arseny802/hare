#pragma once
#include <memory>
#include <string>

namespace hare {
class hlogger;
} // namespace hare

namespace hare::details {
/*
 * @brief Auto initialization of spdlog
 */
struct autoinit final {
  /*
   * @brief Constructor that initializes the logger with default config
   */
  autoinit(const char project[], const char module[]) noexcept;
  ~autoinit();

  /*
   * Get logger object by name remembered in constructor
   */
  [[nodiscard]] std::shared_ptr<hlogger> get_logger() const;

 private:
  const std::string name_;
};
} // namespace hare::details
