#include "lexer.hpp"
#include "helper_lexer.hpp"

#include "gtest.h"

namespace {
    using T = klang::Token;
    using klang::TokenType;
}

#define TEST_PRIM_ORIG(type, prefix, name, value) \
TEST(lexer, prefix ## name) { \
  std::stringstream is; \
  is << value; \
  klang::TokenVector tokens; \
  bool success; \
  std::tie(success, tokens) = klang::tokenize(is); \
  EXPECT_TRUE(success); \
  klang::TokenVector const expect = { \
      T{type, value, 1}, \
  }; \
  EXPECT_EQ(expect, tokens); \
}
// end of TEST_PRIM_ORIG

#define TEST_PRIM_SYMBOL(name, sym) TEST_PRIM_ORIG(TokenType::SYMBOL, primSymbol, name, sym)

#define TEST_PRIM_IDENTIFIER(name, identifier) TEST_PRIM_ORIG(TokenType::IDENTIFIER, primSymbol, name, identifier)

#define TEST_PRIM_NUMBER(name, number) TEST_PRIM_ORIG(TokenType::NUMBER, primNumber, name, number)

#define TEST_PRIM_STRING(name, str) \
TEST(lexer, primString ## name) { \
  std::stringstream is; \
  is << #str; \
  klang::TokenVector tokens; \
  bool success; \
  std::tie(success, tokens) = klang::tokenize(is); \
  EXPECT_TRUE(success); \
  klang::TokenVector const expect = { \
      T{TokenType::STRING, str, 1}, \
  }; \
  EXPECT_EQ(expect, tokens); \
}
// end of TEST_PRIM_STRING
// アンクォートされた文字列をtokinize して返すので、一段クォートしないといけない。

#define TEST_PRIM_IGNORE(name, ign) \
TEST(lexer, primIgnore ## name) { \
  std::stringstream is; \
  is << ign; \
  klang::TokenVector tokens; \
  bool success; \
  std::tie(success, tokens) = klang::tokenize(is); \
  EXPECT_TRUE(success); \
  EXPECT_EQ(klang::TokenVector(), tokens); \
}
// end of TEST_PRIM_IGNORE_ORIG

TEST_PRIM_SYMBOL(WaveDash, "~")
TEST_PRIM_SYMBOL(Puls, "+")
TEST_PRIM_SYMBOL(Minus, "-")
TEST_PRIM_SYMBOL(Mul, "*")
TEST_PRIM_SYMBOL(Div, "/")
TEST_PRIM_SYMBOL(Persent, "%")
TEST_PRIM_SYMBOL(colonEq, ":=")
TEST_PRIM_SYMBOL(colonPlusEq, ":+=")
TEST_PRIM_SYMBOL(colonMinusEq, ":-=")
TEST_PRIM_SYMBOL(colonMulEq, ":*=")
TEST_PRIM_SYMBOL(colonDivEq, ":/=")
TEST_PRIM_SYMBOL(colonPersentEq, ":%=")
TEST_PRIM_SYMBOL(Equal, "=")
TEST_PRIM_SYMBOL(NotEqual, "=/")
TEST_PRIM_SYMBOL(LessThan, "<")
TEST_PRIM_SYMBOL(MoreThan, ">")
TEST_PRIM_SYMBOL(LessThanOrEq, "<=")
TEST_PRIM_SYMBOL(MoreThanOrEq, ">=")
TEST_PRIM_SYMBOL(SemiColon, ";")
TEST_PRIM_SYMBOL(LeftParen, "(")
TEST_PRIM_SYMBOL(RightParen, ")")
TEST_PRIM_SYMBOL(LeftBracket, "{")
TEST_PRIM_SYMBOL(RightBracket, "}")
TEST_PRIM_SYMBOL(Arrow, "->")
TEST_PRIM_SYMBOL(CloseComment, "~}")
TEST_PRIM_SYMBOL(And, "and")
TEST_PRIM_SYMBOL(Or, "or")
TEST_PRIM_SYMBOL(Not, "not")
TEST_PRIM_SYMBOL(Int, "int")
TEST_PRIM_SYMBOL(Def, "def")
TEST_PRIM_SYMBOL(Var, "var")
TEST_PRIM_SYMBOL(If, "if")
TEST_PRIM_SYMBOL(Else, "else")
TEST_PRIM_SYMBOL(While, "while")
TEST_PRIM_SYMBOL(For, "for")
TEST_PRIM_SYMBOL(Break, "break")
TEST_PRIM_SYMBOL(Continue, "continue")
TEST_PRIM_SYMBOL(Return, "return")

TEST_PRIM_IDENTIFIER(AllLower, "identifier")
TEST_PRIM_IDENTIFIER(AllUpper, "IDENTIFIER")
TEST_PRIM_IDENTIFIER(Camel, "Identifier")
TEST_PRIM_IDENTIFIER(Snake, "i_d_e_n_t_i_f_i_e_r")
TEST_PRIM_IDENTIFIER(Number, "identifier42")
TEST_PRIM_IDENTIFIER(HeadBar, "_identifier")
TEST_PRIM_IDENTIFIER(BarOrNum, "_4_2_")
TEST_PRIM_IDENTIFIER(AllBar, "__________")
TEST_PRIM_IDENTIFIER(BarNumAlpha, "_42identifier")

TEST_PRIM_NUMBER(Zero, "0")
TEST_PRIM_NUMBER(One, "1")
TEST_PRIM_NUMBER(Two, "2")
TEST_PRIM_NUMBER(Three, "3")
TEST_PRIM_NUMBER(Four, "4")
TEST_PRIM_NUMBER(Five, "5")
TEST_PRIM_NUMBER(Six, "6")
TEST_PRIM_NUMBER(Seven, "7")
TEST_PRIM_NUMBER(Eight, "8")
TEST_PRIM_NUMBER(Nine, "9")
TEST_PRIM_NUMBER(Ten, "10")
TEST_PRIM_NUMBER(TheAnswerToTheUltimateQuestionOfLifeTheUniverseAndEverything, "42")
TEST_PRIM_NUMBER(Hundred, "100")

TEST_PRIM_STRING(Normal, "string")
TEST_PRIM_STRING(Quoted, "\"string\"")
TEST_PRIM_STRING(EscapedQuote, "\\\"string")
TEST_PRIM_STRING(EscapedQuote2, "\\\\\"string")
TEST_PRIM_STRING(EscapedQuote3, "\\\\\\\"string")
TEST_PRIM_STRING(Quote, "\"")
TEST_PRIM_STRING(Quote2, "\\\"")
TEST_PRIM_STRING(BackSlash, "\\")
TEST_PRIM_STRING(BackSlash2, "\\\\")
TEST_PRIM_STRING(NewLine, "\n")
TEST_PRIM_STRING(NewLineQ, "\\n")
TEST_PRIM_STRING(Tab, "\t")
TEST_PRIM_STRING(TabQ, "\\t")

TEST_PRIM_IGNORE(EmptySource, "")
TEST_PRIM_IGNORE(Space, " ")
TEST_PRIM_IGNORE(NewLine, "\n")
TEST_PRIM_IGNORE(Tab, "\t")
TEST_PRIM_IGNORE(SingleComment, "~~ This is comment.")
TEST_PRIM_IGNORE(MultiLineComment, "{~ This is comment. ~}")

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
