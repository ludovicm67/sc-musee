#include <stdlib.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  if (argc != 1) usage(argv[0], "");
  shm_acceder();

  int id = sem_acceder();
  P(id);

  return EXIT_SUCCESS;
}
