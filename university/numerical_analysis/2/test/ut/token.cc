#include <gtest/gtest.h>

#include "token.h"

using namespace numerical_analysis;

TEST(token, match_type_char) {
  EXPECT_EQ(token_type_t::minus, match_token_type('-'));
  EXPECT_EQ(token_type_t::plus, match_token_type('+'));
  EXPECT_EQ(token_type_t::multiply, match_token_type('*'));
  EXPECT_EQ(token_type_t::divide, match_token_type('/'));
  EXPECT_EQ(token_type_t::opening_bracket, match_token_type('('));
  EXPECT_EQ(token_type_t::closing_bracket, match_token_type(')'));

  ASSERT_ANY_THROW(match_token_type('u'));
}

TEST(token, match_type_string) {
  EXPECT_EQ(token_type_t::sin, match_token_type("sin"));
  EXPECT_EQ(token_type_t::cos, match_token_type("cos"));
  EXPECT_EQ(token_type_t::log, match_token_type("log"));
  EXPECT_EQ(token_type_t::exp, match_token_type("exp"));
  EXPECT_EQ(token_type_t::variable, match_token_type("x"));

  ASSERT_ANY_THROW(match_token_type("asdqdwqd"));
}

TEST(token, check_number) {
  EXPECT_EQ(token_type_t::number, match_token_type("123"));
  EXPECT_EQ(token_type_t::number, match_token_type("123123.55"));
  EXPECT_EQ(token_type_t::number, match_token_type("1"));

  ASSERT_ANY_THROW(match_token_type(".123"));
  ASSERT_ANY_THROW(match_token_type("123."));
  ASSERT_ANY_THROW(match_token_type("123.1241.1231"));
  ASSERT_ANY_THROW(match_token_type("31131a13123"));
}
