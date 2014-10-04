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
  Either(const Right& right);
  Either(Right&& right);
  Either(LeftTag, const Left& left);
  Either(LeftTag, Left&& left);
  Either(RightTag , const Right& right);
  Either(RightTag, Right&& right);
  Either(const Either& either);
  Either(Either&& either);
  Either& operator=(const Either& either);
  Either& operator=(Either&& either);
  void swap(Either& that);
  bool is_left() const;
  bool is_right() const;
  const Left& left_value() const;
  const Right& right_value() const;
  explicit operator bool() const;
  const Right& operator*() const&;
  Right& operator*() &;
  Right&& operator*() &&;
  const Right* operator->() const;
  Right* operator->();
 private:
  optional<Left> left_;
  optional<Right> right_;
};

template <typename Left, typename Right, typename E = Either<Left, Right> >
bool operator==(const E& lhs, const E& rhs);

template <typename Left, typename Right, typename E = Either<Left, Right> >
bool operator<(const E& lhs, const E& rhs);

template <typename Left, typename Right, typename E = Either<Left, Right> >
void swap(E& lhs, E& rhs);

}  // namespace klang

#endif  // KMC_KLANG_EITHER_HPP
