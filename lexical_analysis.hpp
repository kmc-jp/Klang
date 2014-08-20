#ifndef KMC_KLANG_LEXICAL_ANALYSIS_HPP
#define KMC_KLANG_LEXICAL_ANALYSIS_HPP

#include <fstream>
#include <string>
#include <vector>

namespace klang {

enum class TokenType {
  IDENTIFIER,
  DIGIT,
  RESERVED,
  CHARACTER,
  STRING
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

TokenVector LexicalAnalysis(std::ifstream& is);

}  // klang

#endif  // KMC_KLANG_LEXICAL_ANALYSIS_HPP
