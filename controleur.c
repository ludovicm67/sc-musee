#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  int shmid, nb_dans_musee;
  struct shm_data * shmaddr;

  if (argc != 1) usage(argv[0], "");
  debug(1, "le contrôleur est en poste");
  
  shmid = shm_acceder();
  shmaddr = shmat(shmid, NULL, 0);

  P(shmaddr->sem_controleur); // est-ce qu'il peut faire entrer des gens ?
  sem_set_value(shmaddr->sem_visiteurs, shmaddr->capacite);

  P(shmaddr->sem_controleur); // lorsque le directeur déclare le musée fermé
  nb_dans_musee = shmaddr->capacite - sem_get_value(shmaddr->sem_visiteurs);
  sem_set_value(shmaddr->sem_visiteurs, 0);

  // attends qu'il n'y ait plus de visiteurs s'il y en a encore
  if (nb_dans_musee) P(shmaddr->sem_controleur);

  debug(1, "le contrôleur s'en va");

  return EXIT_SUCCESS;
}
