#include <gtest/gtest.h>

#include "gauss_solver.h"

using namespace numerical_analysis;

TEST(gauss_solver, test_triangulate) {
  gauss_solver_t solver;
    
  matrix_t matrix = solver.triangulate_matrix({
    {1, 1},
    {1, 2}
  });

  EXPECT_TRUE(matrix_t({{1, 1}, {0, 1}}) == matrix) << matrix;

  matrix = solver.triangulate_matrix({
    {2, 0, 0},
    {2, 1, 0},
    {2, 1, 3}
  });
   
  EXPECT_TRUE(matrix_t({{2, 0, 0}, {0, 1, 0}, {0, 0, 3}}) == matrix) << matrix;

  matrix = solver.triangulate_matrix({
    {1, 2, 3},
    {1, 3, 4},
    {1, 2, 5}
  });

  EXPECT_TRUE(matrix_t({{1, 2, 3}, {0, 1, 1}, {0, 0, 2}}) == matrix) << matrix;

  matrix = solver.triangulate_matrix({
    {1, 2, 3, 1},
    {4, 3, 7, 2},
    {7, 8, 9, 3}
  });

  EXPECT_TRUE(matrix_t({{7, 8, 9, 3}, {0, -1.5714285714285712, 1.8571428571428577, 0.28571428571428581}, {0, -1.1102230246251565e-16, 2.727272727272728, 0.72727272727272729}}) == matrix) << matrix;

  EXPECT_ANY_THROW(solver.triangulate_matrix(matrix_t({{1, 2}, {1, 2}})));
}

TEST(gauss_solver, calculate_answer) {
  gauss_solver_t solver;
  matrix_t matrix({{1, 1}, {1, 2}});
  vector_t b = {1, 2};

  vector_t answer = solver.solve(matrix, b);

  EXPECT_TRUE(vector_t({0, 1}) == answer) << answer;
}

TEST(gauss_solver, strong_solve) {
  gauss_solver_t solver;
  matrix_t matrix({{1, 2, 3}, {4, 3, 7}, {7, 8, 9}});
  vector_t b = {1, 2, 3};

  vector_t answer = solver.solve(matrix, b);

  EXPECT_TRUE(vector_t({-0.066666666666666555, 0.1333333333333333, 0.26666666666666661}) == answer) << answer;
}
