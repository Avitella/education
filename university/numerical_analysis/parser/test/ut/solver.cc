#include <gtest/gtest.h>

#include <cmath>

#include "solver.h"

using namespace parser;

TEST(Solver, Plus) {
  SolverPtr root(new SolverPlus());

  root->SetLeft(SolverPtr(new SolverVariableX()));
  root->SetRight(SolverPtr(new SolverConstant(5)));

  ASSERT_EQ(27, root->Solve(22));
}

TEST(Solver, Sin) {
  SolverPtr plus(new SolverPlus());

  plus->SetLeft(SolverPtr(new SolverVariableX()));
  plus->SetRight(SolverPtr(new SolverConstant(5)));

  SolverPtr root(new SolverSin());
  root->SetRight(plus);

  ASSERT_EQ(sin(27), root->Solve(22));
  ASSERT_EQ(sin(10), root->Solve(5));
}
