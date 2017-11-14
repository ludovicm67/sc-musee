#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sem.h>
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

  id = sem_acceder();
int debugSEM = semctl(id, 0, GETNCNT);
printf("%d\n", debugSEM);
P(id);


  debug(1, "un visiteur arrive au musée");
  temps_de_visite(time);
  V(id);
  debug(1, "le visiteur a fini sa visite");

  return EXIT_SUCCESS;
}
