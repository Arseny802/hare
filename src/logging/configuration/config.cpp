//
// Created by arseny on 01/05/2020.
//

#include "config.h"

namespace hare {

Config::Config(std::string_view project_name) {
  project_name_ = std::string(project_name);
}

void Config::SetProjectName(const std::string_view project_name) {
  project_name_ = project_name;
}

std::string_view Config::GetProjectName() const {
  return project_name_;
}
Levels Config::GetLevel() const {
  return level_;
}
void Config::SetLevel(Levels level) {
  level_ = level;
}
Config::Config() {}

}
