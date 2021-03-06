#include "helper_lexer.hpp"

#include <sstream>

std::string test::to_string(klang::TokenType t){
  if(t == klang::TokenType::IDENTIFIER) return "IDENTIFIER";
  if(t == klang::TokenType::NUMBER)     return "NUMBER";
  if(t == klang::TokenType::SYMBOL)     return "SYMBOL";
  if(t == klang::TokenType::CHARACTER)  return "CHARACTER";
  if(t == klang::TokenType::STRING)     return "STRING";
  if(t == klang::TokenType::IGNORE)     return "IGNORE";
  return "UNKNOWN";
}

std::string test::to_string(klang::Token const& t){
  std::ostringstream os;
  os << to_string(t.type()) << ": " << t.str() << " at Line " << t.line() << "\n";
  return os.str();
}

std::string test::to_string(klang::TokenVector const& vec){
  std::ostringstream os;
  for(auto const& e: vec) {
    os << to_string(e);
  }
  return os.str();
}

std::ostream& operator<<(std::ostream& os, klang::TokenType t){
  return os << test::to_string(t);
}

std::ostream& operator<<(std::ostream& os, klang::Token const& t){
  return os << test::to_string(t);
}

std::ostream& operator<<(std::ostream& os, klang::TokenVector const& vec){
  return os << test::to_string(vec);
}
