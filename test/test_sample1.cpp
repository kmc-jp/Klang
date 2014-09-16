#include "gtest.h"

// http://opencv.jp/googletestdocs/primer.html Google test 入門ガイド

TEST(alwaysPass, assertTrue) {
  ASSERT_TRUE(true);
}

TEST(alwaysPass, eq11) {
  EXPECT_EQ(1, 1);
}

TEST(alwaysPass, lt12) {
  EXPECT_LT(1, 2);
}
