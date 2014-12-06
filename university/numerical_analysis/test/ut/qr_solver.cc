#include <gtest/gtest.h>

#include "qr_solver.h"

using namespace numerical_analysis;

TEST(qr_solver, test_2x2) {
  qr_solver_t solver;
  matrix_t matrix({{1, 1}, {1, 2}});
  vector_t b = {1, 2};

  vector_t answer = solver.solve(matrix, b);

  EXPECT_TRUE(vector_t({0, 1}) == answer) << answer;
}

TEST(qr_solver, test_3x3) {
  qr_solver_t solver;
  matrix_t matrix({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});
  vector_t b = {1, 2, 3};

  vector_t answer = solver.solve(matrix, b);

  EXPECT_TRUE(vector_t({0, 0, 1}) == answer) << answer;
}
