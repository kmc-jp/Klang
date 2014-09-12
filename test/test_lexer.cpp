#include "gtest.h"

#include "lexer.hpp"
#include "helper_lexer.hpp"

TEST(lexer, empty_source) {
  std::stringstream is;
  auto tokens = klang::tokenize(is);
  EXPECT_EQ("", test::to_string(tokens));
}
