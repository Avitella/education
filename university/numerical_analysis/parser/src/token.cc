#include "token.h"

namespace parser {

static const std::string UNKNOWN_TOKEN = "Unknown token: ";

UnknownTokenException::UnknownTokenException(const std::string& token) noexcept :
    message_(UNKNOWN_TOKEN + token) {
}

UnknownTokenException::UnknownTokenException(char token) noexcept :
    message_(UNKNOWN_TOKEN + token) {
}

const char* UnknownTokenException::what() const noexcept {
  return message_.c_str();
}

TokenType MatchTokenType(char c) noexcept {
  switch (c) {
    case '(':
      return TokenType::OPENING_BRACKET;
    case ')':
      return TokenType::CLOSING_BRACKET;
    case '+':
      return TokenType::PLUS;
    case '-':
      return TokenType::MINUS;
    case '*':
      return TokenType::MULTIPLY;
    case '/':
      return TokenType::DIVIDE;
    default:
      return TokenType::UNKNOWN;
  }
}

static bool IsNumber(const std::string& s) noexcept {
  if (s.empty())
    return false;
  for (size_t i = 0; i < s.length(); ++i)
    if (!isdigit(s[i]) && s[i] != '.')
      return false;
  if (std::count(s.begin(), s.end(), '.') > 1)
    return false;
  if (s.front() == '.' || s.back() == '.')
    return false;
  return true;
}

TokenType MatchTokenType(const std::string& s) noexcept {
  if (s == "sin")
    return TokenType::SIN;
  if (s == "cos")
    return TokenType::COS;
  if (s == "log")
    return TokenType::LOG;
  if (s == "exp")
    return TokenType::EXP;
  if (s == "x")
    return TokenType::VARIABLE_X;
  if (s == "y")
    return TokenType::VARIABLE_Y;
  if (IsNumber(s))
    return TokenType::NUMBER;
  return TokenType::UNKNOWN;
}

Token::Token() noexcept :
    token_type_(TokenType::UNKNOWN),
    value_() {
}

Token::Token(TokenType token_type) noexcept :
    token_type_(token_type),
    value_() {
}

Token::Token(const Token& other) noexcept :
    token_type_(other.token_type_),
    value_(other.value_) {
}

Token::Token(TokenType token_type, const std::string& value) noexcept :
    token_type_(token_type),
    value_(value) {
}

TokenType Token::GetType() const noexcept {
  return token_type_;
}

const std::string& Token::GetValue() const noexcept {
  return value_;
}

}
