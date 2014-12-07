#include <iostream>

#include <puck/options.h>

#include "gauss_solver.h"
#include "qr_solver.h"

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    options.parse(argc, argv, {
      "h",
      "help",
      "input-tsv=",
      "output-tsv=",
      "random"
    });
  } catch (puck::exception_t const &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
