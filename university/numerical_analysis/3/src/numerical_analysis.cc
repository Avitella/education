#include <puck/options.h>

#include "parser/parser.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  puck::options_t options;

  try {
    std::vector<std::string> args = {
      "f=",
      "x0=",
      "y0=",
      "h=",
      "n="
    };
    options.parse(argc, argv, args);
  } catch (const std::exception& e) {
    return -1;
  }

  return 0;
}
