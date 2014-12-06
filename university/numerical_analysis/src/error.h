#ifndef _NUMERICAL_ANALYSIS_ERROR_H
#define _NUMERICAL_ANALYSIS_ERROR_H

#include <puck/exception.h>

namespace numerical_analysis {

struct linearly_dependent_error_t : public puck::exception_t {
  linearly_dependent_error_t() noexcept :
      puck::exception_t("linearly dependent system") {
  }
};

struct wrong_sizes_error_t : public puck::exception_t {
  wrong_sizes_error_t(matrix_t const &matrix) noexcept :
      puck::exception_t("wrong sizes error: %lu, %lu", matrix.rows_count(), matrix.columns_count()) {
  }
};

}

#endif
