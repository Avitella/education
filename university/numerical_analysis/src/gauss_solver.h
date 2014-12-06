#ifndef _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H
#define _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H

#include <algorithm>

#include "matrix.h"
#include "solver.h"
#include "vector.h"

namespace numerical_analysis {

class gauss_solver_t : public solver_t {
 public:
  matrix_t triangulate_matrix(matrix_t matrix) const {
    for (size_t i = 0; i < matrix.rows_count(); ++i) {
      size_t max_row = i;
      for (size_t j = i + 1; j < matrix.rows_count(); ++j) {
        if (abs(matrix[j][i]) > abs(matrix[max_row][i])) {
          max_row = j;
        }
      }
      if (equal_to_(matrix[max_row][i], 0.0)) {
        throw linearly_dependent_error_t();
      }
      for (size_t j = i; j < matrix.columns_count(); ++j) {
        std::swap(matrix[i][j], matrix[max_row][j]);
      }
      for (size_t j = i + 1; j < matrix.rows_count(); ++j) {
        double mult = matrix[j][i] / matrix[i][i];
        for (size_t k = i; k < matrix.columns_count(); ++k) {
          matrix[j][k] -= matrix[i][k] * mult;
        }
      }
    }
    return matrix;
  }

  virtual vector_t solve(matrix_t const &_matrix, vector_t const &b) const {
    volatile clock_t start_clock = clock();
    matrix_t matrix(_matrix);
    check_sizes(matrix, b);
    for (size_t i = 0; i < b.size(); ++i) {
      matrix[i].push_back(b.at(i));
    }
    matrix = triangulate_matrix(matrix);
    vector_t answer(matrix.rows_count(), 0.0);
    for (int i = matrix.rows_count() - 1; i >= 0; --i) {
      answer[i] = matrix[i][matrix.columns_count() - 1];
      for (int j = i + 1; j < (int) matrix.rows_count(); ++j) {
        answer[i] -= matrix[i][j] * answer[j];
      }
      answer[i] /= matrix[i][i];
    }
    spent_time_ = (clock() - start_clock) * 1.0 / CLOCKS_PER_SEC;
    return answer;
  }

 private:
  puck::equal_to_t<double> equal_to_;
};

}

#endif
