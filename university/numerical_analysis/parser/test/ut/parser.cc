#include <gtest/gtest.h>

#include "parser.h"

using namespace parser;

TEST(Parser, WithoutBrackets) {
  const std::string expr = "2 + 4 - 11 * 2";
  Parser parser;
  SolverPtr solver = parser.Parse(expr);
  EXPECT_EQ(-16, solver->Solve(0));
}

TEST(Parser, WithBracketsAndVariableX) {
  const std::string expr = "2 + 4 * (3 + x) + 2 * ((1 + 3 * (1 + 10))) - 4 * sin(x)";
  Parser parser;
  SolverPtr solver = parser.Parse(expr);
  EXPECT_EQ(86.36281029269728, solver->Solve(2.0));
}

TEST(Parser, Functions) {
  const std::string expr = "sin(x) + cos(x) + log(x) * exp(y) - 22 * (((0 * 29)) + 71) / (sin(x) * cos(x) * log(y))";
  Parser parser;
  SolverPtr solver = parser.Parse(expr);
  EXPECT_EQ(-4955.169487907536, solver->Solve(1.0, 2.0));
}
