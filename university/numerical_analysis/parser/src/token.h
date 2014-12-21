#ifndef _PARSER_TOKEN_H
#define _PARSER_TOKEN_H

#include <exception>
#include <string>

namespace parser {

enum class TokenType {
  UNKNOWN = -1,
  NUMBER,
  VARIABLE_X,
  VARIABLE_Y,
  OPENING_BRACKET,
  CLOSING_BRACKET,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  SIN,
  COS,
  LOG,
  EXP,
  END
};

class Token {
 public:
  Token() noexcept;
  Token(const Token& other) noexcept;
  explicit Token(TokenType token_type) noexcept;
  Token(TokenType token_type, const std::string& value) noexcept;
  TokenType GetType() const noexcept;
  const std::string& GetValue() const noexcept;

 private:
  TokenType token_type_;
  std::string value_;
};

class UnknownTokenException : public std::exception {
 public:
  UnknownTokenException(const std::string& token) noexcept;
  UnknownTokenException(char token) noexcept;
  virtual const char* what() const noexcept;

 private:
  std::string message_;
};

TokenType MatchTokenType(char c) noexcept;
TokenType MatchTokenType(const std::string& s) noexcept;

}

#endif // _PARSER_TOKEN_H
