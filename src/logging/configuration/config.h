#pragma once

#include <string>
#include <memory>
#include "DiagnosticLevels.h"

namespace hare {
///
struct Config {
  ///
  /// \param project_name
  explicit Config(std::string_view project_name, Levels level);
  Config();

  ///
  /// \return
  [[nodiscard]] std::string_view GetProjectName() const;
  ///
  /// \param project_name
  void SetProjectName(std::string_view project_name);
  ///
  /// \return
  [[nodiscard]] Levels GetLevel() const;
  ///
  /// \param level
  void SetLevel(Levels level);
 private:
  std::string project_name_;
  Levels level_;
  bool truncate_file_at_start_;
};
using ConfigPtr = std::unique_ptr<Config>;
}
