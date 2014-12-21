#include "solver.h"

#include <cassert>
#include <cmath>

namespace parser {

const SolverPtr& Solver::GetLeft() const noexcept {
  return left_;
}

void Solver::SetLeft(const SolverPtr& ptr) noexcept {
  left_ = ptr;
}

const SolverPtr& Solver::GetRight() const noexcept {
  return right_;
}

void Solver::SetRight(const SolverPtr& ptr) noexcept {
  right_ = ptr;
}

double SolverVariableX::Solve(double x, double) const noexcept {
  return x;
}

double SolverVariableY::Solve(double, double y) const noexcept {
  return y;
}

SolverConstant::SolverConstant() noexcept {
}

SolverConstant::SolverConstant(double constant) noexcept :
    constant_(constant) {
}

double SolverConstant::Solve(double, double) const noexcept {
  return constant_;
}

double SolverPlus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) + right_->Solve(x, y) : right_->Solve(x, y);
}

double SolverMinus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) - right_->Solve(x, y) : right_->Solve(x, y);
}

double SolverMultiply::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) * right_->Solve(x, y);
}

double SolverDivide::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) / right_->Solve(x, y);
}

double SolverSin::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return sin(right_->Solve(x, y));
}

double SolverCos::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return cos(right_->Solve(x, y));
}

double SolverExp::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return exp(right_->Solve(x, y));
}

double SolverLog::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return log(right_->Solve(x, y));
}

}
