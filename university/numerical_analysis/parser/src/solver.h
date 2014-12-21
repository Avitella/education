#ifndef _PARSER_SOLVER_H
#define _PARSER_SOLVER_H

#include <memory>

namespace parser {

class Solver;
typedef std::shared_ptr<Solver> SolverPtr;

class Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept = 0;

  const SolverPtr& GetLeft() const noexcept;
  void SetLeft(const SolverPtr& ptr) noexcept;
  const SolverPtr& GetRight() const noexcept;
  void SetRight(const SolverPtr& ptr) noexcept;

 protected:
  SolverPtr left_, right_;
};

class SolverVariableX : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverVariableY : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverConstant : public Solver {
 public:
  SolverConstant() noexcept;
  explicit SolverConstant(double constant) noexcept;
  virtual double Solve(double x, double y = 0) const noexcept;

 private:
  double constant_;
};

class SolverPlus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverMinus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverMultiply : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverDivide : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverSin : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverCos : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverLog : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

class SolverExp : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
};

}

#endif
