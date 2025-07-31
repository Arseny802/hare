#pragma once
#include <chrono>
#include <string>
#include <string_view>

#include "hare/hlogger.h"

namespace hare::details {
/**
 * @brief A class that automatically measures the execution time of a block of code.
 *
 * This class is used to simplify measuring the execution time of blocks of code in hare. It takes
 * the file name and function signature of the calling code, and uses them to populate the log
 * message with relevant context.
 */
class auto_measure {
 public:
  /**
   * @brief Constructor that initializes the logger with a specified name, file name,
   *         and function signature.
   *
   * @param logger_name The name of the logger.
   * @param file_name The name of the file.
   * @param function_signature The function signature.
   */
  explicit auto_measure(std::string_view file_name, std::string_view function_signature,
                        const std::string& logger_name = "",
                        std::string_view obj_name = "") noexcept;

  /**
   * @brief Destructor that deinitializes the logger.
   */
  ~auto_measure();

  static constexpr bool enable_measure_pretty_format = true;

 private:
  /**
   * @brief Callback to be called when the logger is initialized.
   *
   * This method is used by the logger to notify interested parties of its
   * initialization.
   *
   * @note This method does not throw exceptions.
   */
  inline void on_initialized() noexcept;

  /**
   * @brief Callback to be called when the logger is deinitialized.
   *
   * This method is used by the logger to notify interested parties of its
   * deinitialization.
   *
   * @note This method does not throw exceptions.
   */
  inline void on_deinitialized() const noexcept;

  // Members
  const hare::hlogger_ptr logger_;
  const std::string file_name_;
  const std::string function_signature_;
  const std::string obj_name_;
  std::chrono::time_point<std::chrono::steady_clock> started_;
};

}  // namespace hare::details
