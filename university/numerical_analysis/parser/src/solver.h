#ifndef _PARSER_SOLVER_H
#define _PARSER_SOLVER_H

#include <iostream>
#include <memory>

namespace parser {

class Solver;
typedef std::shared_ptr<Solver> SolverPtr;

class Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept = 0;
  virtual std::string ToString() const noexcept = 0;

  const SolverPtr& GetLeft() const noexcept;
  void SetLeft(const SolverPtr& ptr) noexcept;
  const SolverPtr& GetRight() const noexcept;
  void SetRight(const SolverPtr& ptr) noexcept;
  void SetChildren(const SolverPtr& left, const SolverPtr& right) noexcept;
  void Print(std::ostream &out, size_t offset = 0, size_t factor = 2) const noexcept;

 protected:
  SolverPtr left_, right_;
};

class SolverVariableX : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverVariableY : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverConstant : public Solver {
 public:
  SolverConstant() noexcept;
  explicit SolverConstant(double constant) noexcept;
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;

 private:
  double constant_;
};

class SolverPlus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverMinus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverMultiply : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverDivide : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverSin : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverCos : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverLog : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

class SolverExp : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual std::string ToString() const noexcept;
};

}

#endif
