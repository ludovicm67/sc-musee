#include <stdlib.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  if (argc != 1) usage(argv[0], "");
  shm_acceder();
  return EXIT_SUCCESS;
}
