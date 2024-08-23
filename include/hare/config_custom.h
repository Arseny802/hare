#pragma once
#include "hare/details/config_default.h"

namespace hare {
  /**
   * Custom configuration for Hare.
   *
   * This structure is used to store custom configurations that are specific to a particular use case or application.
   */
  struct config_custom: config_default {
    /**
     * Default constructor. Initializes the custom configuration with default values.
     */
    config_custom() = default;

    /**
     * Destructor. Cleans up any resources allocated by the custom configuration.
     */
    ~config_custom() override = default;

    /**
     * Sets the log format to use for logging.
     *
     * @param new_log_format The new log format to set.
     */
    void set_log_format(std::string new_log_format);

    /**
     * Sets the date format to use in log messages.
     *
     * @param new_log_format_date The new date format to set.
     */
    void set_log_format_date(std::string new_log_format_date);

    /**
     * Sets the level at which log messages are displayed.
     *
     * @param new_log_format_level The new log level to set.
     */
    void set_log_format_level(std::string new_log_format_level);

    /**
     * Sets the sinks information.
     *
     * @param new_sinks_info The new sinks information to set.
     */
    void set_sinks_info(sinks_info new_sinks_info);
  };
} // namespace hare
