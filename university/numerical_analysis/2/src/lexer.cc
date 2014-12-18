#include "lexer.h"

namespace numerical_analysis {

static char const END_CHAR = '#';

enum class parse_state_t {
  unknown,
  number,
  letter,
  end
};

static void move_token(std::string &tok, std::queue<token_t> &tokens) {
  if (!tok.empty()) {
    tokens.push(token_t(tok, match_token_type(tok)));
    tok.clear();
  }
}

static parse_state_t parse_unknown(char c, std::string &token, std::queue<token_t> &tokens) {
  switch (c) {
    case '0' ... '9': case '.':
      token += c;
      return parse_state_t::number;
    case 'a' ... 'z':
      token += c;
      return parse_state_t::letter;
    case '+': case '-': case '*': case '/': case '(': case ')':
      tokens.push(token_t(c, match_token_type(c)));
      return parse_state_t::unknown;
    case ' ':
      return parse_state_t::unknown;
    case END_CHAR:
      return parse_state_t::end;
    default:
      throw unexpected_symbol_error_t(c);
  }
}

static parse_state_t parse_number(char c, std::string &token, std::queue<token_t> &tokens) {
  switch (c) {
    case '0' ... '9': case '.':
      token += c;
      return parse_state_t::number;
    case 'a' ... 'z':
      move_token(token, tokens);
      token += c;
      return parse_state_t::letter;
    case '+': case '-': case '*': case '/': case '(': case ')':
      move_token(token, tokens);
      tokens.push(token_t(c, match_token_type(c)));
      return parse_state_t::unknown;
    case ' ':
      move_token(token, tokens);
      return parse_state_t::unknown;
    case END_CHAR:
      move_token(token, tokens);
      return parse_state_t::end;
    default:
      throw unexpected_symbol_error_t(c);
  }
}

static parse_state_t parse_letter(char c, std::string &token, std::queue<token_t> &tokens) {
  switch (c) {
    case '0' ... '9': case '.':
      move_token(token, tokens);
      token += c;
      return parse_state_t::number;
    case 'a' ... 'z':
      token += c;
      return parse_state_t::letter;
    case '+': case '-': case '*': case '/': case '(': case ')':
      move_token(token, tokens);
      tokens.push(token_t(c, match_token_type(c)));
      return parse_state_t::unknown;
    case ' ':
      move_token(token, tokens);
      return parse_state_t::unknown;
    case END_CHAR:
      move_token(token, tokens);
      return parse_state_t::end;
    default:
      throw unexpected_symbol_error_t(c);
  }
}

void lexer_t::parse(std::string expr) {
  expr += END_CHAR;
  std::string token;
  parse_state_t current_state = parse_state_t::unknown;
  for (char c : expr) {
    switch (current_state) {
      case parse_state_t::unknown:
        current_state = parse_unknown(c, token, tokens_);
        break;
      case parse_state_t::number:
        current_state = parse_number(c, token, tokens_);
        break;
      case parse_state_t::letter:
        current_state = parse_letter(c, token, tokens_);
        break;
      default:
        break;
    }
  }
}

}
