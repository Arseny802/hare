#pragma once
#include "details/exports.h"

#include <string>
#include <vector>

namespace shared_library_example {
  class HARE_EXAMPLE_SUB_API worker {
public:
    ///
    worker();
    ///
    ~worker();

    ///
    /// \tparam T
    /// \param data
    /// \return
    [[nodiscard]] static bool vector_has_repetitions(const std::vector<int>& data) noexcept;
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
} // namespace shared_library_example
