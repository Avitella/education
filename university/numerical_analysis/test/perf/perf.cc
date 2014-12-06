#include <gtest/gtest.h>

#include "gauss_solver.h"
#include "qr_solver.h"

using namespace numerical_analysis;

static size_t constexpr MAX_VALUE = 1e4;
static size_t constexpr ROWS_COUNT = 1000;
static size_t constexpr COLUMNS_COUNT = 1000;
static size_t constexpr INIT = 773;

vector_t gauss_answer, qr_answer;

static matrix_t generate_matrix() {
  clock_t start_clock = clock();

  matrix_t matrix(ROWS_COUNT, COLUMNS_COUNT, 0.0);

  for (size_t i = 0; i < ROWS_COUNT; ++i) {
    for (size_t j = 0; j < COLUMNS_COUNT; ++j) {
      matrix[i][j] = rand() % MAX_VALUE - MAX_VALUE / 2;
    }
  }

  matrix = matrix * matrix.transpose();

  std::cerr << "generate matrix spent time: " << (clock() - start_clock) * 1.0 / CLOCKS_PER_SEC << std::endl;
  return matrix;
}

static vector_t generate_answer() {
  vector_t b(ROWS_COUNT, 0.0);
  for (size_t i = 0; i < ROWS_COUNT; ++i) {
    b[i] =  rand() % MAX_VALUE - MAX_VALUE / 2;
  }
  return b;
}

TEST(gauss_solver, bigbadabam) {
  srand(INIT);

  gauss_solver_t solver;

  matrix_t matrix = generate_matrix();
  vector_t b = generate_answer();

  try {
    gauss_answer = solver.solve(matrix, b);
    std::cerr << "gauss solve spent time: " << solver.spent_time() << std::endl;
  } catch (puck::exception_t const &e) {
    std::cerr << e.what() << std::endl;
  }
}

TEST(qr_solver, bigbadaboom) {
  srand(INIT);

  qr_solver_t solver;

  matrix_t matrix = generate_matrix();
  vector_t b = generate_answer();

  try {
    qr_answer = solver.solve(matrix, b);
    std::cerr << "qr solve spent time: " << solver.spent_time() << std::endl;
  } catch (puck::exception_t const &e) {
    std::cerr << e.what() << std::endl;
  }
}

TEST(perf, compare) {
  puck::equal_to_t<double> eq(1e-9);
  ASSERT_EQ(gauss_answer.size(), qr_answer.size());
  for (size_t i = 0; i < gauss_answer.size(); ++i) {
    ASSERT_TRUE(eq(gauss_answer[i], qr_answer[i])) << "gauss: " << gauss_answer[i] << ", qr: " << qr_answer[i];
  }
}
