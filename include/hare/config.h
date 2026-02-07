#pragma once
#include <memory>
#include <optional>
#include <string>

#include "hare/hlevels.h"
#include "hare/htypes.h"
#include "hare/sinks_info.h"

namespace hare {
/// Configuration settings for a logger.
/**
 * This structure holds configuration settings for a logger. The constructor initializes
 * the logger name and the HTypes mask, as well as sets the default logging level.
 */
struct config {
  using ptr = std::unique_ptr<config>;
  /**
   * Constructor to initialize the logger with a given name, HTypes mask, and logging level.
   *
   * @param logger_name the name of the logger
   * @param htypes_mask the HTypes mask for this logger
   * @param level the default logging level
   */
  explicit config(std::string logger_name, htypes_mask_t htypes_mask, hlevels level);
  /**
   * Destructor.
   *
   * This is a virtual destructor to ensure proper cleanup when the configuration object
   * is deleted through a base class pointer.
   */
  virtual ~config();
  /**
   * This method initializes the logger with the given configuration. If no
   * configuration is provided, it uses the default configuration.
   *
   * @param config The configuration to use for initializing the logger.
   * @return The logger name.
   */
  static std::string initialize_logger(const char project[],
                                       const char module[],
                                       ptr&& config = nullptr,
                                       bool throw_on_error = true);
  /// Returns the logger name.
  /**
   * Retrieves the logger name that was set during initialization.
   *
   * @return The logger name.
   */
  [[nodiscard]] std::string get_logger_name() const;
  /**
   * This method retrieves the project name that was configured alongside
   * the logger settings. The project name provides additional context for logs
   * and can be used to differentiate between logs from different projects or
   * modules within a larger application.
   *
   * @return The project name.
   */
  [[nodiscard]] std::string get_project_name() const;
  /**
   * Retrieves the name of the module that this logger is associated with. This
   * information can be used to filter logs or provide additional context for
   * logging purposes.
   *
   * @return The name of the module.
   */
  [[nodiscard]] std::string get_module_name() const;
  /**
   * This method provides access to the HTypes mask that was set during
   * configuration. The HTypes mask determines which log messages are
   * processed by this logger.
   *
   * @return The HTypes mask.
   */
  [[nodiscard]] htypes_mask_t get_type_mask() const;
  /**
   * This method provides access to the sinks information that was set during configuration.
   * The sinks information determines which log messages are routed to which sinks.
   *
   * @return A constant reference to the sinks information.
   */
  [[nodiscard]] const sinks_info& get_sinks_info() const;
  /**
   * This method retrieves the default logging level that was set during
   * initialization. The logging level determines which log messages are
   * processed by this logger.
   *
   * @return The default logging level.
   */
  [[nodiscard]] hlevels get_level() const;
  /**
   * This method retrieves the log format that was set during configuration. The
   * log format determines how log messages are formatted for output.
   *
   * @return A constant reference to the log format, or an empty optional if no format is set.
   */
  [[nodiscard]] std::optional<std::string> get_log_format() const;
  /**
   * This method retrieves the log date format that was set during configuration. The
   * log date format determines how dates are formatted for output in logs.
   *
   * @return A constant reference to the log date format, or an empty optional if no format is set.
   */
  [[nodiscard]] std::optional<std::string> get_log_format_date() const;
  /**
   * Retrieves the log format that corresponds to the specified logging level.
   *
   * @param level The logging level for which to retrieve the log format.
   * @return A constant reference to the log format, or an empty optional if no format is set
   */
  [[nodiscard]] std::optional<std::string> get_log_format_level() const;

  /**
   * Sets a new project name for this logger. This method allows you to dynamically
   * change the project name associated with this logger.
   *
   * @param new_project_name The new project name to set.
   */
  virtual void set_project_name(std::string new_project_name) = 0;

  /**
   * This method sets the name of the module that this logger is associated with.
   *
   * @param new_module_name The new name for the module.
   */
  virtual void set_module_name(std::string new_module_name) = 0;

  /**
   *  Sets the default logging level for this logger.
   *
   * @param new_hlevel The new logging level to use.
   */
  virtual void set_hlevel(hlevels new_hlevel) = 0;

  /**
   * This method creates a new configuration object that is a deep copy of the
   * current configuration. The new configuration object has its own independent
   * state, and any changes made to it do not affect the original configuration.
   *
   * @return A pointer to the new configuration object.
   */
  [[nodiscard]] virtual std::unique_ptr<config> clone() const = 0;

  /**
   * This method creates a logger name based on the given project and module names.
   * The generated logger name is in the format "project_name-module_name".
   *
   * @param project_name The project name to use for the logger name.
   * @param module_name The module name to use for the logger name.
   * @return The generated logger name.
   */
  static std::string create_logger_name(const std::string& project_name, const std::string& module_name);
  /**
   * This method parses a logger name and extracts the project name and module
   * name from it. It is used to verify that the logger name conforms to the
   * expected format.
   *
   * @param logger_name The logger name to parse.
   * @param project_name The extracted project name.
   * @param module_name The extracted module name.
   * @return Whether the logger name was successfully parsed.
   */
  static bool parse_logger_name(const std::string& logger_name, std::string& project_name, std::string& module_name);

 protected:
  /**
   * This is a protected member variable representing the project name of this logger.
   *
   * @see #set_project_name
   */
  std::string project_name_;
  /**
   * This is a protected member variable representing the name of the module that
   * this logger is associated with.
   *
   * @see #set_module_name
   */
  std::string module_name_;
  /**
   * This is a protected member variable representing the default logging level for this logger.
   *
   * @see #get_level
   */
  hlevels logger_min_level_;
  /**
   * This is a protected member variable representing the masks of log types that this logger can
   * handle.
   *
   * @see #get_types_mask
   */
  htypes_mask_t htypes_mask_;
  /**
   * This is a protected member variable representing the sinks information for this logger.
   *
   * @see #get_sinks_info
   */
  sinks_info sinks_info_;

  /**
   * This is a protected member variable representing the log format date.
   * The log format date represents the format of the timestamp that will be
   * included in logs generated by this logger.
   *
   * @see #get_log_format_date
   */
  std::optional<std::string> log_format_;
  /**
   * This is a protected member variable representing the log format level.
   * The log format level represents the format of the logging level that will be
   * included in logs generated by this logger.
   *
   * @see #get_log_format_level
   */
  std::optional<std::string> log_format_date_;
  /**
   * This is a protected member variable representing the log format level for a specified logging
   * level. The log format level represents the format of the logging level that will be included in
   * logs generated by this logger, with respect to a specific logging level.
   *
   * @see #get_log_format_level
   */
  std::optional<std::string> log_format_level_;
};

using config_ptr = config::ptr;
} // namespace hare
