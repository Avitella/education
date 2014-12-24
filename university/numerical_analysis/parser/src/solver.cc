#include "solver.h"

#include <cassert>
#include <cmath>
#include <stdexcept>

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

void Solver::SetChildren(const SolverPtr& left, const SolverPtr& right) noexcept {
  left_ = left;
  right_ = right;
}

double SolverVariableX::Solve(double x, double) const noexcept {
  return x;
}

void SolverVariableX::CheckOrThrow() const {
}

double SolverVariableY::Solve(double, double y) const noexcept {
  return y;
}

void SolverVariableY::CheckOrThrow() const {
}

SolverConstant::SolverConstant() noexcept {
}

SolverConstant::SolverConstant(double constant) noexcept :
    constant_(constant) {
}

double SolverConstant::Solve(double, double) const noexcept {
  return constant_;
}

void SolverConstant::CheckOrThrow() const {
}

double SolverPlus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) + right_->Solve(x, y) : right_->Solve(x, y);
}

// TODO: std::exception -> ExpectedTokenException

void SolverPlus::CheckOrThrow() const {
  if (!right_)
    throw std::exception();
}

double SolverMinus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) - right_->Solve(x, y) : right_->Solve(x, y);
}

void SolverMinus::CheckOrThrow() const {
  if (!right_)
    throw std::exception();
}

double SolverMultiply::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) * right_->Solve(x, y);
}

void SolverMultiply::CheckOrThrow() const {
  if (!left_ || !right_)
    throw std::exception();
}

double SolverDivide::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) / right_->Solve(x, y);
}

void SolverDivide::CheckOrThrow() const {
  if (!left_ || !right_)
    throw std::exception();
}

double SolverSin::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return sin(right_->Solve(x, y));
}

void SolverSin::CheckOrThrow() const {
  if (left_ || !right_)
    throw std::exception();
}

double SolverCos::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return cos(right_->Solve(x, y));
}

void SolverCos::CheckOrThrow() const {
  if (left_ || !right_)
    throw std::exception();
}

double SolverExp::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return exp(right_->Solve(x, y));
}

void SolverExp::CheckOrThrow() const {
  if (left_ || !right_)
    throw std::exception();
}

double SolverLog::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return log(right_->Solve(x, y));
}

void SolverLog::CheckOrThrow() const {
  if (left_ || !right_)
    throw std::exception();
}

}
