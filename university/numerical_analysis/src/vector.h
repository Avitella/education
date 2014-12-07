#ifndef _NUMERICAL_ANALYSIS_VECTOR_H
#define _NUMERICAL_ANALYSIS_VECTOR_H

#include <cmath>
#include <cstdlib>
#include <vector>

#include <puck/algo.h>

namespace numerical_analysis {

class vector_t {
 public:
  vector_t(std::initializer_list<double> list) noexcept :
      vector_(list) {
  }

  vector_t(vector_t const &other) noexcept :
      vector_(other.vector_) {
  }

  double &operator [] (size_t i) noexcept {
    return vector_[i];
  }

  double at(size_t i) const noexcept {
    return vector_.at(i);
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

  double operator * (vector_t const &other) const noexcept {
    assert(size() == other.size());
    double answer = 0;
    for (size_t i = 0; i < size(); ++i) {
      answer += vector_[i] * other.vector_[i];
    }
    return answer;
  }

  vector_t &operator *= (double c) noexcept {
    for (size_t i = 0; i < size(); ++i) {
      vector_[i] *= c;
    }
    return *this;
  }

  vector_t operator * (double c) const noexcept {
    vector_t result(*this);
    return (result *= c);
  }

  vector_t operator / (double c) const noexcept {
    return (*this) * (1.0 / c);
  }

  vector_t &operator += (vector_t const &other) noexcept {
    assert(size() == other.size());
    for (size_t i = 0; i < size(); ++i) {
      vector_[i] *= other.vector_[i];
    }
    return *this;
  }

  vector_t operator + (vector_t const &other) const noexcept {
    vector_t result(*this);
    return (result += other);
  }

  vector_t &operator -= (vector_t const &other) noexcept {
    assert(size() == other.size());
    for (size_t i = 0; i < size(); ++i) {
      vector_[i] -= other.vector_[i];
    }
    return *this;
  }

  vector_t operator - (vector_t const &other) const noexcept {
    vector_t result(*this);
    return (result -= other);
  }

  double norm() const noexcept {
    return sqrt((*this) * (*this));
  }

  bool zero() const noexcept {
    for (size_t i = 0; i < size(); ++i) {
      if (puck::abs(vector_[i]) > EPS) {
        return false;
      }
    }
    return true;
  }

  bool equal_to(vector_t const &other, puck::equal_to_t<double> const &eq) const noexcept {
    if (size() != other.size())
      return false;
    for (size_t i = 0; i < size(); ++i)
      if (!eq(vector_[i], other.vector_[i])) 
        return false;
    return true;
  }

  void copy(vector_t const &other) noexcept {
    vector_.resize(other.vector_.size());
    for (size_t i = 0; i < vector_.size(); ++i) {
      vector_[i] = other.vector_[i];
    }
  }

 private:
  static double constexpr EPS = 1e-9;

  std::vector<double> vector_;
};

inline std::ostream &operator << (std::ostream &out, vector_t const &v) {
  out << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    out << v.at(i);
    if (i + 1 != v.size()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

}

#endif
