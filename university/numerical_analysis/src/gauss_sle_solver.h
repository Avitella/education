#ifndef _NUMERICAL_ANALYSIS_GAUSS_SLE_SOLVER_H
#define _NUMERICAL_ANALYSIS_GAUSS_SLE_SOLVER_H

#include <algorithm>

#include <puck/exception.h>

#include "matrix.h"
#include "vector.h"

namespace numerical_analysis {

class gauss_sle_solver_t {
  mutable double run_time_;
  mutable size_t steps_count_;

  void check_sizes(matrix_t const &matrix1, vector_t const &b1) const {
    if (matrix1.empty()) {
      throw puck::exception_t("Unexpected empty matrix");
    }
    size_t height = matrix1.size();
    for (size_t i = 0; i < matrix1.size(); ++i) {
      if (matrix1[i].size() != height) {
        throw puck::exception_t(
          "Wrong matrix size: %lu, expected: %lu, on row: %lu",
          matrix1.size(), height, i
        );
      }
    }
    if (b1.size() != height) {
      throw puck::exception_t(
        "Wrong size of free members vector: %lu, expected: %lu",
        b1.size(), height
      );
    }
  }

 public:
  gauss_sle_solver_t() noexcept :
      run_time_(0),
      steps_count_(0) {
  }

  matrix_t triangulate(matrix_t const &matrix1, double eps = 1e-9) const {
    size_t n = matrix1.size(), m = matrix1.front().size();
    matrix_t matrix(matrix1);
    for (size_t i = 0; i < n; ++i) {
      size_t max_row = i;
      for (size_t j = i + 1; j < n; ++j) {
        if (matrix[j][i] > matrix[max_row][i]) {
          max_row = j;
        }
      }
      for (size_t k = 0; k < m; ++k) {
        std::swap(matrix[max_row][k], matrix[i][k]);
      }
      for (size_t j = i + 1; j < n; ++j) {
        if (abs(matrix[i][i]) < eps) {
          throw puck::exception_t("Linearly dependent vectors in matrix");
        }
        double mult = matrix[j][i] / matrix[i][i];
        for (size_t k = i; k < m; ++k) {
          matrix[j][k] -= matrix[i][k] * mult;
        }
      }
    }
    bool ok = false;
    for (size_t i = 0; i < m; ++i) {
      if (matrix[n - 1][i] != 0) {
        ok = true;
      }
    }
    if (!ok) {
      throw puck::exception_t("Linearly dependent vectors in matrix");
    }
    return matrix;
  }

  vector_t solve(matrix_t const &matrix1, vector_t const &b1) const {
    check_sizes(matrix1, b1);

    matrix_t matrix(matrix1.begin(), matrix1.end());
    for (size_t i = 0; i < matrix.size(); ++i) {
      matrix[i].push_back(b1[i]);
    }

    run_time_ = clock();
    steps_count_ = 0;

    run_time_ = (clock() - run_time_) * 1.0 / CLOCKS_PER_SEC;
    
    vector_t answer;
    return answer;
  }

  double get_spent_time() const noexcept {
    return run_time_;
  }

  size_t get_steps_count() const noexcept {
    return steps_count_;
  }
};

}

#endif
