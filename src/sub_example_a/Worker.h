//
// Created by arseny on 28/03/2020.
//

#ifndef HARE_SRC_SUB_EXAMPLE_A_WORKER_H_
#define HARE_SRC_SUB_EXAMPLE_A_WORKER_H_

#include <string>
#include <vector>

namespace sub_example_a {
class Worker {
 public:
  ///
  Worker();
  ///
  ~Worker();

  ///
  /// \tparam T
  /// \param data
  /// \return
  //template <class T>
  [[nodiscard]] bool VectorHasRepetitions(const std::vector<int> &data) const noexcept;
  ///
  /// \return
  [[nodiscard]] std::string SomeGetter() const noexcept;
  ///
  /// \param value
  void SomeSetter(std::string_view value) noexcept;
  static const int kBytesToReserve;
 private:
  std::string some_string_{};
  uint8_t* some_data_;
};
}
#endif //HARE_SRC_SUB_EXAMPLE_WORKER_H_
