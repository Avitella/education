#include <iostream>

#include <puck/options.h>

#include "gauss_solver.h"
#include "qr_solver.h"

static int error(std::exception const &e) {
  std::cerr << "ERROR: " << e.what() << std::endl;
  return -1;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    options.parse(argc, argv, {
      "help",
      "input-tsv=",
      "output-tsv=",
      "random"
    });
  } catch (std::exception const &e) {
    return error(e);
  }

  return 0;
}
