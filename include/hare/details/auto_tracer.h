#pragma once
#include <string>
#include <string_view>

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
class auto_tracer final {
 public:
  /**
   * @brief Constructor that initializes the logger with a specified name, file name,
   *         and function signature.
   *
   * @param logger_name The name of the logger.
   * @param file_name The name of the file.
   * @param function_signature The function signature.
   */
  explicit auto_tracer(std::string_view file_name,
                       std::string_view function_signature,
                       const std::string& logger_name = "",
                       std::string_view obj_name = "") noexcept;

  /**
   * @brief Destructor that deinitializes the logger.
   */
  ~auto_tracer();

 protected:
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
  const std::shared_ptr<hlogger> logger_;
  const std::string file_name_;
  const std::string function_signature_;
  const std::string obj_name_;
};

} // namespace hare::details
