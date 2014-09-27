#ifndef KMC_KLANG_LEXER_HPP
#define KMC_KLANG_LEXER_HPP

#include <istream>
#include <string>
#include <vector>

namespace klang {

enum class TokenType {
  IDENTIFIER,
  NUMBER,
  SYMBOL,
  CHARACTER,
  STRING,
  IGNORE,
  UNKNOWN
};

class Token {
 public:
  Token();
  Token(TokenType type, const std::string& str, int line);
  TokenType type() const;
  std::string str() const;
  int line() const;
 private:
  TokenType type_;
  std::string str_;
  int line_;
};

bool operator==(Token const& lhs, Token const& rhs);
bool operator!=(Token const& lhs, Token const& rhs);

typedef std::vector<Token> TokenVector;

TokenVector tokenize(std::istream& is);

}  // namespace klang

#endif  // KMC_KLANG_LEXER_HPP
