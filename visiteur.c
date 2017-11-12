#include <stdlib.h>
#include <unistd.h> // sleep
#include "musee.h"


int main(int argc, char * argv[]) {
  int time;
  if (argc != 2) usage(argv[0], "time");
  time = atoi(argv[1]);
  if (time < 0) usage(argv[0], "time>=0");
  shm_acceder();

  sleep(5);
  int id = sem_acceder();
  V(id);

  return EXIT_SUCCESS;
}
