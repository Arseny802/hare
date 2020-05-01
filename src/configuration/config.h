//
// Created by arseny on 01/05/2020.
//

#ifndef HARE_SRC_CONFIGURATION_CONFIG_H_
#define HARE_SRC_CONFIGURATION_CONFIG_H_

#include <string>

namespace hare {
struct Config {

  explicit Config(const std::string_view project_name);

  [[nodiscard]] const std::string &GetProjectName() const;
  void SetProjectName(const std::string &project_name);

 private:
  std::string project_name_;
};
}

#endif //HARE_SRC_CONFIGURATION_CONFIG_H_
