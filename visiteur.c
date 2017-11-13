#include <stdlib.h>
#include <time.h>
#include "musee.h"

void temps_de_visite(int ms) {
  struct timespec ts;
  ts.tv_sec = (time_t) (ms / 1000);
  ts.tv_nsec = (ms - ((long) ts.tv_sec * 1000)) * 1000000;
  nanosleep(&ts, NULL);
}

int main(int argc, char * argv[]) {
  int time, id;
  if (argc != 2) usage(argv[0], "time");
  time = atoi(argv[1]);
  if (time < 0) usage(argv[0], "time>=0");
  shm_acceder();

  temps_de_visite(time);
  id = sem_acceder();
  V(id);

  return EXIT_SUCCESS;
}
