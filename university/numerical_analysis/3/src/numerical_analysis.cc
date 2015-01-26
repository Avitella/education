#include <puck/options.h>

#include "parser/parser.h"

#include <fstream>
#include <cassert>
#include <iostream>

struct Point {
  double x, y;

  Point() noexcept {
  }

  Point(double x, double y) noexcept :
      x(x),
      y(y) {
  }
};

struct MethodContext {
  double x0, y0, h, xn, t;
  size_t overhead;

  MethodContext() noexcept {
    x0 = y0 = h = xn = t = 0;
    overhead = 0;
  }

  MethodContext(double x0, double y0, double h, double xn) noexcept :
      x0(x0),
      y0(y0),
      h(h),
      xn(xn),
      t(0),
      overhead(0) {
  }

  MethodContext(const MethodContext& c) noexcept :
      x0(c.x0),
      y0(c.y0),
      h(c.h),
      xn(c.xn),
      t(c.t),
      overhead(c.overhead) {
  }
};

static std::vector<Point> RungeKuttaMethod(const parser::SolverPtr& solver, MethodContext* context, int64_t count = 0) {
  double start = clock();
  double y = context->y0, x = context->x0, h = context->h, xn = context->xn;
  std::vector<Point> points;
  points.push_back(Point(x, y));
  --count;
  while (x < xn && count != 0) {
    double k1 = solver->Solve(x, y);
    double k2 = solver->Solve(x + h / 2.0, y + (h / 2.0) * k1);
    double k3 = solver->Solve(x + h / 2.0, y + (h / 2.0) * k2);
    double k4 = solver->Solve(x + h, y + h * k3);
    y = y + (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
    x += h;
    points.push_back(Point(x, y));
    --count;
  }
  context->t = (clock() - start) * 1.0 / CLOCKS_PER_SEC;
  return points;
}

static std::vector<Point> AdamsMethod(const parser::SolverPtr& solver, MethodContext* context) {
  double start = clock();
  double y = context->y0, x = context->x0, h = context->h, xn = context->xn;
  std::vector<Point> points;
  {
    MethodContext buffer_context(*context);
    points = RungeKuttaMethod(solver, &buffer_context, 4);
    context->overhead += buffer_context.overhead;
  }
  std::vector<double> dy;
  for (size_t i = 0; i < points.size(); ++i)
    dy.push_back(solver->Solve(points[i].x, points[i].y));
  while (x < xn) {
    x = points.back().x;
    y = points.back().y;
    y = y + h * (55 * dy[dy.size() - 1] - 59 * dy[dy.size() - 2] + 37 * dy[dy.size() - 3] - 9 * dy[dy.size() - 4]) / 24;
    x += h;
    points.push_back(Point(x, y));
    dy.push_back(solver->Solve(points.back().x, points.back().y));
  }
  context->t = (clock() - start) * 1.0 / CLOCKS_PER_SEC;
  return points;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    std::vector<std::string> args = {
      "f=",
      "x0=",
      "y0=",
      "h=",
      "xn="
    };
    options.parse(argc, argv, args);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if (!options.contains("f")) {
    std::cerr << "Function expected: use -f= option" << std::endl;
    return -1;
  }

  if (!options.contains("x0")) {
    std::cerr << "x0 expected: use -x0= option" << std::endl;
    return -1;
  }

  if (!options.contains("y0")) {
    std::cerr << "y0 expected: use -y0= option" << std::endl;
    return -1;
  }

  if (!options.contains("h")) {
    std::cerr << "h expected: use -h= option" << std::endl;
    return -1;
  }

  if (!options.contains("xn")) {
    std::cerr << "xn expected: use -xn= option" << std::endl;
    return 0;
  }

  double x0 = std::stod(options.get_argument("x0"));
  double y0 = std::stod(options.get_argument("y0"));
  double h = std::stod(options.get_argument("h"));
  double xn = std::stod(options.get_argument("xn"));

  if (xn <= x0) {
    std::cerr << "xn must be greater then x0" << std::endl;
    return -1;
  }

  try {
    parser::Parser parser;
    parser::SolverPtr solver = parser.Parse(options.get_argument("f"));

    MethodContext runge_kutta_context(x0, y0, h, xn);
    std::vector<Point> runge_kutta_answer = RungeKuttaMethod(solver, &runge_kutta_context);

    MethodContext adams_context(x0, y0, h, xn);
    std::vector<Point> adams_answer = AdamsMethod(solver, &adams_context);

    assert(adams_answer.size() == runge_kutta_answer.size());

    std::cout << "RungeKuttaX\tRungeKuttaY\tAdamsX\tAdamsY\n";
    for (size_t i = 0; i < runge_kutta_answer.size(); ++i) {
      std::cout << runge_kutta_answer[i].x << '\t' << runge_kutta_answer[i].y << '\t'
                << adams_answer[i].x << '\t' << adams_answer[i].y << '\n';
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  return 0;
}
