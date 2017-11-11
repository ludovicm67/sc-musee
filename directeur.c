#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musee.h"

void musee_creer(char * program_name, int capacite, int file) {
  // on vérifie les arguments
  if (capacite <= 0) usage(program_name, "creer capacite(> 0 !!) file");
  if (file < 0)      usage(program_name, "creer capacite file(>= 0 !!)");

  shm_create();
}

void musee_ouvrir(void) {
  
}

void musee_fermer(void) {
  
}

void musee_supprimer(void) {
  int shmid = shm_access();
  if (shmid != -1) shm_delete(shmid);
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
