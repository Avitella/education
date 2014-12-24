#ifndef _PARSER_SOLVER_H
#define _PARSER_SOLVER_H

#include <memory>

namespace parser {

class Solver;
typedef std::shared_ptr<Solver> SolverPtr;

class Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept = 0;
  virtual void CheckOrThrow() const = 0;

  const SolverPtr& GetLeft() const noexcept;
  void SetLeft(const SolverPtr& ptr) noexcept;
  const SolverPtr& GetRight() const noexcept;
  void SetRight(const SolverPtr& ptr) noexcept;
  void SetChildren(const SolverPtr& left, const SolverPtr& right) noexcept;

 protected:
  SolverPtr left_, right_;
};

class SolverVariableX : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverVariableY : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverConstant : public Solver {
 public:
  SolverConstant() noexcept;
  explicit SolverConstant(double constant) noexcept;
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;

 private:
  double constant_;
};

class SolverPlus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverMinus : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverMultiply : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverDivide : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverSin : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverCos : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverLog : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

class SolverExp : public Solver {
 public:
  virtual double Solve(double x, double y = 0) const noexcept;
  virtual void CheckOrThrow() const;
};

}

#endif
