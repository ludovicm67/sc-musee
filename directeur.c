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

  debug(1, "création du musée");

  shmid = shm_creer();

  // @TODO: tester valeur de retour
  shmaddr = shmat(shmid, NULL, 0);

  shmaddr->capacite = capacite;
  shmaddr->file = file;
  shmaddr->est_ouvert = 0;

  shmaddr->sem_entrer = sem_creer(SEM_MUSEE_ENTRER, capacite);
  shmaddr->sem_ouvert = sem_creer(SEM_MUSEE_OUVERT, 0);

  debug(2, "le musée a bien été créé !");
}

void musee_ouvrir(void) {
  int shmid;
  struct shm_data * shmaddr;

  debug(1, "ouverture du musée");
  shmid = shm_acceder();
  shmaddr = shmat(shmid, NULL, 0);
  shmaddr->est_ouvert = 1;
  debug(2, "le musée a bien été ouvert !");
}

void musee_fermer(void) {
  int shmid;
  struct shm_data * shmaddr;

  debug(1, "fermeture du musée");
  shmid = shm_acceder();
  shmaddr = shmat(shmid, NULL, 0);
  shmaddr->est_ouvert = 0;
  debug(2, "le musée a bien été fermé !");
}

void musee_supprimer(void) {
  int shmid;

  debug(1, "suppression du musée");

  debug(4, "lancement de la suppression des segments de mémoire...");
  shmid = shm_acceder();
  shm_supprimer(shmid);
  debug(3, "suppression des segments de mémoire terminé !");
  debug(4, "lancement de la suppression des sémaphores...");
  int semid = sem_acceder();
  sem_supprimer(semid);
  debug(3, "suppression des sémaphores terminé !");
  debug(2, "suppression du musée terminé !");
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
