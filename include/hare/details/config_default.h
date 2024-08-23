#pragma once
#include "hare/config.h"

namespace hare {
  /**
   * @brief The config_default class represents a default configuration for hare applications.
   *
   * It provides a set of methods to configure project and module names, as well as log levels.
   */
  struct config_default: public config {
    /**
     * @brief Construct a new config_default object with optional project and module names.
     *
     * @param project_name The name of the project (default is empty string).
     * @param module_name The name of the module (default is empty string).
     */
    explicit config_default(std::string project_name = std::string(), std::string module_name = std::string());
    /**
     * Destructor. Releases any resources allocated by this object.
     *
     * @see ~config
     */
    virtual ~config_default() override;

    /**
     * @brief Set the project name.
     *
     * @param new_logger_name The new project name.
     */
    void set_project_name(std::string new_logger_name) override;

    /**
     * @brief Set the module name.
     *
     * @param new_module_name The new module name.
     */
    void set_module_name(std::string new_module_name) override;

    /**
     * @brief Set the log level.
     *
     * @param new_hlevel The new log level.
     */
    void set_hlevel(hlevels new_hlevel) override;

    /**
     * @brief Get a deep copy of this config object.
     *
     * @return A unique pointer to the cloned config object.
     */
    [[nodiscard]] std::unique_ptr<config> clone() const override;

    /**
     * @brief Get the default project name.
     *
     * @return The default project name.
     */
    static std::string get_default_project_name();
  };
} // namespace hare
