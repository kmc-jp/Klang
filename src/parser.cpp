#include "parser.hpp"

#include "ast_data.hpp"

namespace klang {

Parser::Parser(TokenVector tokens)
    : tokens_(std::move(tokens)),
      current_(std::begin(tokens_))
{}

bool Parser::parse_symbol(const char* str) {
  if (current_type() == TokenType::SYMBOL &&
      current_string() == std::string{str}) {
    advance(1);
    return true;
  } else {
    return false;
  }
}

ast::IdentifierPtr Parser::parse_identifier() {
  if (current_type() == TokenType::IDENTIFIER) {
    advance(1);
    return make_unique<ast::IdentifierData>(current_string());
  } else {
    return nullptr;
  }
}

ast::TypePtr Parser::parse_type() {
  if (current_type() == TokenType::SYMBOL) {
    advance(1);
    return make_unique<ast::TypeData>(current_string());
  } else {
    return nullptr;
  }
}

ast::IntegerLiteralPtr Parser::parse_integer_literal() {
  if (current_type() == TokenType::NUMBER) {
    advance(1);
    return make_unique<ast::IntegerLiteralData>(current_string());
  } else {
    return nullptr;
  }
}

ast::CharacterLiteralPtr Parser::parse_character_literal() {
  if (current_type() == TokenType::CHARACTER) {
    advance(1);
    return make_unique<ast::CharacterLiteralData>(current_string());
  } else {
    return nullptr;
  }
}

ast::StringLiteralPtr Parser::parse_string_literal() {
  if (current_type() == TokenType::STRING) {
    advance(1);
    return make_unique<ast::StringLiteralData>(current_string());
  } else {
    return nullptr;
  }
}

ast::TranslationUnitPtr Parser::parse_translation_unit() {
  std::vector<ast::FunctionDefinitionPtr> functions;
  while (auto function = parse_function_definition()) {
    functions.push_back(std::move(function));
  }
  return make_unique<ast::TranslationUnitData>(std::move(functions));
}

ast::FunctionDefinitionPtr Parser::parse_function_definition() {
  const auto s = snapshot();
  if (parse_symbol("def")) {
    if (auto function_name = parse_identifier()) {
      if (parse_symbol("(")) {
        if (auto arguments = parse_argument_list()) {
          if (parse_symbol(")") && parse_symbol("->") && parse_symbol("(")) {
            if (auto return_type = parse_type()) {
              if (parse_symbol(")")) {
                if (auto function_body = parse_compound_statement()) {
                  return make_unique<ast::FunctionDefinitionData>(
                      std::move(function_name),
                      std::move(arguments),
                      std::move(return_type),
                      std::move(function_body));
                }
              }
            }
          }
        }
      }
    }
  }
  rewind(s);
  return nullptr;
}

ast::ArgumentListPtr Parser::parse_argument_list() {
  std::vector<ast::ArgumentPtr> arguments;
  if (auto first_argument = parse_argument()) {
    arguments.push_back(std::move(first_argument));
    while (true) {
      const auto s = snapshot();
      if (parse_symbol(",")) {
        if (auto argument = parse_argument()) {
          arguments.push_back(std::move(argument));
          continue;
        }
      }
      rewind(s);
      break;
    }
  }
  return make_unique<ast::ArgumentListData>(std::move(arguments));
}

ast::ArgumentPtr Parser::parse_argument() {
  const auto s = snapshot();
  if (auto argument_type = parse_type()) {
    if (auto argument_name = parse_identifier()) {
      return make_unique<ast::ArgumentData>(std::move(argument_type),
                                            std::move(argument_name));
    }
  }
  rewind(s);
  return nullptr;
}

ast::StatementPtr Parser::parse_statement() {
  if (auto statement = parse_compound_statement()) {
    return std::move(statement);
  } else if (auto statement = parse_if_statement()){
    return std::move(statement);
  } else if (auto statement = parse_while_statement()){
    return std::move(statement);
  } else if (auto statement = parse_for_statement()){
    return std::move(statement);
  } else if (auto statement = parse_return_statement()){
    return std::move(statement);
  } else if (auto statement = parse_break_statement()){
    return std::move(statement);
  } else if (auto statement = parse_continue_statement()){
    return std::move(statement);
  } else if (auto statement = parse_variable_definition_statement()){
    return std::move(statement);
  } else if (auto statement = parse_expression_statement()){
    return std::move(statement);
  }
  return nullptr;
}

ast::CompoundStatementPtr Parser::parse_compound_statement() {
  std::vector<ast::StatementPtr> statements;
  const auto s = snapshot();
  if (parse_symbol("{")) {
    while (auto statement = parse_statement()) {
      statements.push_back(std::move(statement));
    }
    if (parse_symbol("}")) {
      return make_unique<ast::CompoundStatementData>(std::move(statements));
    }
  }
  rewind(s);
  return nullptr;
}

ast::IfStatementPtr Parser::parse_if_statement() {
  const auto s = snapshot();
  if (parse_symbol("if") && parse_symbol("(")) {
    if (auto condition = parse_expression()) {
      if (parse_symbol(")")) {
        if (auto compound_statement = parse_compound_statement()) {
          return make_unique<ast::IfStatementData>(
              std::move(condition),
              std::move(compound_statement),
              parse_else_statement());
        }
      }
    }
  }
  rewind(s);
  return nullptr;
}

ast::IfStatementPtr Parser::parse_else_statement() {
  const auto s = snapshot();
  if (parse_symbol("else")) {
    if (auto else_if_statement = parse_if_statement()) {
      return std::move(else_if_statement);
    } else if (auto compound_statement = parse_compound_statement()) {
      return make_unique<ast::ElseStatementData>(std::move(compound_statement));
    }
  }
  rewind(s);
  return nullptr;
}

ast::WhileStatementPtr Parser::parse_while_statement() {
  const auto s = snapshot();
  if (parse_symbol("while") && parse_symbol("(")) {
    if (auto condition = parse_expression()) {
      if (parse_symbol(")")) {
        if (auto compound_statement = parse_compound_statement()) {
          return make_unique<ast::WhileStatementData>(
              std::move(condition),
              std::move(compound_statement));
        }
      }
    }
  }
  rewind(s);
  return nullptr;
}

ast::ForStatementPtr Parser::parse_for_statement() {
  const auto s = snapshot();
  if (parse_symbol("for") && parse_symbol("(")) {
    auto init_expression = parse_expression();
    if (parse_symbol(";")) {
      auto cond_expression = parse_expression();
      if (parse_symbol(";")) {
        auto reinit_expression = parse_expression();
        if (parse_symbol(")")) {
          if (auto compound_statement = parse_compound_statement()) {
            return make_unique<ast::ForStatementData>(
                std::move(init_expression),
                std::move(cond_expression),
                std::move(reinit_expression),
                std::move(compound_statement));
          }
        }
      }
    }
  }
  rewind(s);
  return nullptr;
}

ast::ReturnStatementPtr Parser::parse_return_statement() {
  const auto s = snapshot();
  if (parse_symbol("return")) {
    if (auto return_value = parse_expression()) {
      if (parse_symbol(";")) {
        return make_unique<ast::ReturnStatementData>(std::move(return_value));
      }
    }
  }
  rewind(s);
  return nullptr;
}

TokenType Parser::current_type() const {
  return is_eof() ? TokenType::IGNORE : current_->type();
}

std::string Parser::current_string() const {
  static const std::string empty_string{""};
  return is_eof() ? empty_string : current_->str();
}

bool Parser::is_eof() const {
  using std::end;
  return current_ == end(tokens_);
}

bool Parser::advance(int count) {
  using std::begin;
  using std::end;
  const auto b = begin(tokens_);
  const auto e = end(tokens_);
  while (count < 0) {
    if (current_ != b) {
      ++count;
      --current_;
    } else {
      return false;
    }
  }
  while (0 < count) {
    if (current_ != e) {
      --count;
      ++current_;
    } else {
      return false;
    }
  }
  return true;
}

auto Parser::snapshot() const -> Pointer {
  return current_;
}

void Parser::rewind(Pointer p) {
  current_ = p;
}

}  // namespace klang
