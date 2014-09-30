#include "gtest.h"

#include "parser.hpp"

TEST(parser, morbid) {
  std::stringstream is;
  is <<
R"(def main() -> (int) {
  x := (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( x ))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
  return x;
})";
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  EXPECT_TRUE(p.parse_translation_unit() != nullptr);
}
