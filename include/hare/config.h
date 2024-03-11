#pragma once
#include "hare/hlevels.h"
#include "hare/htypes.h"
#include "hare/sinks_info.h"

#include <string>
#include <optional>
#include <memory>

namespace hare {
///
struct config {
  ///
  /// \param logger_name
  explicit config(std::string logger_name,
                  hlevels level = hlevels::trace);
  virtual ~config();
  ///
  /// \return
  [[nodiscard]] std::string get_logger_name() const;
  ///
  /// \return
  [[nodiscard]] std::string get_project_name() const;
  ///
  /// \return
  [[nodiscard]] std::string get_module_name() const;
  ///
  /// \return
  [[nodiscard]] htypes_mask_t get_type_mask() const;
  ///
  /// \return
  [[nodiscard]] const sinks_info& get_sinks_info() const;
  ///
  /// \return
  [[nodiscard]] hlevels get_level() const;
  ///
  /// \return
  [[nodiscard]] std::optional<std::string> get_log_format() const;
  ///
  /// \return
  [[nodiscard]] std::optional<std::string> get_log_format_date() const;
  ///
  /// \return
  [[nodiscard]] std::optional<std::string> get_log_format_level() const;

  ///
  /// \param new_project_name
  virtual void set_project_name(std::string new_project_name) = 0;

  ///
  /// \param new_module_name
  virtual void set_module_name(std::string new_module_name) = 0;
  ///
  /// \param new_hlevel
  virtual void set_hlevel(hlevels new_hlevel) = 0;

  ///
  [[nodiscard]] virtual std::unique_ptr<config> clone() const = 0;

  static std::string create_logger_name(const std::string &project_name, const std::string &module_name);
  static bool parse_logger_name(const std::string &logger_name, std::string &project_name, std::string &module_name);

 protected:
  std::string project_name_;
  std::string module_name_;
  hlevels logger_min_level_;
  htypes_mask_t htypes_mask_;
  sinks_info sinks_info_;

  std::optional<std::string> log_format_;
  std::optional<std::string> log_format_date_;
  std::optional<std::string> log_format_level_;
};

using config_ptr = std::unique_ptr<config>;
} // namespace hare
