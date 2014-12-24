#include "solver.h"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace parser {

void Solver::Print(std::ostream &out, size_t offset, size_t factor) const noexcept {
  if (right_)
    right_->Print(out, offset + 1, factor);
  for (size_t i = 0; i < offset * factor; ++i) {
    out << " ";
  }
  out << ToString() << std::endl;
  if (left_)
    left_->Print(out, offset + 1, factor);
}

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

std::string SolverVariableX::ToString() const noexcept {
  return "x";
}

double SolverVariableY::Solve(double, double y) const noexcept {
  return y;
}

std::string SolverVariableY::ToString() const noexcept {
  return "y";
}

SolverConstant::SolverConstant() noexcept {
}

SolverConstant::SolverConstant(double constant) noexcept :
    constant_(constant) {
}

double SolverConstant::Solve(double, double) const noexcept {
  return constant_;
}

std::string SolverConstant::ToString() const noexcept {
  return std::to_string(constant_);
}

double SolverPlus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) + right_->Solve(x, y) : right_->Solve(x, y);
}

std::string SolverPlus::ToString() const noexcept {
  return "+";
}

double SolverMinus::Solve(double x, double y) const noexcept {
  assert(right_);
  return left_ ? left_->Solve(x, y) - right_->Solve(x, y) : right_->Solve(x, y);
}

std::string SolverMinus::ToString() const noexcept {
  return "-";
}

double SolverMultiply::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) * right_->Solve(x, y);
}

std::string SolverMultiply::ToString() const noexcept {
  return "*";
}

double SolverDivide::Solve(double x, double y) const noexcept {
  assert(left_);
  assert(right_);
  return left_->Solve(x, y) / right_->Solve(x, y);
}

std::string SolverDivide::ToString() const noexcept {
  return "/";
}

double SolverSin::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return sin(right_->Solve(x, y));
}

std::string SolverSin::ToString() const noexcept {
  return "sin";
}

double SolverCos::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return cos(right_->Solve(x, y));
}

std::string SolverCos::ToString() const noexcept {
  return "cos";
}

double SolverExp::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return exp(right_->Solve(x, y));
}

std::string SolverExp::ToString() const noexcept {
  return "exp";
}

double SolverLog::Solve(double x, double y) const noexcept {
  assert(!left_);
  assert(right_);
  return log(right_->Solve(x, y));
}

std::string SolverLog::ToString() const noexcept {
  return "log";
}

}
