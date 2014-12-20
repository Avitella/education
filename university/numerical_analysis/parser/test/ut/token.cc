#include <gtest/gtest.h>

#include "token.h"

using namespace parser;

TEST(Token, MatchTypeChar) {
  EXPECT_EQ(TokenType::MINUS, MatchTokenType('-'));
  EXPECT_EQ(TokenType::PLUS, MatchTokenType('+'));
  EXPECT_EQ(TokenType::MULTIPLY, MatchTokenType('*'));
  EXPECT_EQ(TokenType::DIVIDE, MatchTokenType('/'));
  EXPECT_EQ(TokenType::OPENING_BRACKET, MatchTokenType('('));
  EXPECT_EQ(TokenType::CLOSING_BRACKET, MatchTokenType(')'));
  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType('u'));
}

TEST(Token, MatchTypeString) {
  EXPECT_EQ(TokenType::SIN, MatchTokenType("sin"));
  EXPECT_EQ(TokenType::COS, MatchTokenType("cos"));
  EXPECT_EQ(TokenType::LOG, MatchTokenType("log"));
  EXPECT_EQ(TokenType::EXP, MatchTokenType("exp"));
  EXPECT_EQ(TokenType::VARIABLE, MatchTokenType("x"));
}

TEST(Token, CheckNumber) {
  EXPECT_EQ(TokenType::NUMBER, MatchTokenType("123"));
  EXPECT_EQ(TokenType::NUMBER, MatchTokenType("123123.55"));
  EXPECT_EQ(TokenType::NUMBER, MatchTokenType("1"));

  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType(".123"));
  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType("123."));
  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType("123.1241.1231"));
  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType("31131a13123"));
  EXPECT_EQ(TokenType::UNKNOWN, MatchTokenType("asdqdwqd"));
}
