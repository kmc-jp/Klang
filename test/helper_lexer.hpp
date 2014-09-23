#ifndef KMC_KLANG_TEST_HELPER_LEXER_HPP
#define KMC_KLANG_TEST_HELPER_LEXER_HPP

#include "lexer.hpp"

#include <string>

namespace test {
  std::string to_string(klang::TokenType t);
  std::string to_string(klang::Token const& t);
  std::string to_string(klang::TokenVector const& vec);
}  // namespace test

namespace klang {
  bool operator==(klang::Token const& lhs, klang::Token const& rhs);
}  // namespace klang

std::ostream& operator<<(std::ostream& os, klang::TokenType t);
std::ostream& operator<<(std::ostream& os, klang::Token const& t);
std::ostream& operator<<(std::ostream& os, klang::TokenVector const& vec);

#endif // KMC_KLANG_TEST_HELPER_LEXER_HPP
