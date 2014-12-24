#include "lexer.h"

namespace parser {

static const std::string UNKNOWN_SYMBOL = "Unknown symbol: ";

UnknownSymbolException::UnknownSymbolException(char c) noexcept :
    message_(UNKNOWN_SYMBOL + c) {
}

const char* UnknownSymbolException::what() const noexcept {
  return message_.c_str();
}

Lexer::Lexer() noexcept {
}

Token Lexer::NextToken() noexcept {
  Token result = tokens_.front();
  tokens_.pop_front();
  return result;
}

const Token& Lexer::FrontToken() const noexcept {
  return tokens_.front();
}

bool Lexer::HasMoreTokens() const noexcept {
  return !tokens_.empty();
}

static const char END_CHAR = '$';

enum class ParseState {
  UNKNOWN,
  NUMBER,
  LETTER,
  END
};

static void MoveToken(std::string &token, size_t offset, TokenQueue &tokens) {
  if (!token.empty()) {
    TokenType token_type = MatchTokenType(token);
    if (token_type == TokenType::UNKNOWN)
      throw UnknownTokenException(token);
    tokens.push_back(Token(token_type, offset, token));
    token.clear();
  }
}

static void PushToken(char token, size_t offset, TokenQueue &tokens) {
  TokenType token_type = MatchTokenType(token);
  if (token_type == TokenType::UNKNOWN)
    throw UnknownTokenException(token);
  tokens.push_back(Token(token_type, offset, std::string() + token));
}

static ParseState ParseUnknown(char c, size_t offset, std::string& token, TokenQueue& tokens) {
  switch (c) {
    case '0'...'9': case '.':
      token += c;
      return ParseState::NUMBER;
    case 'a'...'z':
      token += c;
      return ParseState::LETTER;
    case '+': case '-': case '*': case '/': case '(': case ')':
      PushToken(c, offset, tokens);
      return ParseState::UNKNOWN;
    case ' ': case '\t': case '\n':
      return ParseState::UNKNOWN;
    case END_CHAR:
      return ParseState::END;
    default:
      throw UnknownSymbolException(c);
  }
}

static ParseState ParseNumber(char c, size_t offset, std::string& token, TokenQueue& tokens) {
  switch (c) {
    case '0'...'9': case '.':
      token += c;
      return ParseState::NUMBER;
    case 'a'...'z':
      MoveToken(token, offset, tokens);
      token += c;
      return ParseState::LETTER;
    case '+': case '-': case '*': case '/': case '(': case ')':
      MoveToken(token, offset, tokens);
      PushToken(c, offset, tokens);
      return ParseState::UNKNOWN;
    case ' ': case '\t': case '\n':
      MoveToken(token, offset, tokens);
      return ParseState::UNKNOWN;
    case END_CHAR:
      MoveToken(token, offset, tokens);
      return ParseState::END;
    default:
      throw UnknownSymbolException(c);
  }
}

static ParseState ParseLetter(char c, size_t offset, std::string& token, TokenQueue& tokens) {
  switch (c) {
    case '0'...'9': case '.':
      MoveToken(token, offset, tokens);
      token += c;
      return ParseState::NUMBER;
    case 'a'...'z':
      token += c;
      return ParseState::LETTER;
    case '+': case '-': case '*': case '/': case '(': case ')':
      MoveToken(token, offset, tokens);
      PushToken(c, offset, tokens);
      return ParseState::UNKNOWN;
    case ' ': case '\t': case '\n':
      MoveToken(token, offset, tokens);
      return ParseState::UNKNOWN;
    case END_CHAR:
      MoveToken(token, offset, tokens);
      return ParseState::END;
    default:
      throw UnknownSymbolException(c);
  }
}

void Lexer::Parse(std::string expr) {
  expr += END_CHAR;

  ParseState state = ParseState::UNKNOWN;
  std::string token;
  for (size_t i = 0; i < expr.length(); ++i) {
    char c = expr[i];
    switch (state) {
      case ParseState::UNKNOWN:
        state = ParseUnknown(c, i, token, tokens_);
        break;
      case ParseState::NUMBER:
        state = ParseNumber(c, i, token, tokens_);
        break;
      case ParseState::LETTER:
        state = ParseLetter(c, i, token, tokens_);
        break;
      case ParseState::END:
        break;
    }
  }
}

void Lexer::PushTokenFront(const Token& token) noexcept {
  tokens_.push_front(token);
}

void Lexer::PushTokenBack(const Token& token) noexcept {
  tokens_.push_back(token);
}

}
