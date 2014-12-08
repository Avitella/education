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

  vector_t const &at(size_t i) const noexcept {
    return matrix_.at(i);
  }

  matrix_t() noexcept {
  }

  matrix_t(size_t rows, size_t columns, size_t value) :
      matrix_(rows, vector_t(columns, value)) {
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

  matrix_t operator * (matrix_t const &other) const noexcept {
    matrix_t result(rows_count(), columns_count(), 0.0);
    matrix_t buffer = other.transpose();
    vector_t first(rows_count() * columns_count(), 0.0);
    vector_t second(buffer.rows_count() * buffer.columns_count(), 0.0);
    for (size_t i = 0; i < rows_count(); ++i) {
      for (size_t j = 0; j < columns_count(); ++j) {
        first[i * columns_count() + j] = matrix_.at(i).at(j);
      }
    }
    for (size_t i = 0; i < buffer.rows_count(); ++i) {
      for (size_t j = 0; j < buffer.columns_count(); ++j) {
        second[i * buffer.columns_count() + j] = buffer.matrix_.at(i).at(j);
      }
    }
    for (size_t i = 0; i < rows_count(); ++i) {
      size_t ii = i * rows_count();
      for (size_t j = 0; j < rows_count(); ++j) {
        size_t jj = j * rows_count();
        for (size_t k = 0; k < rows_count(); ++k) {
          result[i][j] += first[ii + k] * second[jj + k];
          //result[i][j] += matrix_.at(i).at(k) * buffer.at(j).at(k);
        }
      }
    }
    return result;
  }

  matrix_t transpose() const noexcept {
    matrix_t result(columns_count(), rows_count(), 0.0);
    for (size_t i = 0; i < rows_count(); ++i) {
      for (size_t j = 0; j < columns_count(); ++j) {
        result[j][i] = (*this).at(i).at(j);
      }
    }
    return result;
  }

  vector_t operator * (vector_t const &other) const noexcept {
    assert(columns_count() == other.size());
    vector_t result(rows_count(), 0.0);
    for (size_t i = 0; i < rows_count(); ++i) {
      for (size_t j = 0; j < columns_count(); ++j) {
        result[i] += other.at(j) * matrix_.at(i).at(j);
      }
    }
    return result;
  }

  bool operator == (matrix_t const &other) const noexcept {
    if (rows_count() != other.rows_count() || columns_count() != other.columns_count())
      return false;
    for (size_t i = 0; i < rows_count(); ++i) {
      for (size_t j = 0; j < columns_count(); ++j) {
        if (matrix_.at(i).at(j) != other.matrix_.at(i).at(j)) {
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
    out << matrix.at(i);
    if (i + 1 != matrix.rows_count()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

}

#endif
