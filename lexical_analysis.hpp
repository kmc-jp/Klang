#ifndef KMC_KLANG_LEXICAL_ANALYSIS_HPP
#define KMC_KLANG_LEXICAL_ANALYSIS_HPP

#include <fstream>
#include <string>
#include <vector>

namespace klang {

enum class TokenType {
  IDENTIFIER,
  DIGIT,
  SYMBOL,
  INT,
  RETURN,
  EOF
};

class Token {
 public:
  Token();
  // 以下適切にコンストラクタを追加。
  TokenType type() const;
  std::string str() const;
  int number() const;
  int line() const;
 private:
  TokenType type_;
  std::string str_;
  int number_;
  int line_;
};

class TokenVector {
 public:
  bool unget_token(int times);
  bool next_token();
  bool push_token(Token token);
  Token get_token() const;
  TokenType current_type() const;
  std::string current_string() const;
  int current_value() const;
  int current_index() const;
  bool set_index(int index);
  bool print_tokens() const;
 private:
  std::vector<Token> tokens_;
  int current_index_;
};

TokenVector LexicalAnalysis(std::ifstream& is);

}  // klang

#endif  // KMC_KLANG_LEXICAL_ANALYSIS_HPP
