#include "gtest.h"

// http://opencv.jp/googletestdocs/primer.html Google test 入門ガイド

TEST(alwaysPass, assert_true) {
  ASSERT_TRUE(true);
}

TEST(alwaysPass, eq1_1) {
  EXPECT_EQ(1, 1);
}

TEST(alwaysPass, lt1_2) {
  EXPECT_LT(1, 2);
}
