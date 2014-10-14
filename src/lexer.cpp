#include "lexer.hpp"

#include <cctype>
#include <algorithm>
#include <iterator>
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
    ";", "(", ")", "{", "}", "->", "~}",
    "and", "or", "not", "int", "def", "var",
    "if", "else", "while", "for", "break", "continue", "return"
  };
  return (std::find(begin(symbol_list), end(symbol_list), str) != end(symbol_list));
}

bool ignore(const std::string& str) {
  if(str.size() != 1) return false;
  return std::isspace(str[0]);
}

bool singleline_comment(const std::string& str) {
  using std::begin;
  using std::end;
  bool inside = (str.back() == '\n' || str.find("\n") == std::string::npos);
  return std::equal(begin(str), std::next(begin(str), 2), "~~") && inside;
}

bool multiline_comment(const std::string& str) {
  using std::begin;
  using std::end;
  if (std::equal(begin(str), std::next(begin(str), 2), "{~")) {
    int nest = 0;
    for(auto it = begin(str); std::next(it) != end(str); ++it) {
      std::string tk(it, std::next(it, 2));
      if (tk == "{~") {
        ++nest;
      } else if(tk == "~}") {
        --nest;
      }
    }
    bool closed = (nest == 0 && std::equal(std::prev(end(str), 2), std::prev(end(str)), "~}"));
    return (nest > 0 || closed);
  }
  return false;
}

bool comment(const std::string& str) {
  return (singleline_comment(str) || multiline_comment(str));
}

bool string_token(const std::string& str) {
  using std::begin;
  using std::end;
  if (str.front() == '"') {
    bool escaped = false;
    for(auto it = std::next(begin(str)); it != end(str); ++it) {
      if (*it == '\\') {
        escaped = true;
      } else if (*it == '"' && (!escaped)) {
        return std::next(it) == end(str);
      } else {
        escaped = false;
      }
    }
  }
  return false;
}

TokenType match_type(std::string const& str) {
  if (comment(str)) return TokenType::IGNORE;
  if (symbol(str)) return TokenType::SYMBOL;
  if (identifier(str)) return TokenType::IDENTIFIER;
  if (decimal_integer(str)) return TokenType::NUMBER;
  if (string_token(str)) return TokenType::STRING;
  if (ignore(str)) return TokenType::IGNORE;
  return TokenType::UNKNOWN;
}

std::string extract_string(const std::string& str) {
  if (str.front() == '"') {
    bool escaped = false;
    std::string new_str;
    for(auto c : str) {
      if (escaped) {
        if(c == '"') new_str.push_back('"');
        if(c == 'n') new_str.push_back('\n');
        escaped = false;
      } else if (c == '\\') {
        escaped = true;
      } else if (c != '"') {
        new_str.push_back(c);
      }
    }
    return new_str;
  }
  return str;
}

TokenVector tokenize(std::istream& is) {
  std::string code{std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()};
  TokenVector tokens;
  std::string str;
  TokenType prev = TokenType::UNKNOWN;
  int line = 1;
  for (char c : code) {
    TokenType next = match_type(str + c);
    if (prev != TokenType::UNKNOWN && next == TokenType::UNKNOWN) {
      if (prev != TokenType::IGNORE) {
        tokens.push_back(Token(prev, extract_string(str), line));
      }
      str = c;
      prev = match_type(str);
    } else {
      str += c;
      prev = next;
    }
    if (c == '\n') ++line;
  }
  return tokens;
}

bool operator==(Token const& lhs, Token const& rhs) {
  return lhs.type() == rhs.type()
      && lhs.str()  == rhs.str()
      && lhs.line() == rhs.line();
}
bool operator!=(Token const& lhs, Token const& rhs) {
  return !( lhs == rhs );
}

}  // namespace klang
