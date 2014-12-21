#include <gtest/gtest.h>

#include "lexer.h"

using namespace parser;

TEST(Lexer, Parse) {
  Lexer lexer;
  lexer.Parse("1 + 22- 11");

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::PLUS, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MINUS, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::END, lexer.NextToken().GetType());
  ASSERT_FALSE(lexer.HasMoreTokens());
}

TEST(Lexer, Exception) {
  Lexer lexer;
  ASSERT_ANY_THROW(lexer.Parse("1 + 22- 11@"));
}

TEST(Lexer, ParseFunction) {
  Lexer lexer;
  lexer.Parse("1 + x -    22 * 44 * (12 - x * sin(13)) / 31 * log(y)");

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::PLUS, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::VARIABLE_X, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MINUS, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MULTIPLY, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MULTIPLY, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::OPENING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MINUS, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::VARIABLE_X, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MULTIPLY, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::SIN, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::OPENING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::CLOSING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::CLOSING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::DIVIDE, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::NUMBER, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::MULTIPLY, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::LOG, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::OPENING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::VARIABLE_Y, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::CLOSING_BRACKET, lexer.NextToken().GetType());
  ASSERT_TRUE(lexer.HasMoreTokens());

  ASSERT_EQ(TokenType::END, lexer.NextToken().GetType());
  ASSERT_FALSE(lexer.HasMoreTokens());
}
