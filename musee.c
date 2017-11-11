#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "musee.h"

// faire une fonction P et V qui fera un P et V pour un sémaphore
// histoire de rendre le code lisible




// quitte le programme en affichant la manière dont il doit être lancé
void usage(char * program_name, char * msg) {
  fprintf(stderr, "usage: %s %s\n", program_name, msg);
  exit(EXIT_FAILURE);
}

// affiche un simple message d'erreur
void error(char * msg) {
  fprintf(stderr, "\033[1;31mERROR: %s\033[0m\n", msg);
  exit(EXIT_FAILURE);
}

// affiche une erreur de primitive système et quitte
void error_p(char * msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

// teste si 'val' est différent de -1 (pas d'erreur); sinon on quitte
int check_error_p(int value, char * msg) {
  if (value == -1) error_p(msg);
  return value;
}


// SEMAPHORES

// créer un ensemble de sémaphores
int sem_creer(int val) {

  key_t k = check_error_p(
    ftok(FTOK_FILENAME, 1),
    "ftok"
  );

  int id  = check_error_p(
    semget(k, 1, IPC_CREAT | 0666),
    "semget"
  );

  check_error_p(
    semctl(id, 0, SETVAL, val),
    "semctl setval"
  );

  return id;

}

// accède à un ensemble de sémaphores
int sem_acceder(void) {

  key_t k = check_error_p(
    ftok(FTOK_FILENAME, 1),
    "ftok"
  );

  return check_error_p(
    semget(k, 0, 0),
    "semget"
  );

}


// supprime un ensemble de sémaphores
void sem_supprimer(int id) {
  check_error_p(
    semctl(id, 0, IPC_RMID, NULL),
    "semctl"
  );
}


// SEGMENTS DE MEMOIRE

// créer un segment de mémoire
int shm_create() {

  key_t k = check_error_p(
    ftok(FTOK_FILENAME, 1),
    "ftok"
  );

  int id = shmget(k, 0, 0);
  if (id != -1) shmctl(id, IPC_RMID, NULL);
  else if (errno != ENOENT) error_p("shmctl");

  return check_error_p(
    shmget(k, sizeof(struct shm_data), IPC_CREAT | 0666),
    "shmget"
  );

}

// accède à un segment de mémoire
int shm_access(void) {

  key_t k = check_error_p(
    ftok(FTOK_FILENAME, 1),
    "ftok"
  );

  return check_error_p(
    shmget(k, 0, 0),
    "shmget"
  );

}

// supprime un segment de mémoire à partir de son id
void shm_delete(int shmid) {
  check_error_p(
    shmctl(shmid, IPC_RMID, NULL),
    "shmctl"
  );
}
