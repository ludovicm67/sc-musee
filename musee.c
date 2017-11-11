#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "musee.h"

// faire une fonction P et V qui fera un P et V pour un sémaphore
// histoire de rendre le code lisible

int creer_shm() {
  key_t k = ftok("musee.c", 1);
  int id = shmget(k, 0, 0);
  if (id != -1) shmctl(id, IPC_RMID, NULL);
  else if (errno != ENOENT) {
    fprintf(stderr, "Panique !\n");
    exit(1);    
  }
  return shmget(k, sizeof(struct shm_datas), IPC_CREAT | 0666);
}

void supprimer_shm(int shmid) {
  shmctl(shmid, IPC_RMID, NULL);
}