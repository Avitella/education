#ifndef _PARSER_LEXER_H
#define _PARSER_LEXER_H

#include <queue>
#include <string>

#include "token.h"

namespace parser {

typedef std::deque<Token> TokenQueue;

class Lexer {
 public:
  Lexer() noexcept;
  void Parse(std::string expr);
  Token NextToken() noexcept;
  const Token& FrontToken() const noexcept;
  void PushTokenFront(const Token& token) noexcept;
  void PushTokenBack(const Token& token) noexcept;
  bool HasMoreTokens() const noexcept;

 private:
  TokenQueue tokens_;
};

class UnknownSymbolException : public std::exception {
 public:
  UnknownSymbolException(char c) noexcept;
  virtual const char* what() const noexcept;

 private:
  std::string message_;
};

}

#endif
