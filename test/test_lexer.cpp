#include "lexer.hpp"
#include "helper_lexer.hpp"

#include "gtest.h"

TEST(lexer, emptySource) {
  std::stringstream is;
  auto tokens = klang::tokenize(is);
  EXPECT_EQ("", test::to_string(tokens));
}

TEST(lexer, hello) {
  std::stringstream is;
  is <<
R"({~
  とりあえずのデバッグ用
  まだdeclareもstringもない
  declare print(string) -> ();
~}

def main() -> (int) {
  print("Hello, World!\n");
  return 0;
}
)";
  auto tokens = klang::tokenize(is);
  using T = klang::Token;
  using klang::TokenType;
  klang::TokenVector const expect = {
      T{TokenType::SYMBOL, "def", 7},
      T{TokenType::IDENTIFIER, "main", 7},
      T{TokenType::SYMBOL, "(", 7},
      T{TokenType::SYMBOL, ")", 7},
      T{TokenType::SYMBOL, "->", 7},
      T{TokenType::SYMBOL, "(", 7},
      T{TokenType::SYMBOL, "int", 7},
      T{TokenType::SYMBOL, ")", 7},
      T{TokenType::SYMBOL, "{", 7},
      T{TokenType::IDENTIFIER, "print", 8},
      T{TokenType::SYMBOL, "(", 8},
      T{TokenType::STRING, "Hello, World!\n", 8},
      T{TokenType::SYMBOL, ")", 8},
      T{TokenType::SYMBOL, ";", 8},
      T{TokenType::SYMBOL, "return", 9},
      T{TokenType::NUMBER, "0", 9},
      T{TokenType::SYMBOL, ";", 9},
      T{TokenType::SYMBOL, "}", 10},
  };
  ASSERT_EQ(expect.size(), tokens.size());
  for(size_t i(0); i < expect.size(); ++i)
    EXPECT_EQ(expect[i], tokens[i]);
}

TEST(lexer, comment1) {
  std::stringstream is;
  is <<
R"(
{~ comment
  {~ nest ~}
~}
def placeholder
)";
  auto tokens = klang::tokenize(is);
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
