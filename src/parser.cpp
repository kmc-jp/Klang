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
  }
  return false;
}

ast::IdentifierPtr Parser::parse_identifier() {
  if (current_type() == TokenType::IDENTIFIER) {
    advance(1);
    return make_unique<ast::IdentifierData>(current_string());
  }
  return nullptr;
}

ast::TypePtr Parser::parse_type() {
  if (current_type() == TokenType::SYMBOL) {
    advance(1);
    return make_unique<ast::TypeData>(current_string());
  }
  return nullptr;
}

ast::IntegerLiteralPtr Parser::parse_integer_literal() {
  if (current_type() == TokenType::NUMBER) {
    advance(1);
    return make_unique<ast::IntegerLiteralData>(current_string());
  }
  return nullptr;
}

ast::CharacterLiteralPtr Parser::parse_character_literal() {
  if (current_type() == TokenType::CHARACTER) {
    advance(1);
    return make_unique<ast::CharacterLiteralData>(current_string());
  }
  return nullptr;
}

ast::StringLiteralPtr Parser::parse_string_literal() {
  if (current_type() == TokenType::STRING) {
    advance(1);
    return make_unique<ast::StringLiteralData>(current_string());
  }
  return nullptr;
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

ast::ElseStatementPtr Parser::parse_else_statement() {
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

ast::BreakStatementPtr Parser::parse_break_statement() {
  const auto s = snapshot();
  if (parse_symbol("break") && parse_symbol(";")) {
    return make_unique<ast::BreakStatementData>();
  }
  rewind(s);
  return nullptr;
}

ast::ContinueStatementPtr Parser::parse_continue_statement() {
  const auto s = snapshot();
  if (parse_symbol("continue") && parse_symbol(";")) {
    return make_unique<ast::ContinueStatementData>();
  }
  rewind(s);
  return nullptr;
}

ast::VariableDefinitionStatementPtr
Parser::parse_variable_definition_statement() {
  const auto s = snapshot();
  if (auto variable_definition = parse_variable_definition()) {
    if (parse_symbol(";")) {
      return make_unique<ast::VariableDefinitionStatementData>(
          std::move(variable_definition));
    }
  }
  rewind(s);
  return nullptr;
}

ast::VariableDefinitionPtr Parser::parse_variable_definition() {
  const auto s = snapshot();
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
  rewind(s);
  return nullptr;
}

ast::ExpressionStatementPtr Parser::parse_expression_statement() {
  const auto s = snapshot();
  auto expression = parse_expression();
  if (parse_symbol(";")) {
    return make_unique<ast::ExpressionStatementData>(std::move(expression));
  }
  rewind(s);
  return nullptr;
}

ast::ExpressionPtr Parser::parse_expression() {
  return parse_assign_expression();
}

ast::AssignExpressionPtr Parser::parse_assign_expression() {
  if (auto lhs_expression = parse_or_expression()) {
    const auto s = snapshot();
    if (parse_symbol(":=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::AssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if(parse_symbol(":+=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::AddAssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if(parse_symbol(":-=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::SubtractAssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if(parse_symbol(":*=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::MultiplyAssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if(parse_symbol(":/=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::DivideAssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if(parse_symbol(":%=")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::ModuloAssignExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    }
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::OrExpressionPtr Parser::parse_or_expression() {
  if (auto lhs_expression = parse_and_expression()) {
    const auto s = snapshot();
    if (parse_symbol("or")) {
      if (auto rhs_expression = parse_or_expression()) {
        return make_unique<ast::OrExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
    }
    rewind(s);
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::AndExpressionPtr Parser::parse_and_expression() {
  if (auto lhs_expression = parse_comparative_expression()) {
    const auto s = snapshot();
    if (parse_symbol("and")) {
      if (auto rhs_expression = parse_and_expression()) {
        return make_unique<ast::AndExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
    }
    rewind(s);
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::ComparativeExpressionPtr Parser::parse_comparative_expression() {
  if (auto lhs_expression = parse_additive_expression()) {
    const auto s = snapshot();
    if (parse_symbol("=")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::EqualExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("=/")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::NotEqualExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("<")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::LessExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol(">")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::GreaterExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("<=")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::LessOrEqualExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol(">=")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::GreaterOrEqualExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    }
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::AdditiveExpressionPtr Parser::parse_additive_expression() {
  if (auto lhs_expression = parse_multiplicative_expression()) {
    const auto s = snapshot();
    if (parse_symbol("+")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::AddExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("-")) {
      if (auto rhs_expression = parse_additive_expression()) {
        return make_unique<ast::SubtractExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    }
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::MultiplicativeExpressionPtr Parser::parse_multiplicative_expression() {
  if (auto lhs_expression = parse_unary_expression()) {
    const auto s = snapshot();
    if (parse_symbol("*")) {
      if (auto rhs_expression = parse_multiplicative_expression()) {
        return make_unique<ast::MultiplyExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("/")) {
      if (auto rhs_expression = parse_multiplicative_expression()) {
        return make_unique<ast::DivideExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    } else if (parse_symbol("%")) {
      if (auto rhs_expression = parse_multiplicative_expression()) {
        return make_unique<ast::ModuloExpressionData>(
            std::move(lhs_expression), std::move(rhs_expression));
      }
      rewind(s);
    }
    return std::move(lhs_expression);
  }
  return nullptr;
}

ast::UnaryExpressionPtr Parser::parse_unary_expression() {
  const auto s = snapshot();
  if (parse_symbol("not")) {
    if (auto unary_expression = parse_unary_expression()) {
      return make_unique<ast::NotExpressionData>(std::move(unary_expression));
    }
    rewind(s);
  } else if (parse_symbol("~")) {
    if (auto unary_expression = parse_unary_expression()) {
      return make_unique<ast::MinusExpressionData>(std::move(unary_expression));
    }
    rewind(s);
  } else if (auto postfix_expression = parse_postfix_expression()) {
    return std::move(postfix_expression);
  }
  return nullptr;
}

ast::PostfixExpressionPtr Parser::parse_postfix_expression() {
  if (auto postfix_expression = parse_function_call_expression()) {
    return std::move(postfix_expression);
  } else if (auto primary_expression = parse_primary_expression()) {
    return std::move(primary_expression);
  }
  return nullptr;
}

ast::FunctionCallExpressionPtr Parser::parse_function_call_expression() {
  const auto s = snapshot();
  if (auto function_name = parse_identifier()) {
    if (parse_symbol("(")) {
      if (auto parameter_list = parse_parameter_list()) {
        if (parse_symbol(")")) {
          return make_unique<ast::FunctionCallExpressionData>(
              std::move(function_name), std::move(parameter_list));
        }
      }
    }
  }
  rewind(s);
  return nullptr;
}

ast::ParameterListPtr Parser::parse_parameter_list() {
  std::vector<ast::ParameterPtr> parameters;
  if (auto first_parameter = parse_parameter()) {
    parameters.push_back(std::move(first_parameter));
    while (true) {
      const auto s = snapshot();
      if (parse_symbol(",")) {
        if (auto parameter = parse_parameter()) {
          parameters.push_back(std::move(parameter));
          continue;
        }
      }
      rewind(s);
      break;
    }
  }
  return make_unique<ast::ParameterListData>(std::move(parameters));
}

ast::ParameterPtr Parser::parse_parameter() {
  if (auto expression = parse_expression()) {
    return make_unique<ast::ParameterData>(std::move(expression));
  }
  return nullptr;
}

ast::PrimaryExpressionPtr Parser::parse_primary_expression() {
  const auto s = snapshot();
  if (parse_symbol("(")) {
    if (auto expression = parse_expression()) {
      if (parse_symbol(")")) {
        return make_unique<ast::ParenthesizedExpressionData>(
            std::move(expression));
      }
    }
    rewind(s);
  } else if (auto identifier = parse_identifier()) {
    return make_unique<ast::IdentifierExpressionData>(
        std::move(identifier));
  } else if (auto integer_literal = parse_integer_literal()) {
    return make_unique<ast::IntegerLiteralExpressionData>(
        std::move(integer_literal));
  } else if (auto character_literal = parse_character_literal()) {
    return make_unique<ast::CharacterLiteralExpressionData>(
        std::move(character_literal));
  } else if (auto string_literal = parse_string_literal()) {
    return make_unique<ast::StringLiteralExpressionData>(
        std::move(string_literal));
  }
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
