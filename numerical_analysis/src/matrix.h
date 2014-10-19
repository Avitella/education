#ifndef _NUMERICAL_ANALYSIS_MATRIX_H
#define _NUMERICAL_ANALYSIS_MATRIX_H

#include <algorithm>
#include <iostream>
#include <vector>

namespace numerical_analysis {
 
using matrix_t = std::vector<std::vector<double>>;

static bool matrix_equals(matrix_t const &a, matrix_t const &b, double eps = 1e-4) {
  if (a.size() != b.size())
    return false;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].size() != b[i].size()) {
      return false;
    }
    for (size_t j = 0; j < a[i].size(); ++j) {
      if (abs(a[i][j] - b[i][j]) > eps) {
        return false;
      }
    }
  }
  return true;
}

std::string make_string(matrix_t const &matrix) {
  std::string out;
  for (size_t i = 0; i < matrix.size(); ++i) {
    out += "{";
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      out += std::to_string(matrix[i][j]);
      if (j + 1 != matrix[i].size())
        out += ",";
    }
    out += "}\n";
  }
  return out;
}

}

#endif
