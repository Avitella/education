#ifndef _NUMERICAL_ANALYSIS_SOLVER_H
#define _NUMERICAL_ANALYSIS_SOLVER_H

#include <puck/exception.h>
#include "error.h"

#include "matrix.h"
#include "vector.h"

namespace numerical_analysis {

class solver_t {
 public:
  void check_sizes(matrix_t const &matrix, vector_t const &b) const {
    if (matrix.rows_count() == 0 || matrix.rows_count() != matrix.columns_count() || matrix.rows_count() != b.size()) {
      throw wrong_sizes_error_t(matrix);
    }
  }

  virtual vector_t solve(matrix_t const &matrix, vector_t const &b) const = 0;

  double spent_time() const noexcept {
    return spent_time_;
  }

 protected:
  mutable volatile double spent_time_;
};

}

#endif
