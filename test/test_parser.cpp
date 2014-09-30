#include "gtest.h"

#include "parser.hpp"

TEST(parser, morbid) {
  std::stringstream is;
  is << "def main() -> (int) {\n"
     << "  x := (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( x ))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));\n"
     << "  return x;\n"
     << "}\n";
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  EXPECT_TRUE(p.parse_translation_unit() != nullptr);
}
