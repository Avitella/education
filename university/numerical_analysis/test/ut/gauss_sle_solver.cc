#include <gtest/gtest.h>

#include "gauss_sle_solver.h"

using namespace numerical_analysis;

TEST(gauss_sle_solver, test_triangular) {
  gauss_sle_solver_t solver;
    
  matrix_t matrix = solver.triangulate({
    {1, 1},
    {1, 2}
  });

  EXPECT_TRUE(matrix_equals(
    {{1, 1}, {0, 1}},
    matrix
  )) << make_string(matrix);

  matrix = solver.triangulate({
    {2, 0, 0},
    {2, 1, 0},
    {2, 1, 3}
  });
   
  EXPECT_TRUE(matrix_equals(
    {{2, 0, 0}, {0, 1, 0}, {0, 0, 3}},
    matrix
  )) << make_string(matrix);

  matrix = solver.triangulate({
    {1, 2, 3},
    {1, 3, 4},
    {1, 2, 5}
  });

  EXPECT_TRUE(matrix_equals(
    {{1, 2, 3},
     {0, 1, 1},
     {0, 0, 2}},
    matrix
  )) << make_string(matrix);

  EXPECT_ANY_THROW(solver.triangulate({{1, 2}, {1, 2}})) << make_string(solver.triangulate({{1, 2}, {1, 2}}));
}
