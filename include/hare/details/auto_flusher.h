#pragma once
#include <string>

namespace hare {
class hlogger;
} // namespace hare

namespace hare::details {
/**
 * @brief A class that automatically adds tracing information to log messages.
 *
 * This class is used to simplify logging in hare. It takes the file name and
 * function signature of the calling code, and uses them to populate the log
 * message with relevant context.
 */
class auto_flusher final {
 public:
  /**
   * @brief Constructor that initializes the logger with a specified name, file name,
   *         and function signature.
   *
   * @param logger_name The name of the logger.
   */
  explicit auto_flusher(const std::string& logger_name = "") noexcept;

  /**
   * @brief Destructor that deinitializes the logger.
   */
  ~auto_flusher();

 private:
  // Members
  const std::shared_ptr<hlogger> logger_;
};

/**
 * @brief A class that automatically adds tracing information to log messages.
 *
 * This class is used to simplify logging in hare. It takes the file name and
 * function signature of the calling code, and uses them to populate the log
 * message with relevant context.
 */
class auto_flusher_all final {
 public:
  /**
   * @brief Constructor that initializes the logger with a specified name, file name,
   *         and function signature.
   */
  auto_flusher_all() noexcept;

  /**
   * @brief Destructor that deinitializes the logger.
   */
  ~auto_flusher_all();
};

} // namespace hare::details
