#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "musee.h"

// export DEBUG_MUSEE=42 && ./visiteur 10000

void temps_de_visite(int ms) {
  struct timespec ts;
  ts.tv_sec = (time_t) (ms / 1000);
  ts.tv_nsec = (ms - ((long) ts.tv_sec * 1000)) * 1000000;
  nanosleep(&ts, NULL);
}

int main(int argc, char * argv[]) {
  int time, shmid, nb_visiteurs_dans_file;
  struct shm_data * shmaddr;

  if (argc != 2) usage(argv[0], "time");
  time = atoi(argv[1]);
  if (time < 0) usage(argv[0], "time>=0");

  shmid = shm_acceder();

  // @TODO: tester valeur de retour
  shmaddr = shmat(shmid, NULL, 0);

  nb_visiteurs_dans_file = check_error_p(
    semctl(shmaddr->sem_entrer, 0, GETNCNT),
    "semctl"
  );

  debug(1, "Le visiteur arrive en direction du musée");
  if (nb_visiteurs_dans_file >= shmaddr->file) {
    debug(2, "Le visiteur n'avait pas envie de faire la file");
  } else {
    debug(2, "Le visiteur entre dans la file");
    P(shmaddr->sem_entrer);
    debug(2, "Le visiteur entre dans le musée");
    temps_de_visite(time);
    debug(2, "Le visiteur a fini la visite du musée");
    V(shmaddr->sem_entrer);
    debug(2, "Le visiteur est sorti du musée.");
  }

  debug(1, "Le visiteur est rentré chez lui");

  return EXIT_SUCCESS;
}
