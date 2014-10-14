#include "lexer.hpp"

#include <cctype>
#include <algorithm>
#include <iterator>
#include <vector>

namespace klang {
namespace {
  using const_iterator = std::string::const_iterator;
}

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

bool identifier(const_iterator head, const_iterator tail) {
  if (head == tail || !alphabet_or_bar(*head)) {
    return false;
  }
  for (auto it(head); it != tail; ++it) {
    if (!alphabet_or_bar(*it) && !decimal_digit(*it)) {
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

bool symbol(const_iterator head, const_iterator tail) {
  using std::begin;
  using std::end;
  std::string const str(head, tail);
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

bool singleline_comment(const_iterator head, const_iterator tail) {
  using std::begin;
  using std::end;
  if(std::equal(head, std::next(head, 2), "~~")) {
      return std::find(head, tail, '\n') == std::prev(tail);
  }
  return false;
}

bool multiline_comment(const_iterator head, const_iterator tail) {
  using std::begin;
  using std::end;
  if (std::equal(head, std::next(head, 2), "{~")) {
    int nest = 0;
    for(auto it = head; std::next(it) != tail; ++it) {
      std::string tk(it, std::next(it, 2));
      if (tk == "{~") {
        ++nest;
      } else if(tk == "~}") {
        --nest;
      }
    }
    bool closed = nest == 0 && std::equal(std::prev(tail, 2), std::prev(tail), "~}");
    return (nest > 0 || closed);
  }
  return false;
}

bool comment(const_iterator head, const_iterator tail) {
  return (singleline_comment(head, tail) || multiline_comment(head, tail));
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

TokenType match_type(const_iterator head, const_iterator tail) {
  if (comment(head, tail)) return TokenType::IGNORE;
  if (symbol(head, tail)) return TokenType::SYMBOL;
  if (identifier(head, tail)) return TokenType::IDENTIFIER;
  if (decimal_integer(head, tail)) return TokenType::NUMBER;
  if (string_token(head, tail)) return TokenType::STRING;
  if (ignore(head, tail)) return TokenType::IGNORE;
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
  using std::begin;
  using std::end;
  std::string const code(std::string{std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()} + '\n');
  // ファイルの末尾が改行で終わっているほうが処理しやすい。
  TokenVector tokens;
  TokenType prev = TokenType::UNKNOWN;
  const_iterator head(begin(code));
  int line = 1;
  for (auto it(begin(code)); it != end(code); ++it) {
    TokenType next = match_type(head, std::next(it));
    if (prev != TokenType::UNKNOWN && next == TokenType::UNKNOWN) {
      if (prev != TokenType::IGNORE) {
        tokens.push_back(Token(prev, extract_string(head, it), line));
      }
      head = it;
      prev = match_type(head, std::next(head));
    } else {
      prev = next;
    }
    if (*it == '\n') ++line;
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
