#ifndef _NUMERICAL_ANALYSIS_MATRIX_H
#define _NUMERICAL_ANALYSIS_MATRIX_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "vector.h"

namespace numerical_analysis {
 
class matrix_t {
 public:
  size_t rows_count() const noexcept {
    return matrix_.size();
  }

  size_t columns_count() const noexcept {
    return matrix_.empty() ? 0 : matrix_.front().size();
  }

  vector_t &operator [] (size_t i) noexcept {
    return matrix_[i];
  }

  vector_t const &operator [] (size_t i) const noexcept {
    return matrix_[i];
  }

  matrix_t() noexcept {
  }

  matrix_t(matrix_t const &other) noexcept :
      matrix_(other.matrix_) {
  }

  matrix_t(matrix_t &&other) noexcept {
    std::swap(matrix_, other.matrix_);
  }

  matrix_t &operator = (matrix_t const &other) noexcept {
    matrix_ = other.matrix_;
    return *this;
  }

  matrix_t &operator = (matrix_t &&other) noexcept {
    std::swap(matrix_, other.matrix_);
    return *this;
  }

  matrix_t(std::initializer_list<vector_t> list) noexcept :
      matrix_(list) {
  }

  bool operator == (matrix_t const &other) const noexcept {
    if (rows_count() != other.rows_count() || columns_count() != other.columns_count())
      return false;
    for (size_t i = 0; i < rows_count(); ++i) {
      for (size_t j = 0; j < columns_count(); ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<vector_t> matrix_;
};

inline std::ostream &operator << (std::ostream &out, matrix_t const &matrix) {
  out << "{";
  for (size_t i = 0; i < matrix.rows_count(); ++i) {
    out << matrix[i];
    if (i + 1 != matrix.rows_count()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

}

#endif
