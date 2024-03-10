#pragma once

#include <string>
#include <vector>

namespace static_library_example {
class worker {
 public:
  ///
  worker();
  ///
  ~worker();

  ///
  /// \param data
  /// \return
  [[nodiscard]] static bool vector_has_repetitions(const std::vector<int> &data) noexcept;
  ///
  /// \return
  [[nodiscard]] std::string some_getter() const noexcept;
  ///
  /// \param value
  void some_setter(std::string_view value) noexcept;

  static const int k_bytes_to_reserve_;

 private:
  std::string some_string_{};
  uint8_t* some_data_;
};
} // namespace static_library_example
