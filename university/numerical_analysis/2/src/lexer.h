#ifndef _NUMERICAL_ANALYSIS_LEXER_H
#define _NUMERICAL_ANALYSIS_LEXER_H

#include <string>
#include <queue>

#include "token.h"

namespace numerical_analysis {

class unexpected_symbol_error_t : public std::exception {
 public:
  unexpected_symbol_error_t(char c) noexcept :
      error(std::string("Unexpected symbol: ") + c) {
  }

  virtual char const *what() const noexcept {
    return error.c_str();
  }
 
 private:
  std::string error;
};

class lexer_t {
 public:
  lexer_t() noexcept {
  }

  void parse(std::string expr);

  token_t next_token() noexcept {
    token_t result = tokens_.front();
    tokens_.pop();
    return result;
  }

  bool empty() const noexcept {
    return tokens_.empty();
  }

 private:
  std::queue<token_t> tokens_;
};

}

#endif
