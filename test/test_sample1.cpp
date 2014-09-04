#include "gtest.h"

// http://opencv.jp/googletestdocs/primer.html Google test 入門ガイド

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(alwaysPass, assert_true) {
  ASSERT_TRUE(true);
}

TEST(alwaysPass, eq1_1) {
  EXPECT_EQ(1, 1);
}

TEST(alwaysPass, lt1_2) {
  EXPECT_LT(1, 2);
}
