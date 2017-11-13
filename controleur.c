#include <stdlib.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  if (argc != 1) usage(argv[0], "");
  debug(1, "le contrôleur est en poste");
  shm_acceder();

  int id = sem_acceder();
  P(id);
  debug(1, "le contrôleur s'en va");

  return EXIT_SUCCESS;
}
