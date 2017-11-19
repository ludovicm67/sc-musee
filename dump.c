#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "musee.h"


int main(int argc, char * argv[]) {
  int shmid;
  struct shm_data * shmaddr;

  if (argc != 1) usage(argv[0], "");
  shmid = shm_acceder_no_err();

  // je ne teste que le segment de mémoire
  if (shmid == -1) error("Le musée est inexistant.");

  if ((shmaddr = shmat(shmid, NULL, 0)) == (void *) -1) error("shmat a échoué");
  printf("CONTENU DU SHM:\n");
  printf(" - file = %d\n", shmaddr->file);
  printf(" - capacite = %d\n", shmaddr->capacite);
  printf(" - est_ouvert = %d\n", shmaddr->est_ouvert);
  printf(" - sem_controleur = %d\n", shmaddr->sem_controleur);
  printf(" - sem_visiteurs = %d\n\n\n", shmaddr->sem_visiteurs);


  return EXIT_SUCCESS;
}
