#ifndef KMC_KLANG_EITHER_HPP
#define KMC_KLANG_EITHER_HPP

#include <boost/optional.hpp>

namespace klang {

template <typename T>
using optional = boost::optional<T>;

struct LeftTag {} left_tag;
struct RightTag {} right_tag;

template <typename Left, typename Right>
class Either {
 public:
  Either(const Right& right)
      : Either(right_tag, right)
  {}
  Either(Right&& right)
      : Either(right_tag, std::move(right))
  {}
  Either(LeftTag, const Left& left)
      : left_(left), right_()
  {}
  Either(LeftTag, Left&& left)
      : left_(std::move(left)), right_()
  {}
  Either(RightTag, const Right& right)
      : left_(), right_(right)
  {}
  Either(RightTag, Right&& right)
      : left_(), right_(std::move(right))
  {}
  Either(const Either& either) = default;
  Either(Either&& either) = default;
  Either& operator=(const Either& either) = default;
  Either& operator=(Either&& either) = default;
  void swap(Either& that) {
    Either tmp = std::move(*this);
    *this = std::move(that);
    that = std::move(tmp);
  }
  bool is_left() const {
    return static_cast<bool>(left_);
  }
  bool is_right() const {
    return static_cast<bool>(right_);
  }
  const Left& left_value() const {
    return *left_;
  }
  const Right& right_value() const {
    return *right_;
  }
  explicit operator bool() const {
    return is_right();
  }
  const Right& operator*() const& {
    return *right_;
  }
  Right& operator*() & {
    return *right_;
  }
  Right&& operator*() && {
    return std::move(*right_);
  }
  const Right* operator->() const {
    return &*right_;
  }
  Right* operator->() {
    return &*right_;
  }
 private:
  optional<Left> left_;
  optional<Right> right_;
};

template <typename Left, typename Right>
bool operator==(const Either<Left, Right>& lhs,
                const Either<Left, Right>& rhs) {
  if (lhs && rhs) {
    return *lhs == *rhs;
  } else if (!lhs && !rhs) {
    return lhs.left_value() == rhs.left_value();
  } else {
    return false;
  }
}

template <typename Left, typename Right>
bool operator<(const Either<Left, Right>& lhs,
               const Either<Left, Right>& rhs) {
  if (lhs) {
    if (rhs) {
      return *lhs < *rhs;
    } else {
      return false;
    }
  } else {
    if (rhs) {
      return true;
    } else {
      return lhs.left_value() < rhs.left_value();
    }
  }
}

template <typename Left, typename Right>
void swap(Either<Left, Right>& lhs, Either<Left, Right>& rhs) {
  lhs.swap(rhs);
}

}  // namespace klang

#endif  // KMC_KLANG_EITHER_HPP
