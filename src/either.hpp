#ifndef KMC_KLANG_EITHER_HPP
#define KMC_KLANG_EITHER_HPP

#include <cassert>
#include <utility>

namespace klang {

struct LeftTag {};
struct RightTag {};

constexpr LeftTag left_tag;
constexpr RightTag right_tag;

template <typename L>
class Left {
 public:
  explicit Left(const L& src)
      : left_{src}
  {}
  explicit Left(L&& src)
      : left_{std::move(src)}
  {}
  Left(const Left&) = default;
  Left(Left&&) = default;
  Left& operator=(const Left&) = default;
  Left& operator=(Left&&) = default;
  void swap(Left& that) {
    using std::swap;
    swap(left_, that.left_);
  }
  const L& value() const& {
    return left_;
  }
  L&& value() && {
    return std::move(left_);
  }
  template <typename L_>
  friend class Left;
  friend void swap(Left& lhs, Left& rhs) {
    lhs.swap(rhs);
  }
  friend bool operator==(const Left& lhs, const Left& rhs) {
    return lhs.left_ == rhs.left_;
  }
  friend bool operator<(const Left& lhs, const Left& rhs) {
    return lhs.left_ < rhs.left_;
  }
 private:
  L left_;
};

template <typename R>
class Right {
 public:
  explicit Right(const R& src)
      : right_{src}
  {}
  explicit Right(R&& src)
      : right_{std::move(src)}
  {}
  Right(const Right&) = default;
  Right(Right&&) = default;
  Right& operator=(const Right&) = default;
  Right& operator=(Right&&) = default;
  void swap(Right& that) {
    using std::swap;
    swap(right_, that.right_);
  }
  const R& value() const& {
    return right_;
  }
  R&& value() && {
    return std::move(right_);
  }
  template <typename R_>
  friend class Right;
  friend void swap(Right& lhs, Right& rhs) {
    lhs.swap(rhs);
  }
  friend bool operator==(const Right& lhs, const Right& rhs) {
    return lhs.right_ == rhs.right_;
  }
  friend bool operator<(const Right& lhs, const Right& rhs) {
    return lhs.right_ < rhs.right_;
  }
 private:
  R right_;
};

template <typename L, typename R>
class Either {
 public:
  Either(LeftTag, const L& left)
      : is_right_{false}, left_{left}
  {}
  Either(LeftTag, L&& left)
      : is_right_{false}, left_{std::move(left)}
  {}
  Either(RightTag, const R& right)
      : is_right_{true}, right_{right}
  {}
  Either(RightTag, R&& right)
      : is_right_{true}, right_{std::move(right)}
  {}
  Either(const Either& that)
      : is_right_{that.is_right_} {
    construct(that);
  }
  Either(Either&& that)
      : is_right_{that.is_right_} {
    construct(std::move(that));
  }
  Either& operator=(const Either& that) {
    assign(that);
    return *this;
  }
  Either& operator=(Either&& that) {
    assign(std::move(that));
    return *this;
  }
  ~Either() {
    destruct();
  }
  void swap(Either& that) {
    Either tmp{std::move(*this)};
    *this = std::move(that);
    that = std::move(tmp);
  }
  bool is_left() const {
    return !is_right_;
  }
  bool is_right() const {
    return is_right_;
  }
  Left<L> left() const& {
    assert(!is_right_);
    return Left<L>{left_};
  }
  Left<L> left() && {
    assert(!is_right_);
    return Left<L>{std::move(left_)};
  }
  Right<R> right() const& {
    assert(is_right_);
    return Right<R>{right_};
  }
  Right<R> right() && {
    assert(is_right_);
    return Right<R>{std::move(right_)};
  }
  explicit operator bool() const {
    return is_right_;
  }
  const R& operator*() const& {
    assert(is_right_);
    return right_;
  }
  R& operator*() & {
    assert(is_right_);
    return right_;
  }
  R&& operator*() && {
    assert(is_right_);
    return std::move(right_);
  }
  const R* operator->() const {
    assert(is_right_);
    return &right_;
  }
  R* operator->() {
    assert(is_right_);
    return &right_;
  }
  template <typename L_, typename R_>
  friend class Either;
  friend void swap(Either& lhs, Either& rhs) {
    lhs.swap(rhs);
  }
  friend bool operator==(const Either& lhs, const Either& rhs) {
    if (lhs.is_right_ != rhs.is_right_) {
      return false;
    } else if (lhs.is_right_) {
      return lhs.right_ == rhs.right_;
    } else {
      return lhs.left_ == rhs.left_;
    }
  }
  friend bool operator<(const Either& lhs, const Either& rhs) {
    if (lhs.is_right_ != rhs.is_right_) {
      return rhs.is_right_;
    } else if (lhs.is_right_) {
      return lhs.right_ < rhs.right_;
    } else {
      return lhs.left_ < rhs.left_;
    }
  }
 private:
  void construct(const Either& src) {
    if (src.is_right_) {
      new (&right_) R{src.right_};
    } else {
      new (&left_) L{src.left_};
    }
  }
  void construct(Either&& src) {
    if (src.is_right_) {
      new (&right_) R{std::move(src.right_)};
    } else {
      new (&left_) L{std::move(src.left_)};
    }
  }
  void assign(const Either& src) {
    if (is_right_ == src.is_right_) {
      if (is_right_) {
        right_ = src.right_;
      } else {
        left_ = src.left_;
      }
    } else {
      destruct();
      construct(src);
      is_right_ = src.is_right_;
    }
  }
  void assign(Either&& src) {
    if (is_right_ == src.is_right_) {
      if (is_right_) {
        right_ = std::move(src.right_);
      } else {
        left_ = std::move(src.left_);
      }
    } else {
      destruct();
      construct(std::move(src));
      is_right_ = src.is_right_;
    }
  }
  void destruct() {
    if (is_right_) {
      right_.~R();
    } else {
      left_.~L();
    }
  }
 private:
  bool is_right_;
  union {
    L left_;
    R right_;
  };
};

}  // namespace klang

#endif  // KMC_KLANG_EITHER_HPP
