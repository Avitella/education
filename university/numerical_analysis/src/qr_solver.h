#ifndef _NUMERICAL_ANALYSIS_QR_DECOMPOSITION_H
#define _NUMERICAL_ANALYSIS_QR_DECOMPOSITION_H

#include <cassert>

#include "vector.h"
#include "solver.h"
#include "matrix.h"
#include "error.h"

namespace numerical_analysis {

class qr_solver_t : public solver_t {
 public:
  qr_solver_t() noexcept {
  }

  vector_t solve(matrix_t const &matrix, vector_t const &b) const {
    volatile clock_t start_clock = clock();
    check_sizes(matrix, b);
    matrix_t v = matrix.transpose();
    vector_t buffer;
    for (size_t i = 0; i < v.rows_count(); ++i) {
      double norm = v[i].norm();
      if (equal_to_(norm, 0.0)) {
        throw linearly_dependent_error_t();
      }
      v[i] /= norm;
      double nv = v[i] * v[i];
      for (size_t j = i + 1; j < v.rows_count(); ++j) {
        double mult = (v[i] * v[j]) / nv;
        buffer.copy(v[i]);
        buffer *= mult;
        v[j] -= buffer;
      }
    }
    matrix_t r = v * matrix;
    vector_t b1 = v * b;
    vector_t answer(b1.size(), 0);
    for (int i = r.rows_count() - 1; i >= 0; --i) {
      answer[i] = b1[i];
      for (int j = i + 1; j < (int) r.rows_count(); ++j) {
        answer[i] -= r[i][j] * answer[j];
      }
      answer[i] /= r[i][i];
    }
    spent_time_ = (clock() - start_clock) * 1.0 / CLOCKS_PER_SEC;
    return answer;
  }

 private:
  puck::equal_to_t<double> equal_to_;
};

}

#endif
