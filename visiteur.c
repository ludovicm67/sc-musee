#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "musee.h"

// fonction qui permet de faire attendre le visiteurs un temps en ms
void temps_de_visite(int ms) {
  struct timespec ts;
  ts.tv_sec = (time_t) (ms / 1000);
  ts.tv_nsec = (ms - ((long) ts.tv_sec * 1000)) * 1000000;
  nanosleep(&ts, NULL);
}

int main(int argc, char * argv[]) {
  int time, shmid, nb_visiteurs_dans_file, nb_dans_musee;
  struct shm_data * shmaddr;

  if (argc != 2) usage(argv[0], "time");
  time = atoi(argv[1]);
  if (time < 0) usage(argv[0], "time>=0");

  shmid = shm_acceder();

  // @TODO: tester valeur de retour
  shmaddr = shmat(shmid, NULL, 0);

  nb_visiteurs_dans_file = check_error_p(
    semctl(shmaddr->sem_visiteurs, 0, GETNCNT),
    "semctl"
  );

  debug(1, "Le visiteur arrive en direction du musée");
  if (nb_visiteurs_dans_file >= shmaddr->file) {
    debug(2, "Le visiteur n'avait pas envie de faire la file");
  } else {
    debug(2, "Le visiteur entre dans la file");
    P(shmaddr->sem_visiteurs);
    debug(2, "Le visiteur entre dans le musée");
    temps_de_visite(time);
    debug(2, "Le visiteur a fini la visite du musée");
    if (shmaddr->est_ouvert) { // si le musée est ouvert
      debug(3, "Le visiteur passe par le portique ce qui libère une place");
      V(shmaddr->sem_visiteurs);
    } else { // si le musee est fermé
      debug(3, "Le visiteur va vers la sortie du musée qui est fermé");
      nb_dans_musee = shmaddr->capacite - sem_get_value(shmaddr->sem_visiteurs);
      // et s'il n'y a plus personne, on indique au controleur qu'il peut partir
      if (nb_dans_musee <= 1) {
        debug(3, "Sort par le portique...");
        debug(3, "...qui dit au controleur que c'était le dernier visiteur");
        V(shmaddr->sem_controleur);
        debug(3, "le controleur peut donc rentrer chez lui !");
      }
    }
    debug(2, "Le visiteur est sorti du musée.");
  }

  debug(1, "Le visiteur est rentré chez lui");

  return EXIT_SUCCESS;
}
