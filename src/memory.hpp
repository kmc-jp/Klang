#ifndef KMC_KLANG_MEMORY_HPP
#define KMC_KLANG_MEMORY_HPP

#include <memory>

namespace klang {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace klang

#endif  // KMC_KLANG_MEMORY_HPP
