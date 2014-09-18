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
    ";", "(", ")", "{", "}", "->",
    "and", "or", "not", "int", "def", "var",
    "if", "else", "while", "for", "break", "continue", "return"
  };
  return (std::find(begin(symbol_list), end(symbol_list), str) != end(symbol_list));
}

bool ignore(const std::string& str) {
  return (str == " " || str == "\n");
}

bool singleline_comment(const std::string& str) {
  bool inside = (str.back() == '\n' || str.find("\n") == std::string::npos);
  return (str.compare(0, 2, "~~") == 0 && inside);
}

bool multiline_comment(const std::string& str) {
  if (str.compare(0, 2, "{~") == 0) {
	int nest = 0;
	for (auto it = str.begin(); it + 1 != str.end(); it++) {
	  std::string tk(it, it+2);
	  if (tk == "{~") {
		nest++;
	  } else if(tk == "~}") {
		nest--;
	  }
	}
	bool closed = (nest == 0 && str.compare(str.size()-2, 2, "~}")) == 0;
	return (nest > 0 || closed);
  }
  return false;
}

bool comment(const std::string& str) {
  return (singleline_comment(str) || multiline_comment(str));
}

bool string_token(const std::string& str) {
  if (str.front() == '"') {
	bool escaped = false;
	for(auto it = str.begin() + 1; it != str.end(); it++) {
	  if (*it == '\\') {
		escaped = true;
	  } else if (*it == '"' && not escaped) {
		return it + 1 == str.end();
	  } else {
		escaped = false;
	  }
	}
  }
  return false;
}

TokenType match_type(std::string const& str) {
  if (str == "~}") return TokenType::SYMBOL;
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
  std::string str, code;
  while (std::getline(is, str)) {
    code += str + '\n';
  }
  TokenVector tokens;
  str.clear();
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

}  // namespace klang
