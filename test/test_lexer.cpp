#include "lexer.hpp"
#include "helper_lexer.hpp"

#include "gtest.h"

TEST(lexer, emptySource) {
  std::stringstream is;
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
  EXPECT_EQ(klang::TokenVector(), tokens);
}

TEST(lexer, return0) {
  std::stringstream is;
  is <<
R"(def main() -> (int) {
  return 0;
})";
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
  using T = klang::Token;
  using klang::TokenType;
  klang::TokenVector const expect = {
      T{TokenType::SYMBOL, "def", 1},
      T{TokenType::IDENTIFIER, "main", 1},
      T{TokenType::SYMBOL, "(", 1},
      T{TokenType::SYMBOL, ")", 1},
      T{TokenType::SYMBOL, "->", 1},
      T{TokenType::SYMBOL, "(", 1},
      T{TokenType::SYMBOL, "int", 1},
      T{TokenType::SYMBOL, ")", 1},
      T{TokenType::SYMBOL, "{", 1},
      T{TokenType::SYMBOL, "return", 2},
      T{TokenType::NUMBER, "0", 2},
      T{TokenType::SYMBOL, ";", 2},
      T{TokenType::SYMBOL, "}", 3},
  };
  ASSERT_EQ(expect, tokens);
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
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
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
  ASSERT_EQ(expect, tokens);
}

TEST(lexer, NestedComment1) {
  std::stringstream is;
  is <<
R"({~ comment
  {~ nest ~}
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
      T{TokenType::SYMBOL, "def", 4},
      T{TokenType::IDENTIFIER, "placeholder", 4},
  };
  ASSERT_EQ(expect, tokens);
}

TEST(lexer, brokenComment1Fixed) {
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
  EXPECT_FALSE(success);
  ASSERT_EQ(klang::TokenVector(), tokens);
}

TEST(lexer, brokenComment2) {
  std::stringstream is;
  is << R"({~ broken comment)";
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_FALSE(success);
  ASSERT_EQ(klang::TokenVector(), tokens);
}
