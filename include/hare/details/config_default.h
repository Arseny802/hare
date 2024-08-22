#pragma once
#include "hare/config.h"

namespace hare {
  struct config_default: public config {
    explicit config_default(std::string project_name = std::string(), std::string module_name = std::string());
    ~config_default() override;

    void set_project_name(std::string new_logger_name) override;

    ///
    /// \param new_module_name
    void set_module_name(std::string new_module_name) override;

    void set_hlevel(hlevels new_hlevel) override;

    [[nodiscard]] std::unique_ptr<config> clone() const override;

    static std::string get_default_project_name();
  };
} // namespace hare
