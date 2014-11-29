#ifndef _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H
#define _NUMERICAL_ANALYSIS_GAUSS_SOLVER_H

#include <algorithm>

#include <puck/exception.h>

#include "matrix.h"
#include "vector.h"

namespace numerical_analysis {

struct linearly_dependent_error_t : public puck::exception_t {
  linearly_dependent_error_t() noexcept :
      puck::exception_t("linearly dependent system") {
  }
};

struct wrong_sizes_error_t : public puck::exception_t {
  wrong_sizes_error_t(matrix_t const &matrix) noexcept :
      puck::exception_t("rows count (%lu) != columns count (%lu)", matrix.rows_count(), matrix.columns_count()) {
  }
};

class gauss_solver_t {
 public:
  void check_sizes(matrix_t const &matrix) const {
    if (matrix.rows_count() != matrix.columns_count()) {
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

 private:
  static double constexpr EPS = 1e-9;
};

}

#endif
