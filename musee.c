#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "musee.h"

// faire une fonction P et V qui fera un P et V pour un sémaphore
// histoire de rendre le code lisible




// quitte le programme en affichant la manière dont il doit être lancé
void usage(char * program_name, char * msg) {
  fprintf(stderr, "usage: %s %s\n", program_name, msg);
  exit(EXIT_FAILURE);
}





// create a shm
int shm_create() {
  key_t k = ftok(FTOK_FILENAME, 1);
  int id = shmget(k, 0, 0);
  if (id != -1) shmctl(id, IPC_RMID, NULL);
  else if (errno != ENOENT) {
    fprintf(stderr, "Panique !\n");
    exit(1);    
  }
  return shmget(k, sizeof(struct shm_datas), IPC_CREAT | 0666);
}

// access a shm (returns -1 if no shm)
int shm_access(void) {
  key_t k = ftok(FTOK_FILENAME, 1);
  return shmget(k, 0, 0);
}

// delete a shm using his shmid
void shm_delete(int shmid) {
  shmctl(shmid, IPC_RMID, NULL);
}
