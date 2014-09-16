#include "parser.hpp"

#include <cassert>
#include "ast_data.hpp"

namespace klang {

Parser::Parser(TokenVector tokens)
    : tokens_(std::move(tokens)),
      current_(std::begin(tokens_))
{}

bool Parser::parse_symbol(const char* str) {
  if (current_type() == TokenType::SYMBOL &&
      current_string() == std::string(str)) {
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
  if (current_type() == TokenType::IDENTIFIER) {
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
  assert(is_eof());
  assert(0 < functions.size());
  return make_unique<ast::TranslationUnitData>(std::move(functions));
}

ast::FunctionDefinitionPtr Parser::parse_function_definition() {
  const auto snapshot = make_snapshot();
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
  rewind(snapshot);
  return nullptr;
}

ast::ArgumentListPtr Parser::parse_argument_list() {
  std::vector<ast::ArgumentPtr> arguments;
  if (auto first_argument = parse_argument()) {
    arguments.push_back(std::move(first_argument));
    while (true) {
      const auto snapshot = make_snapshot();
      if (parse_symbol(",")) {
        if (auto argument = parse_argument()) {
          arguments.push_back(std::move(argument));
          continue;
        }
      }
      rewind(snapshot);
      break;
    }
  }
  return make_unique<ast::ArgumentListData>(std::move(arguments));
}

ast::ArgumentPtr Parser::parse_argument() {
  const auto snapshot = make_snapshot();
  if (auto argument_type = parse_type()) {
    if (auto argument_name = parse_identifier()) {
      return make_unique<ast::ArgumentData>(std::move(argument_type),
                                            std::move(argument_name));
    }
  }
  rewind(snapshot);
  return nullptr;
}

ast::CompoundStatementPtr Parser::parse_compound_statement() {
  const auto snapshot = make_snapshot();
  std::vector<ast::StatementPtr> statements;
  if (parse_symbol("{")) {
    while (auto statement = parse_statement()) {
      statements.push_back(std::move(statement));
    }
    if (parse_symbol("}")) {
      return make_unique<ast::CompoundStatementData>(std::move(statements));
    }
  }
  rewind(snapshot);
  return nullptr;
}

ast::ExpressionStatementPtr Parser::parse_expression_statement() {
  const auto snapshot = make_snapshot();
  auto expression = parse_expression();
  if (parse_symbol(";")) {
    return make_unique<ast::ExpressionStatementData>(std::move(expression));
  }
  rewind(snapshot);
  return nullptr;
}

ast::VariableDefinitionStatementPtr
Parser::parse_variable_definition_statement() {
  const auto snapshot = make_snapshot();
  if (auto variable_definition = parse_variable_definition()) {
    if (parse_symbol(";")) {
      return make_unique<ast::VariableDefinitionStatementData>(
          std::move(variable_definition));
    }
  }
  rewind(snapshot);
  return nullptr;
}

ast::VariableDefinitionPtr Parser::parse_variable_definition() {
  const auto snapshot = make_snapshot();
  if (parse_symbol("def")) {
    if (auto type_name = parse_type()) {
      const bool is_mutable = parse_symbol("var");
      if (auto variable_name = parse_identifier()) {
        if (parse_symbol(":=")) {
          if (auto expression = parse_expression()) {
            return make_unique<ast::VariableDefinitionData>(
                std::move(type_name),
                is_mutable,
                std::move(variable_name),
                std::move(expression));
          }
        }
      }
    }
  }
  rewind(snapshot);
  return nullptr;
}

ast::IfStatementPtr Parser::parse_if_statement() {
  const auto snapshot = make_snapshot();
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
  rewind(snapshot);
  return nullptr;
}

TokenType Parser::current_type() const {
  return is_eof() ? TokenType::IGNORE : current_->type();
}

std::string Parser::current_string() const {
  static const std::string empty_string("");
  return is_eof() ? empty_string : current_->str();
}

bool Parser::is_eof() const {
  using std::end;
  return current_ == end(tokens_);
}

bool Parser::advance(int count) {
  using std::begin;
  using std::end;
  while (count < 0) {
    if (current_ != begin(tokens_)) {
      ++count;
      --current_;
    } else {
      return false;
    }
  }
  while (0 < count) {
    if (current_ != end(tokens_)) {
      --count;
      ++current_;
    } else {
      return false;
    }
  }
  return true;
}

TokenVector::const_iterator Parser::make_snapshot() const {
  return current_;
}

void Parser::rewind(TokenVector::const_iterator snapshot) {
  current_ = snapshot;
}

}  // namespace klang
