#include "token.h"

#include <algorithm>

namespace numerical_analysis {

static bool check_number(std::string const &s) {
  if (s.empty())
    return false;
  if (s.front() == '.' || s.back() == '.')
    return false;
  if (std::count(s.begin(), s.end(), '.') > 1)
    return false;
  for (char c : s)
    if (c != '.' && (c < '0' || c > '9'))
      return false;
  return true;
}

token_type_t match_token_type(std::string const &s) {
  if (s == "sin")
    return token_type_t::sin;
  if (s == "cos")
    return token_type_t::cos;
  if (s == "log")
    return token_type_t::log;
  if (s == "exp")
    return token_type_t::exp;
  if (s == "x")
    return token_type_t::variable;
  if (check_number(s))
    return token_type_t::number;
  throw unknown_token_type_error_t(s);
}

token_type_t match_token_type(char c) {
  switch (c) {
    case '+':
      return token_type_t::plus;
    case '-':
      return token_type_t::minus;
    case '*':
      return token_type_t::multiply;
    case '/':
      return token_type_t::divide;
    case '(':
      return token_type_t::opening_bracket;
    case ')':
      return token_type_t::closing_bracket;
    default:
      throw unknown_token_type_error_t(c);
  }
}

}
