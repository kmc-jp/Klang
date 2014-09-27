#include "parser.hpp"

namespace klang {

Parser::Parser(TokenVector tokens)
    : tokens_(std::move(tokens)),
      current_(std::begin(tokens_))
{}

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

}  // namespace klang
