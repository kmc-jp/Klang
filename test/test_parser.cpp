#include "gtest.h"

#include "ast_data.hpp"
#include "parser.hpp"

TEST(parser, emptySource) {
  std::stringstream is;
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
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
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  klang::Parser p(tokens);
  auto tu = p.parse_translation_unit();
  auto tud = dynamic_cast<klang::ast::TranslationUnitData*>(tu.get());
  ASSERT_TRUE(tud != nullptr);
  auto const& funcs = tud->functions();
  ASSERT_EQ(1u, funcs.size());

  auto const& func = funcs[0];
  auto fdD = dynamic_cast<klang::ast::FunctionDefinitionData*>(func.get());
  ASSERT_TRUE(fdD != nullptr);

  { // 関数名がmain である
    auto const& idPtr = fdD->name();
    auto idD = dynamic_cast<klang::ast::IdentifierData*>(idPtr.get());
    ASSERT_TRUE(idD != nullptr);
    EXPECT_EQ("main", idD->value());
  }
  { // 引数リストが空である
    auto const& alPtr = fdD->arguments();
    auto alD = dynamic_cast<klang::ast::ArgumentListData*>(alPtr.get());
    ASSERT_TRUE(alD != nullptr);
    EXPECT_EQ(0u, alD->arguments().size());
  }
  { // return type がint である
    auto const& tyPtr = fdD->return_type();
    auto tyD = dynamic_cast<klang::ast::TypeData*>(tyPtr.get());
    ASSERT_TRUE(tyD != nullptr);
    EXPECT_EQ("int", tyD->value());
  }
  { // 関数の中身がreturn 一文である
    auto const& csPtr = fdD->body();
    auto csD = dynamic_cast<klang::ast::CompoundStatementData*>(csPtr.get());
    ASSERT_TRUE(csD != nullptr);
    auto const& statements = csD->statements();
    ASSERT_EQ(1u, statements.size()); // 一文である

    auto const& statementPtr = statements[0];
    auto statementD = dynamic_cast<klang::ast::ReturnStatementData*>(statementPtr.get());
    ASSERT_TRUE(statementD != nullptr); // それがreturn 文である

    auto const& expPtr = statementD->return_value();
    auto ileD = dynamic_cast<klang::ast::IntegerLiteralExpressionData*>(expPtr.get());
    ASSERT_TRUE(ileD != nullptr); // return の返すものが数値リテラル式である

    auto const& ilPtr = ileD->expression();
    auto ilD = dynamic_cast<klang::ast::IntegerLiteralData*>(ilPtr.get());
    ASSERT_TRUE(ilD != nullptr);

    ASSERT_EQ("0", ilD->value()); // それが0 である
  }
}

TEST(parser, morbid) {
  std::stringstream is;
  is <<
R"(def main() -> (int) {
  x := (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( x ))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
  return x;
})";
  klang::TokenVector tokens;
  bool success;
  std::tie(success, tokens) = klang::tokenize(is);
  EXPECT_TRUE(success);
  klang::Parser p(tokens);
  EXPECT_TRUE(p.parse_translation_unit() != nullptr);
}
