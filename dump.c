#include <stdlib.h>
#include <stdio.h>
#include "musee.h"

// affiche le statut d'un sémaphore
void print_sem(int semid) {
  printf("\n\nCONTENU DU SÉMAPHORE (#%d) :\n", semid);
  printf(" - valeur : %d\n", sem_get_value(semid));
  printf(" - nb en attente : %d\n", sem_nb_attente(semid));
}

int main(int argc, char * argv[]) {
  int shmid;
  struct shm_data * shmaddr;

  if (argc != 1) usage(argv[0], "");
  shmid = shm_acceder_no_err();

  // je ne teste que le segment de mémoire
  if (shmid == -1) error("Le musée est inexistant.");

  shmaddr = shm_at(shmid);
  printf("CONTENU DU SHM:\n");
  printf(" - file = %d\n", shmaddr->file);
  printf(" - capacite = %d\n", shmaddr->capacite);
  printf(" - est_ouvert = %d\n", shmaddr->est_ouvert);
  printf(" - sem_controleur = %d\n", shmaddr->sem_controleur);
  printf(" - sem_visiteurs = %d\n", shmaddr->sem_visiteurs);
  printf(" - sem_lasts= %d\n", shmaddr->sem_lasts);

  print_sem(shmaddr->sem_controleur);
  print_sem(shmaddr->sem_visiteurs);
  print_sem(shmaddr->sem_lasts);

  return EXIT_SUCCESS;
}
