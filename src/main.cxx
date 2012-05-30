#include <cstdlib>

#include "ep2.h"

int main(int argc, char **argv) {
  // Initialize.
  ep2::init(argc, argv);
  // Run.
  ep2::run();
  // Never reaches here.
  return EXIT_SUCCESS;
}
