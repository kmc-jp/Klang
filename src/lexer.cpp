#include "lexer.hpp"

#include <cctype>
#include <algorithm>
#include <vector>

namespace klang {

Token::Token()
  : type_(TokenType::UNKNOWN), str_(), line_(-1)
{}

Token::Token(TokenType type, const std::string& str, int line)
  : type_(type), str_(str), line_(line)
{}

TokenType Token::type() const { return type_; }
std::string Token::str() const { return str_; }
int Token::line() const { return line_; }


bool alphabet(char c) {
  return std::isalpha(c);
}

bool alphabet_or_bar(char c) {
  return (c == '_' || alphabet(c));
}

bool nonzero_digit(char c) {
  return (c >= '1' && c <= '9');
}

bool decimal_digit(char c) {
  return std::isdigit(c);
}

bool identifier(const std::string& str) {
  if (str.empty() || !alphabet_or_bar(str.front())) {
    return false;
  }
  for (char c : str) {
    if (!alphabet_or_bar(c) && !decimal_digit(c)) {
      return false;
    }
  }
  return true;
}

bool decimal_integer(const std::string& str) {
  if (str == "0") return true;
  if (str.empty() || !nonzero_digit(str.front())) {
    return false;
  }
  for (char c : str) {
    if (!decimal_digit(c)) {
      return false;
    }
  }
  return true;
}

bool symbol(const std::string& str) {
  using std::begin;
  using std::end;
  static std::vector<std::string> const symbol_list = {
    "~", "+", "-", "*", "/", "%",
    ":=", ":+=", ":-=", ":*=", ":/=", ":%=",
    "=", "=/", "<", ">", "<=", ">=",
    ";", "(", ")", "{", "}",
    "and", "or", "not", "int", "def", "var",
    "if", "else", "while", "for", "break", "continue", "return"
  };
  return (std::find(begin(symbol_list), end(symbol_list), str) != end(symbol_list));
}

bool ignore(const std::string& str) {
  return (str == " " || str == "\n");
}

TokenType match_type(std::string const& str) {
  if (symbol(str)) return TokenType::SYMBOL;
  if (identifier(str)) return TokenType::IDENTIFIER;
  if (decimal_integer(str)) return TokenType::NUMBER;
  if (ignore(str)) return TokenType::IGNORE;
  return TokenType::UNKNOWN;
}

TokenVector tokenize(std::istream& is) {
  std::string str, code;
  while (std::getline(is, str)) {
    code += str + '\n';
  }
  TokenVector tokens;
  str.clear();
  TokenType prev = TokenType::UNKNOWN;
  int line = 0;
  for (char c : code) {
    if (c == '\n') ++line;
    TokenType next = match_type(str + c);
    if (prev != TokenType::UNKNOWN && next == TokenType::UNKNOWN) {
      if (prev != TokenType::IGNORE) {
        tokens.push_back(Token(prev, str, line));
      }
      str = c;
      prev = match_type(str);
    } else {
      str += c;
      prev = next;
    }
  }
  return tokens;
}

}  // namespace klang
