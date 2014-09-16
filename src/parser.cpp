#include "parser.hpp"

namespace klang {

Parser::Parser(TokenVector tokens)
    : tokens_(std::move(tokens)),
      current_(std::begin(tokens_))
{}

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

}  // namespace klang
