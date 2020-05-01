//
// Created by arseny on 01/05/2020.
//

#include "config.h"

namespace hare {

void Config::SetProjectName(const std::string &project_name) {
  project_name_ = project_name;
}
const std::string &Config::GetProjectName() const {
  return project_name_;
}
Config::Config(std::string_view project_name) {
  project_name_ = std::string(project_name);
}

}
