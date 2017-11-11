#define FTOK_FILENAME "musee.c"

struct shm_datas {
  int capacite;
  int file;
  int nb_visiteurs;
  int est_ouvert;
  int controleur_present;
};


void usage(char * program_name, char * msg);
int shm_create();
int shm_access(void);
void shm_delete(int shmid);
