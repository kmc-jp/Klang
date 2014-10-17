#include "lexer.hpp"
#include "helper_lexer.hpp"

#include "gtest.h"

TEST(lexer, comment1) {
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

TEST(lexer, split12345abcde) {
/*
  現在はこのテストは失敗する。
  はやく通過するようになっておくれ

  ref: https://github.com/kmc-jp/Klang/pull/57#issuecomment-57607078
 */
  std::stringstream is;
  is << "12345abcde";
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_FALSE(success);
  ASSERT_EQ(klang::TokenVector(), tokens);
}
