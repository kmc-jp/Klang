#include "lexical_analysis.hpp"

#include <set>

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


// <cctype>のstd::isalphaを使うのはどうか。
bool alphabet(char c) {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// 個人的にalphabet_or_barあたりに留めたい。
// _で終わるpublicな識別子には違和感がある。
bool alphabet_(char c) {
  return (c == '_' || alphabet(c));
}

bool nonzero_digit(char c) {
  return (c >= '1' && c <= '9');
}

// <cctype>のstd::isdigitを使うのはどうか。
bool decimal_digit(char c) {
  return (c >= '0' && c <= '9');
}

bool identifier(const std::string& str) {
  if (str.empty() || !alphabet_(str.front())) {
    return false;
  }
  for (char c : str) {
    if (!alphabet_(c) && !decimal_digit(c)) {
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

// reservedだと"予約済み"の印象があるので、代わりにkeywordを使うのはどうか。
bool reserved(const std::string& str) {
  // static constな定数にしておくと良いのでは。
  std::set<std::string> reserved_list = {
    // ここの初期化は長すぎるように感じた。
    // keywordとsymbolに分けてはどうか。
    // もちろん、","から"}"までがsymbol、"and"から"continue"までがkeywordだ。
    ";", ":=", ":+=", ":-=", ":*=", ":/=", ":%=", "*", "/", "%", "+", "-",
    "=", "<", ">", "<=", ">=", "/=", "(", ")", "{", "}", "and", "or",
    "not", "xor", "int", "def", "var", "return",
    "if", "else", "while", "for", "break", "continue"
  };
  // setのfindメンバを使うよりもvectorと<algorithm>のfindを使うほうが自然では。
  // 特筆すべき事由がない限り、vectorを選択すべき。
  // メンバ関数形式の.end()ではなく、グローバルなend()を使うほうがC++11ライク。
  // 事前にスコープ内でusing std::end;するのを忘れずに。
  return (reserved_list.find(str) != reserved_list.end());
}

// <cctype>のstd::isspaceを使うのはどうか。
// 少なくとも'\t', '\v', '\r', '\f'のチェックが足りない。
bool ignore(const std::string& str) {
  return (str == " " || str == "\n");
}

TokenType match_type(std::string str) {
  if (reserved(str)) return TokenType::RESERVED;
  if (identifier(str)) return TokenType::IDENTIFIER;
  if (decimal_integer(str)) return TokenType::DIGIT;
  if (ignore(str)) return TokenType::IGNORE;
  return TokenType::UNKNOWN;
}
// ここまでのユーティリティ関数は他のファイルで利用することはないだろうから、無名名前空間で囲っておくべき。

TokenVector LexicalAnalysis(std::ifstream& is) {
  std::string str, code;
  while (std::getline(is, str)) {
    code += str + '\n';
  }
  TokenVector tokens;
  // str.clear();
  str = "";
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
