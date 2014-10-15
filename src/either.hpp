#ifndef KMC_KLANG_EITHER_HPP
#define KMC_KLANG_EITHER_HPP

namespace klang {

struct LeftTag {};
struct RightTag {};

constexpr LeftTag left_tag;
constexpr RightTag right_tag;

template <typename L, typename R>
class Either {
 public:
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
