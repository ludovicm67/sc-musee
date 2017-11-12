#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "musee.h"

void musee_creer(char * program_name, int capacite, int file) {
  int shmid;
  struct shm_data * shmaddr;

  // on vérifie les arguments
  if (capacite <= 0) usage(program_name, "creer capacite(> 0 !!) file");
  if (file < 0)      usage(program_name, "creer capacite file(>= 0 !!)");

  shmid = shm_creer();

  // @TODO: tester valeur de retour
  shmaddr = shmat(shmid, NULL, 0);

  shmaddr->capacite = capacite;
  shmaddr->file = file;

  sem_creer(0);
}

void musee_ouvrir(void) {
  shm_acceder();
}

void musee_fermer(void) {
  shm_acceder();
}

void musee_supprimer(void) {
  int shmid = shm_acceder();
  shm_supprimer(shmid);

  int semid = sem_acceder();
  sem_supprimer(semid);
}


int main(int argc, char * argv[]) {

  switch (argc) {
    case 2:
      if (!strcmp(argv[1], "ouvrir")) {
        musee_ouvrir();
        break;
      } else if (!strcmp(argv[1], "fermer")) {
        musee_fermer();
        break;
      } else if (!strcmp(argv[1], "supprimer")) {
        musee_supprimer();
        break;
      }
      __attribute__ ((fallthrough));
    case 4:
      if (argc == 4 && !strcmp(argv[1], "creer")) {
        musee_creer(argv[0], atoi(argv[2]), atoi(argv[3]));
        break;
      }
      __attribute__ ((fallthrough));
    default:
      usage(argv[0], "[creer capacite file | ouvrir | fermer | supprimer]");
  }

  return EXIT_SUCCESS;
}
