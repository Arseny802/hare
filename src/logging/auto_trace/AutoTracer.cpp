//
// Created by arseny on 25/04/2020.
//

#include "AutoTracer.h"
#include "../hare.hpp"

namespace hare {

AutoTracer::AutoTracer(std::string_view file_name, std::string_view function_signature)
	: file_name_(GetLocalFileName(file_name)), function_signature_(function_signature) {
  if (std::uncaught_exceptions() > 0) {
    spdlog::debug("Function {} entered with {} uncaught exceptions in file {}.",
	            function_signature_.c_str(), std::uncaught_exceptions(), file_name_);
  } else {
    spdlog::debug("Function {} entered in file {}.", function_signature_, file_name_);
  }
}

AutoTracer::~AutoTracer() {
  if (std::uncaught_exceptions() > 0) {
    spdlog::debug("Function {} left with {} uncaught exceptions in file {}.",
                function_signature_.c_str(), std::uncaught_exceptions(), file_name_);
  } else {
    spdlog::debug("Function {} left in file {}.", function_signature_, file_name_);
  }
}

std::string AutoTracer::GetLocalFileName(std::string_view file_name) {
  return std::string(file_name.substr(file_name.find_last_of('/') + 1, file_name.size()));
}

} /* namespace hare */
