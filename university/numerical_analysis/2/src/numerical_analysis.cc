#include <puck/options.h>

#include "parser/parser.h"

#include <fstream>
#include <iostream>

struct point_t {
  double x, y;

  point_t() noexcept {
  }

  point_t(double x, double y) noexcept :
      x(x),
      y(y) {
  }
};

static void Log(char const *what) {
  std::cerr << "Log: " << what << std::endl;
}

static void Error(char const *what) {
  std::cerr << "Error: " << what << std::endl;
}

static double keystone(const std::vector<point_t>& points) {
  double answer = 0;
  for (size_t i = 1; i < points.size(); ++i) {
    answer += ((points[i].y + points[i - 1].y) / 2.0) * (points[i].x - points[i - 1].x);
  }
  return answer;
}

static double rectangle(const std::vector<point_t>& points) {
  double answer = 0;
  for (size_t i = 1; i < points.size(); ++i)
    answer += points[i].y * (points[i].x - points[i - 1].x);
  return answer;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    std::vector<std::string> args = {
      "function=",
      "from=",
      "to=",
      "delta=",
      "stdin",
      "draw-tree",
      "output-tsv=",
      "log"
    };
    options.parse(argc, argv, args);
  } catch (const std::exception& e) {
    Error(e.what());
    return -1;
  }

  std::string expr;

  if (options.contains("function")) {
    expr = options.get_argument("function");
  }

  if (options.contains("stdin")) {
    std::getline(std::cin, expr);
  }

  if (expr.empty()) {
    Error("Expected function");
    return -1;
  }

  if (options.contains("log")) {
    Log(expr.c_str());
  }

  if (!options.contains("from") || !options.contains("to") || !options.contains("delta")) {
    Error("Expected from, to and delta");
    return -1;
  }

  double from = std::stod(options.get_argument("from"));
  double to = std::stod(options.get_argument("to"));
  double delta = std::stod(options.get_argument("delta"));

  if (to < from) {
    std::swap(to, from);
  }
  delta = fabs(delta);

  if (options.contains("log")) {
    Log(("from = " + std::to_string(from)).c_str());
    Log(("to = " + std::to_string(to)).c_str());
    Log(("delta = " + std::to_string(delta)).c_str());
  }

  parser::Parser parser;
  parser::SolverPtr solver;
  
  try {
    solver = parser.Parse(expr);
  } catch (const std::exception& e) {
    Error(e.what());
    return -1;
  }

  if (options.contains("draw-tree")) {
    solver->Print(std::cout, 0, 2);
  }

  std::vector<point_t> points;
  for (double x = from; x <= to; x += delta) {
    points.push_back(point_t(x, solver->Solve(x)));
  }

  if (options.contains("output-tsv")) {
    std::ofstream fout(options.get_argument("output-tsv"));
    fout << "x\ty" << std::endl;
    for (size_t i = 0; i < points.size(); ++i) {
      fout << points[i].x << '\t' << points[i].y << std::endl;
    }
  }

  std::cout << "Rectangle: " << rectangle(points) << std::endl;
  std::cout << "Keystone: " << keystone(points) << std::endl;

  return 0;
}
