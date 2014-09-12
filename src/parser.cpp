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

}  // namespace klang
