#pragma once
#include "hlevels.h"
#include "config.h"
#include "details/config_default.h"

#include <format>
#include <optional>
#include <string_view>
#include <memory>
#include <mutex>


namespace hare {
class hlogger final {
 public:
  explicit hlogger(config_ptr config = std::make_unique<config_default>());
  ~hlogger();

  ///
  /// \param log_message
  void trace(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void debug(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void info(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void warn(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void warning(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void error(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void critical(std::string_view log_message) noexcept;
  ///
  /// \param log_message
  void fatal(std::string_view log_message) noexcept;

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void trace(const std::string_view log_format_message, Args &&... args) noexcept {
    trace(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void debug(const std::string_view log_format_message, Args &&... args) noexcept {
    debug(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void info(const std::string_view log_format_message, Args &&... args) noexcept {
    info(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void warn(const std::string_view log_format_message, Args &&... args) noexcept {
    warn(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void warning(const std::string_view log_format_message, Args &&... args) noexcept {
    warning(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void error(const std::string_view log_format_message, Args &&... args) noexcept {
    error(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void critical(const std::string_view log_format_message, Args &&... args) noexcept {
    critical(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  ///
  /// \tparam T
  /// \param log_format_message
  /// \param args
  template<typename... Args>
  void fatal(const std::string_view log_format_message, Args &&... args) noexcept {
    fatal(std::vformat(log_format_message, std::make_format_args(args...)));
  }

  [[nodiscard]] config_ptr get_config_copy() const;

 private:
  void initialize();

  [[nodiscard]] constexpr bool is_level_enabled(hlevels level) const;

  const config_ptr config_;

  struct logger_pimpl;
  std::unique_ptr<logger_pimpl> logger_pimpl_;
};

using hlogger_ptr = std::shared_ptr<hlogger>;
} // namespace hare
