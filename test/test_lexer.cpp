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
  std::string nl("\n");
  is << "{~" << nl
     << "  とりあえずのデバッグ用" << nl
     << "  まだdeclareもstringもない" << nl
     << "  declare print(string) -> ();" << nl
     << "~}" << nl
     << "" << nl
     << "def main() -> (int) {" << nl
     << "  print(\"Hello, World!\\n\");" << nl
     << "  return 0;" << nl
     << "}" << nl;
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
      EXPECT_TRUE(expect[i] == tokens[i]);
}
