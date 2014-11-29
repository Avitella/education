#ifndef _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H
#define _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H

#include <algorithm>

#include <puck/exception.h>

#include "matrix.h"
#include "error.h"
#include "vector.h"

namespace numerical_analysis {

class gauss_solver_t {
 public:
  void check_sizes(matrix_t const &matrix, vector_t const &b) const {
    if (matrix.rows_count() == 0 || matrix.rows_count() != matrix.columns_count() || matrix.rows_count() != b.size()) {
      throw wrong_sizes_error_t(matrix);
    }
  }

  matrix_t triangulate_matrix(matrix_t matrix) const {
    for (size_t i = 0; i < matrix.rows_count(); ++i) {
      size_t max_row = i;
      for (size_t j = i + 1; j < matrix.rows_count(); ++j) {
        if (abs(matrix[j][i]) > abs(matrix[max_row][i])) {
          max_row = j;
        }
      }
      if (abs(matrix[max_row][i]) < EPS) {
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

  vector_t solve(matrix_t matrix, vector_t const &b) const {
    check_sizes(matrix, b);
    for (size_t i = 0; i < b.size(); ++i) {
      matrix[i].push_back(b[i]);
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
    return answer;
  }

 private:
  static double constexpr EPS = 1e-9;
};

}

#endif
