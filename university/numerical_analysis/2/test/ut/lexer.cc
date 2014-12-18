#include <gtest/gtest.h>

#include "lexer.h"

using namespace numerical_analysis;

TEST(lexer, parse) {
  lexer_t lexer;
  lexer.parse("1 + 22- 11");

  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::plus, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::minus, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
}

TEST(lexer, parse_function) {
  lexer_t lexer;
  lexer.parse("1 + x -    22 * 44 * (12 - x * sin(13)) / 31 * log(x)");

  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::plus, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::variable, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::minus, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::multiply, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::multiply, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::opening_bracket, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::minus, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::variable, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::multiply, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::sin, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::opening_bracket, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::closing_bracket, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::closing_bracket, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::divide, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::number, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::multiply, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::log, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::opening_bracket, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::variable, lexer.next_token().get_type());
  ASSERT_EQ(token_type_t::closing_bracket, lexer.next_token().get_type());
}
