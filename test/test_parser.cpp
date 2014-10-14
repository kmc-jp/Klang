#include "gtest.h"

#include "ast_data.hpp"
#include "parser.hpp"

TEST(parser, emptySource) {
  std::stringstream is;
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  auto ptu = p.parse_translation_unit();
  ASSERT_TRUE(ptu != nullptr);
}

TEST(parser, onlyReturn) {
  std::stringstream is;
  is <<
R"(def main() -> (int) {
  return 0;
})";
  auto tokens = klang::tokenize(is);
  klang::Parser p(tokens);
  ASSERT_TRUE(p.parse_translation_unit() != nullptr);
  auto tu = p.parse_translation_unit();
  auto dy = dynamic_cast<klang::ast::TranslationUnitData*>(tu.get());
  ASSERT_TRUE(dy != nullptr);
  EXPECT_EQ(1u, dy->functions().size());
}

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
