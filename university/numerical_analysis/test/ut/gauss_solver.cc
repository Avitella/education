#include <gtest/gtest.h>

#include "gauss_solver.h"

using namespace numerical_analysis;

TEST(gauss_solver, test_triangular) {
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

  EXPECT_ANY_THROW(solver.triangulate_matrix(matrix_t({{1, 2}, {1, 2}})));
}
