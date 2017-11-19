#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "musee.h"

void debug(int level, char * msg) {
  int env_lvl;
  char * env_debug = getenv("DEBUG_MUSEE");
  if (env_debug == NULL) return;
  env_lvl = atoi(env_debug);
  if (env_lvl >= level) {
    fprintf(stderr, "\033[1;34mDEBUG: %s\033[0m\n", msg);
    fflush(stderr);
  }
}

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
int sem_creer(enum sem_name n, int val) {

  key_t k = check_error_p(
    ftok(FTOK_FILENAME, n),
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

// Permet de changer la valeur d'un sémaphore
void sem_set_value(int id, int val) {
  check_error_p(
    semctl(id, 0, SETVAL, val),
    "semctl setval"
  );
}

// Permet de récupérer la valeur d'un sémaphore
int sem_get_value(int id) {
  return check_error_p(
    semctl(id, 0, GETVAL),
    "semctl setval"
  );
}


// supprime un ensemble de sémaphores
void sem_supprimer(int id) {
  check_error_p(
    semctl(id, 0, IPC_RMID, NULL),
    "semctl"
  );
}


void P(int id) {
  struct sembuf s [1] = {
    {0, -1, 0}
  };

  check_error_p(
    semop(id, s, 1),
    "semop"
  );
}

void V(int id) {
  struct sembuf s [1] = {
    {0, 1, 0}
  };

  check_error_p(
    semop(id, s, 1),
    "semop"
  );
}


// SEGMENTS DE MEMOIRE

// créer un segment de mémoire
int shm_creer() {

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
// (on ne fait pas le test sur l'existance ici)
int shm_acceder_no_err(void) {
  key_t k = check_error_p(
    ftok(FTOK_FILENAME, 1),
    "ftok"
  );
  return shmget(k, 0, 0);
}

// accède à un segment de mémoire
int shm_acceder(void) {
  return check_error_p(
    shm_acceder_no_err(),
    "shmget"
  );
}

// supprime un segment de mémoire à partir de son id
void shm_supprimer(int shmid) {
  check_error_p(
    shmctl(shmid, IPC_RMID, NULL),
    "shmctl"
  );
}
