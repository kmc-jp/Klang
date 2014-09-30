#include "gtest.h"

#include "parser.hpp"

TEST(parser, emptySource) {
  std::stringstream is;
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  auto ptu = p.parse_translation_unit();
  ASSERT_TRUE(ptu != nullptr);
}

TEST(parser, morbid) {
  std::stringstream is;
  std::string nl("\n");
  is << "def main() -> (int) {" << nl
     << "  x := (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( x ))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));" << nl
     << "  return x;" << nl
     << "}" << nl;
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  EXPECT_TRUE(p.parse_translation_unit() != nullptr);
}
