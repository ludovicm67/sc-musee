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
  if (shmid == -1) {
    printf("Le musée est inexistant.\n");
    return EXIT_SUCCESS;
  }

  // @TODO: tester valeur de retour
  shmaddr = shmat(shmid, NULL, 0);

  printf("FILE=%d\n", shmaddr->file);
  printf("CAPA=%d\n", shmaddr->capacite);


  return EXIT_SUCCESS;
}
