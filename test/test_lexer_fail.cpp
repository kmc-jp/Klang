#include "lexer.hpp"
#include "helper_lexer.hpp"

#include "gtest.h"

TEST(lexer, brokenComment1) {
  std::stringstream is;
  is <<
R"(
{~ comment
  {~ broken nest
~}
def placeholder
)";
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
  using T = klang::Token;
  using klang::TokenType;
  klang::TokenVector const expect = {
      T{TokenType::SYMBOL, "def", 5},
      T{TokenType::IDENTIFIER, "placeholder", 5},
  };
  ASSERT_EQ(expect.size(), tokens.size());
  for(size_t i(0); i < expect.size(); ++i)
    EXPECT_EQ(expect[i], tokens[i]);
}
