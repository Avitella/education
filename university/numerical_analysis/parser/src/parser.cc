#include "parser.h"
#include "solver.h"
#include "lexer.h"

#include <string>

namespace parser {

UnexpectedTokenException::UnexpectedTokenException(const Token& token) noexcept :
    message_("Unexpected token: " + token.GetValue() + " at " + std::to_string(token.GetOffset())) {
}

UnexpectedTokenException::UnexpectedTokenException(TokenType) noexcept : 
    message_("Unexpected token type") {
}

const char* UnexpectedTokenException::what() const noexcept {
  return message_.c_str();
}

Parser::Parser() noexcept {
}

static double TokenToDouble(const Token& token) noexcept {
  return std::stod(token.GetValue());
}

static SolverPtr MatchSolver(const Token& token) {
  switch (token.GetType()) {
    case TokenType::PLUS:
      return SolverPtr(new SolverPlus());
    case TokenType::MINUS:
      return SolverPtr(new SolverMinus());
    case TokenType::MULTIPLY:
      return SolverPtr(new SolverMultiply());
    case TokenType::DIVIDE:
      return SolverPtr(new SolverDivide());
    case TokenType::SIN:
      return SolverPtr(new SolverSin());
    case TokenType::COS:
      return SolverPtr(new SolverCos());
    case TokenType::LOG:
      return SolverPtr(new SolverLog());
    case TokenType::EXP:
      return SolverPtr(new SolverExp());
    case TokenType::VARIABLE_X:
      return SolverPtr(new SolverVariableX());
    case TokenType::VARIABLE_Y:
      return SolverPtr(new SolverVariableY());
    case TokenType::NUMBER:
      return SolverPtr(new SolverConstant(TokenToDouble(token)));
    default:
      throw UnexpectedTokenException(token);
  }
}

static SolverPtr ParseSummand(Lexer *lexer, bool with_bracket = false);

static SolverPtr ParseBracket(Lexer *lexer) {
  if (!lexer->HasMoreTokens())
    throw UnexpectedTokenException(Token(TokenType::END));
  if (lexer->FrontToken().GetType() != TokenType::OPENING_BRACKET)
    throw UnexpectedTokenException(lexer->FrontToken());
  lexer->NextToken();
  SolverPtr bracket;
  while (lexer->HasMoreTokens()) {
    switch (lexer->FrontToken().GetType()) {
      case TokenType::NUMBER:
      case TokenType::VARIABLE_X:
      case TokenType::VARIABLE_Y:
      {
        if (bracket)
          throw UnexpectedTokenException(lexer->FrontToken());
        bracket = MatchSolver(lexer->NextToken());
        break;
      }
      case TokenType::OPENING_BRACKET:
      {
        if (bracket)
          throw UnexpectedTokenException(lexer->FrontToken());
        bracket = ParseBracket(lexer);
        break;
      }
      case TokenType::CLOSING_BRACKET:
      {
        if (!bracket)
          throw UnexpectedTokenException(Token(TokenType::END));
        return bracket;
      }
      case TokenType::SIN:
      case TokenType::COS:
      case TokenType::EXP:
      case TokenType::LOG:
      {
        if (bracket)
          throw UnexpectedTokenException(lexer->FrontToken());
        bracket = MatchSolver(lexer->NextToken());
        bracket->SetRight(ParseBracket(lexer));
        break;
      }
      case TokenType::PLUS:
      case TokenType::MINUS:
      {
        SolverPtr ptr = MatchSolver(lexer->NextToken());
        ptr->SetRight(ParseSummand(lexer, true)); // true: parse with bracket
        ptr->SetLeft(bracket);
        bracket = ptr;
        break;
      }
      default:
      {
        throw UnexpectedTokenException(lexer->FrontToken());
      }
    }
  }
  if (!bracket)
    throw UnexpectedTokenException(Token(TokenType::END));
  return bracket;
}

static SolverPtr NextSummand(Lexer *lexer) {
  if (!lexer->HasMoreTokens())
    throw UnexpectedTokenException(Token(TokenType::END));
  switch (lexer->FrontToken().GetType()) {
    case TokenType::OPENING_BRACKET:
    {
      return ParseBracket(lexer);
    }
    case TokenType::SIN:
    case TokenType::COS:
    case TokenType::EXP:
    case TokenType::LOG:
    {
      SolverPtr ptr = MatchSolver(lexer->NextToken());
      ptr->SetRight(ParseBracket(lexer));
      return ptr;
    }
    case TokenType::NUMBER:
    case TokenType::VARIABLE_X:
    case TokenType::VARIABLE_Y:
    {
      return MatchSolver(lexer->NextToken());
    }
    default:
    {
      throw UnexpectedTokenException(lexer->FrontToken());
    }
  }
}

static SolverPtr ParseSummand(Lexer *lexer, bool with_bracket) {
  SolverPtr summand;
  while (lexer->HasMoreTokens()) {
    switch (lexer->FrontToken().GetType()) {
      case TokenType::OPENING_BRACKET:
      {
        if (summand)
          throw UnexpectedTokenException(lexer->FrontToken());
        summand = ParseBracket(lexer);
        break;
      }
      case TokenType::SIN:
      case TokenType::COS:
      case TokenType::EXP:
      case TokenType::LOG:
      {
        if (summand)
          throw UnexpectedTokenException(lexer->FrontToken());
        summand = MatchSolver(lexer->NextToken());
        summand->SetRight(ParseBracket(lexer));
        break;
      }
      case TokenType::VARIABLE_X:
      case TokenType::VARIABLE_Y:
      case TokenType::NUMBER:
      {
        if (summand)
          throw UnexpectedTokenException(lexer->FrontToken());
        summand = MatchSolver(lexer->NextToken());
        break;
      }
      case TokenType::MULTIPLY:
      case TokenType::DIVIDE:
      {
        SolverPtr parent = MatchSolver(lexer->NextToken());
        parent->SetLeft(summand);
        parent->SetRight(NextSummand(lexer));
        summand = parent;
        break;
      }
      case TokenType::PLUS:
      case TokenType::MINUS:
      {
        if (!summand)
          throw UnexpectedTokenException(lexer->FrontToken());
        return summand;
      }
      case TokenType::CLOSING_BRACKET:
      {
        if (with_bracket) {
          if (!summand)
            throw UnexpectedTokenException(lexer->FrontToken());
          return summand;
        }
      }
      default:
      {
        throw UnexpectedTokenException(lexer->FrontToken());
      }
    }
  }
  if (!summand)
    throw UnexpectedTokenException(Token(TokenType::END));
  return summand;
}

static SolverPtr ParseExpression(Lexer *lexer) {
  SolverPtr solver;
  while (lexer->HasMoreTokens()) {
    switch (lexer->FrontToken().GetType()) {
      case TokenType::PLUS:
      case TokenType::MINUS:
      {
        SolverPtr parent = MatchSolver(lexer->NextToken());
        parent->SetLeft(solver);
        parent->SetRight(ParseSummand(lexer));
        solver = parent;
        break;
      }
      case TokenType::OPENING_BRACKET:
      case TokenType::SIN:
      case TokenType::COS:
      case TokenType::EXP:
      case TokenType::LOG:
      case TokenType::VARIABLE_X:
      case TokenType::VARIABLE_Y:
      case TokenType::NUMBER:
      {
        if (solver)
          throw UnexpectedTokenException(lexer->FrontToken());
        solver = ParseSummand(lexer);
        break;
      }
      default:
      {
        throw UnexpectedTokenException(lexer->FrontToken());
      }
    }
  }
  return solver;
}

SolverPtr Parser::Parse(const std::string& expr) const {
  Lexer lexer;
  lexer.Parse(expr);
  return ParseExpression(&lexer);
}

}
