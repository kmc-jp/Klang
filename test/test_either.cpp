#include "either.hpp"

#include <string>

#include "gtest.h"

using namespace klang;

TEST(Left, left) {
  const std::string value("left");
  const Left<std::string> l(value);

  ASSERT_EQ(value, l.value());

  auto const e = make_left(value);

  // implicit conversion Left<T> to Either<U, T>
  ASSERT_EQ(e, l);
}

TEST(Right, right) {
  const std::string value("right");
  const Right<std::string> r(value);

  ASSERT_EQ(value, r.value());

  auto const e = make_right(value);

  // implicit conversion Right<T> to Either<T, U>
  ASSERT_EQ(e, r);
}

TEST(either, left) {
  const std::string value("left");
  const Either<std::string, int> e(left_tag, value);
  ASSERT_TRUE(e.is_left());
  ASSERT_FALSE(e.is_right());
  ASSERT_FALSE(static_cast<bool>(e));
  ASSERT_EQ(value, e.left().value());

  ASSERT_DEATH(e.right().value(), "");
  ASSERT_DEATH(*e, "");
}

TEST(either, right) {
  const std::string value("right");
  const Either<double, std::string> e(right_tag, value);
  ASSERT_FALSE(e.is_left());
  ASSERT_TRUE(e.is_right());
  ASSERT_TRUE(static_cast<bool>(e));
  ASSERT_EQ(value, e.right().value());

  // We can treat the Either<S,T> value as the pointer of type T,
  // when the value has the right value.
  ASSERT_EQ(value, *e);
  ASSERT_EQ(value.length(), e->length());

  ASSERT_DEATH(e.left(), "");
}

TEST(either, sameType) {
  const std::string value("both");
  Either<std::string, std::string> l(left_tag, value);
  const Either<std::string, std::string> r(right_tag, value);

  ASSERT_TRUE(l.is_left());
  ASSERT_FALSE(r.is_left());
  ASSERT_FALSE(l.is_right());
  ASSERT_TRUE(r.is_right());
  ASSERT_EQ(l.left().value(), *r);

  l = r;
  ASSERT_TRUE(l.is_right());
  ASSERT_EQ(value, *l);
}

TEST(either, swap) {
  const std::string value("value");
  Either<std::string, int> e1(left_tag, value);
  Either<std::string, int> e2(right_tag, 42);
  ASSERT_EQ(value, e1.left().value());
  ASSERT_EQ(42, *e2);

  swap(e1, e2);
  ASSERT_EQ(42, *e1);
  ASSERT_EQ(value, e2.left().value());

  swap(e1, e2);
  ASSERT_EQ(value, e1.left().value());
  ASSERT_EQ(42, *e2);
}

TEST(either, comparators) {
  const Either<int, int> e1(left_tag, 0);
  const Either<int, int> e2(right_tag, 1);
  const Either<int, int> e3(left_tag, 2);
  const Either<int, int> e4(right_tag, 3);

  ASSERT_TRUE(e1 < e2);
  ASSERT_FALSE(e2 < e1);
  ASSERT_TRUE(e1 < e3);
  ASSERT_FALSE(e3 < e1);
  ASSERT_FALSE(e2 < e3);
  ASSERT_TRUE(e3 < e2);
  ASSERT_TRUE(e2 < e4);
  ASSERT_FALSE(e4 < e2);
  ASSERT_TRUE(e3 < e4);
  ASSERT_FALSE(e4 < e3);
}

TEST(either, equals) {
  const Either<int, int> e1(right_tag, 0);
  const Either<int, int> e2(left_tag, 0);
  const Either<int, int> e3(right_tag, 0);
  const Either<int, int> e4(left_tag, 0);

  ASSERT_FALSE(e1 == e2);
  ASSERT_TRUE(e1 == e3);
  ASSERT_FALSE(e2 == e3);
  ASSERT_TRUE(e2 == e4);
}
