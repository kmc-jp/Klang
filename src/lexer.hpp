#ifndef KMC_KLANG_LEXER_HPP
#define KMC_KLANG_LEXER_HPP

#include <fstream>
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

typedef std::vector<Token> TokenVector;

TokenVector tokenize(std::ifstream& is);

}  // namespace klang

#endif  // KMC_KLANG_LEXER_HPP