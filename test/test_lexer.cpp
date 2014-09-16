#include "gtest.h"

#include "lexer.hpp"
#include "helper_lexer.hpp"

TEST(lexer, emptySource) {
  std::stringstream is;
  auto tokens = klang::tokenize(is);
  EXPECT_EQ("", test::to_string(tokens));
}

TEST(lexer, hello) {
  std::stringstream is;
  is << "{~\n"
     << "  とりあえずのデバッグ用\n"
     << "  まだdeclareもstringもない\n"
     << "  declare print(string) -> ();\n"
     << "~}\n"
     << "\n"
     << "def main() -> (int) {\n"
     << "  print(\"Hello, World!\\n\");\n"
     << "  return 0;\n"
     << "}\n";
  auto tokens = klang::tokenize(is);
  std::stringstream expect;
  expect << "SYMBOL: def at Line 7\n"
         << "IDENTIFIER: main at Line 7\n"
         << "SYMBOL: ( at Line 7\n"
         << "SYMBOL: ) at Line 7\n"
         << "SYMBOL: -> at Line 7\n"
         << "SYMBOL: ( at Line 7\n"
         << "SYMBOL: int at Line 7\n"
         << "SYMBOL: ) at Line 7\n"
         << "SYMBOL: { at Line 7\n"
         << "IDENTIFIER: print at Line 8\n"
         << "SYMBOL: ( at Line 8\n"
         << "STRING: Hello, World!\n"
         << " at Line 8\n"
         << "SYMBOL: ) at Line 8\n"
         << "SYMBOL: ; at Line 8\n"
         << "SYMBOL: return at Line 9\n"
         << "NUMBER: 0 at Line 9\n"
         << "SYMBOL: ; at Line 9\n"
         << "SYMBOL: } at Line 10\n";
  EXPECT_EQ(expect.str(), test::to_string(tokens));
}
