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
  std::stringstream expect;
  expect << "SYMBOL: def at Line 7" << nl
         << "IDENTIFIER: main at Line 7" << nl
         << "SYMBOL: ( at Line 7" << nl
         << "SYMBOL: ) at Line 7" << nl
         << "SYMBOL: -> at Line 7" << nl
         << "SYMBOL: ( at Line 7" << nl
         << "SYMBOL: int at Line 7" << nl
         << "SYMBOL: ) at Line 7" << nl
         << "SYMBOL: { at Line 7" << nl
         << "IDENTIFIER: print at Line 8" << nl
         << "SYMBOL: ( at Line 8" << nl
         << "STRING: Hello, World!" << nl
         << " at Line 8" << nl
         << "SYMBOL: ) at Line 8" << nl
         << "SYMBOL: ; at Line 8" << nl
         << "SYMBOL: return at Line 9" << nl
         << "NUMBER: 0 at Line 9" << nl
         << "SYMBOL: ; at Line 9" << nl
         << "SYMBOL: } at Line 10" << nl;
  EXPECT_EQ(expect.str(), test::to_string(tokens));
}
