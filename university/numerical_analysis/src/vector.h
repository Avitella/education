#ifndef _NUMERICAL_ANALYSIS_VECTOR_H
#define _NUMERICAL_ANALYSIS_VECTOR_H

#include <vector>

namespace numerical_analysis {

class vector_t {
 public:
  vector_t(std::initializer_list<double> list) noexcept :
      vector_(list) {
  }

  double &operator [] (size_t i) noexcept {
    return vector_[i];
  }

  double const &operator [] (size_t i) const noexcept {
    return vector_[i];
  }

  size_t size() const noexcept {
    return vector_.size();
  }

  void push_back(double x) noexcept {
    vector_.push_back(x);
  }

  vector_t() noexcept {
  }

  vector_t(size_t size, double zero) noexcept :
      vector_(size, zero) {
  }

  bool operator == (vector_t const &other) const noexcept {
    if (size() != other.size()) {
      return false;
    }
    for (size_t i = 0; i < size(); ++i) {
      if (vector_[i] != other.vector_[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  std::vector<double> vector_;
};

inline std::ostream &operator << (std::ostream &out, vector_t const &v) {
  out << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i + 1 != v.size()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

}

#endif
