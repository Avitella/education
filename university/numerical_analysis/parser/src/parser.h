#ifndef _PARSER_PARSER_H
#define _PARSER_PARSER_H

#include "lexer.h"
#include "solver.h"
#include "token.h"

namespace parser {

class Parser {
 public:
  Parser() noexcept;
  SolverPtr Parse(const std::string& expr) const;
};

class UnexpectedTokenException : public std::exception {
 public:
  UnexpectedTokenException(const Token& token) noexcept;
  UnexpectedTokenException(TokenType type) noexcept;
  virtual const char* what() const noexcept;

 private:
  std::string message_;
};

}

#endif // _PARSER_PARSER_H
