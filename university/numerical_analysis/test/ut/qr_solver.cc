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

  EXPECT_TRUE(vector_t({0.0093877551020407866, -0.024326530612244913, -0.088326530612244936}) == answer) << answer;
}

TEST(qr_solver, strong_solve) {
  qr_solver_t solver;
  matrix_t matrix({{1, 2, 3}, {4, 3, 7}, {7, 8, 9}});
  vector_t b = {1, 2, 3};

  vector_t answer = solver.solve(matrix, b);

  puck::equal_to_t<double> eq(1e-9);

  EXPECT_TRUE(vector_t({-0.066666666666666555, 0.1333333333333333, 0.26666666666666661}).equal_to(answer, eq)) << answer;
}
