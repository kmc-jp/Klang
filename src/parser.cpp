#include "parser.hpp"

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
