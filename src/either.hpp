#ifndef KMC_KLANG_EITHER_HPP
#define KMC_KLANG_EITHER_HPP

#include <boost/optional.hpp>

namespace klang {

template <typename T>
using optional = boost::optional<T>;

struct LeftTag {};
struct RightTag {};

constexpr LeftTag left_tag;
constexpr RightTag right_tag;

template <typename Left, typename Right>
class Either {
 public:
  Either(const Either& either) = default;
  Either(Either&& either) = default;
  Either& operator=(const Either& either) = default;
  Either& operator=(Either&& either) = default;
 private:
  optional<Left> left_;
  optional<Right> right_;
};

}  // namespace klang

#endif  // KMC_KLANG_EITHER_HPP
