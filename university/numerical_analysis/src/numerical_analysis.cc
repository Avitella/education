#include <iostream>
#include <fstream>

#include <puck/options.h>
#include <puck/tsv.h>

#include "gauss_solver.h"
#include "qr_solver.h"

using namespace numerical_analysis;

static int const SRAND_INIT = 773;
static int const MAX_VALUE = 1000;

static matrix_t generate_matrix(size_t n) {
  matrix_t matrix(n, n, 0.0);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      matrix[i][j] = rand() % MAX_VALUE - MAX_VALUE / 2;
    }
  }
  return matrix;
}

static vector_t generate_answer(size_t n) {
  vector_t result(n, 0.0);
  for (size_t i = 0; i < n; ++i) {
    result[i] = rand() % MAX_VALUE - MAX_VALUE / 2;
  }
  return result;
}

static int error(char const *s) {
  std::cerr << "ERROR: " << s << std::endl;
  return -1;
}

static int warning(char const *s) {
  std::cerr << "WARNING: " << s << std::endl;
  return 0;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    options.parse(argc, argv, {
      "help",
      "input-tsv=",
      "output-tsv=",
      "range=",
    });
  } catch (std::exception const &e) {
    return error(e.what());
  }

  if (options.contains("range")) {
    std::ostream *out = &std::cout;
    std::ofstream fout;
    if (options.contains("output-tsv")) {
      fout = std::ofstream(options.get_argument("output-tsv"));
      out = &fout;
    }
    (*out) << "MatrixSize" << '\t' << "GaussSolverSpentTime" << '\t' <<  "GaussSolverIterations" << '\t' << "QRSolverSpentTime" << '\t' << "QRSolverIterations" << std::endl;
    std::string const &range = options.get_argument("range");
    int from, to;
    if (sscanf(range.c_str(), "%d:%d", &from, &to) != 2) {
      return error("wrong range format");
    }
    if (from <= 0 || to <= 0 || to < from) {
      return error("wrong range values");
    }
    for (int n = from; n <= to; ++n) {
      srand(SRAND_INIT);

      matrix_t matrix = generate_matrix(n);
      vector_t b = generate_answer(n);

      gauss_solver_t gauss_solver;
      qr_solver_t qr_solver;

      try {
        vector_t gauss_answer = gauss_solver.solve(matrix, b);
        vector_t qr_answer = qr_solver.solve(matrix, b);

        (*out) << n << '\t' << gauss_solver.spent_time() << '\t' << gauss_solver.iterations_count() << '\t' << qr_solver.spent_time() << '\t' << qr_solver.iterations_count() << std::endl;
      } catch (std::exception const &e) {
        warning(e.what());
      }
    }
  }

  return 0;
}
