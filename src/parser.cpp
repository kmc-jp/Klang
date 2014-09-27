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
