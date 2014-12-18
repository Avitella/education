#ifndef _NUMERICAL_ANALYSIS_TOKEN_H
#define _NUMERICAL_ANALYSIS_TOKEN_H

#include <string>

namespace numerical_analysis {

class unknown_token_type_error_t : public std::exception {
 public:
  unknown_token_type_error_t(std::string const &s) noexcept :
      error(std::string("Unknown token type: ") + s) {
  }

  unknown_token_type_error_t(char c) noexcept :
      error(std::string("Unknown token type: ") + c) {
  }

  virtual char const *what() const noexcept {
    return error.c_str();
  }

 private:
  std::string error;
};

enum class token_type_t {
  unknown,
  plus,
  minus,
  multiply,
  divide,
  number,
  variable,
  opening_bracket,
  closing_bracket,
  sin,
  cos,
  log,
  exp
};

token_type_t match_token_type(std::string const &s);
token_type_t match_token_type(char c);

class token_t {
 public:
  token_t() noexcept :
      token_type_(token_type_t::unknown) {
  }

  token_t(token_t const &tok) noexcept :
      value_(tok.value_),
      token_type_(tok.token_type_) {
  }

  token_t(std::string const &s, token_type_t t) noexcept :
      value_(s),
      token_type_(t) {
  }

  token_t(char c, token_type_t t) noexcept :
      value_(std::string() + c),
      token_type_(t) {
  }

  token_type_t get_type() const noexcept {
    return token_type_;
  }

  std::string const &get_value() const noexcept {
    return value_;
  }

 private:
  std::string value_;
  token_type_t token_type_;
};

}

#endif
