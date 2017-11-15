#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  int shmid, s_ouvert, s_entrer;
  struct shm_data * shmaddr;

  if (argc != 1) usage(argv[0], "");
  debug(1, "le contrôleur est en poste");
  
  shmid = shm_acceder();
  shmaddr = shmat(shmid, NULL, 0);

  s_ouvert = sem_acceder(SEM_MUSEE_OUVERT);
  s_entrer = sem_acceder(SEM_MUSEE_ENTRER);
  P(s_ouvert); // est-ce qu'il peut faire entrer des gens ?
  sem_set_value(s_entrer, shmaddr->capacite);
  P(s_ouvert); // demande de sortie du controleur
  sem_set_value(s_entrer, 0);

  debug(1, "le contrôleur s'en va");

  return EXIT_SUCCESS;
}
