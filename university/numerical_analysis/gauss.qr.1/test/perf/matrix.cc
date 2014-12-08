#include <gtest/gtest.h>

#include "matrix.h"

using namespace numerical_analysis;

static size_t constexpr ROWS_COUNT = 1000;
static size_t constexpr COLUMNS_COUNT = 1000;

TEST(matrix, multiply) {
  matrix_t a(ROWS_COUNT, COLUMNS_COUNT, 1), b(ROWS_COUNT, COLUMNS_COUNT, 1);
  a = a * b;
  puck::equal_to_t<double> eq;
  for (size_t i = 0; i < ROWS_COUNT; ++i) {
    for (size_t j = 0; j < COLUMNS_COUNT; ++j) {
      EXPECT_FALSE(eq(0, a[i][j]));
    }
  }
}
