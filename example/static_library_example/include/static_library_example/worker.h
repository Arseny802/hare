#pragma once

#include <string>
#include <vector>

namespace static_library_example {
  /**
   * @brief A simple worker class that encapsulates some functionality.
   *
   * This class provides methods for performing tasks and handling data.
   */
  class worker {
public:
    /**
     * Constructor for worker.
     *
     * @brief A brief description of what this class does.
     */
    worker();
    /**
     * Destructor for the worker. Frees any resources allocated by the
     * constructor or during the lifetime of the object.
     *
     * @post No external resources will be held.
     */
    ~worker();
    /**
     * Checks if a given vector of integers has any repetitions.
     *
     * @param data The vector to check for repetition.
     * @return Whether or not the vector contains any repeated values.
     */
    [[nodiscard]] static bool vector_has_repetitions(const std::vector<int>& data) noexcept;
    /**
     * Retrieves some value from this worker instance.
     *
     * @return The retrieved value.
     */
    [[nodiscard]] std::string some_getter() const noexcept;
    /**
     * Sets a value in the worker instance.
     *
     * @param value The new value to set.
     */
    void some_setter(std::string_view value) noexcept;

    /**
     * A constant that specifies how many bytes should be reserved for certain operations.
     */
    static const int k_bytes_to_reserve = 1024;

private:
    std::string some_string_{};
    uint8_t* some_data_;
  };
} // namespace static_library_example
