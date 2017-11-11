#define FTOK_FILENAME "musee.c"

struct shm_data {
  int capacite;
  int file;
};

  // int nb_visiteurs;
  // int est_ouvert;
  // int controleur_present;


// quitte le programme en affichant la manière dont il doit être lancé
void usage(char * program_name, char * msg);

// affiche un simple message d'erreur
void error(char * msg);

// affiche une erreur de primitive système et quitte
void error_p(char * msg);

// teste si 'val' est différent de -1 (pas d'erreur); sinon on quitte
int check_error_p(int value, char * msg);


// SEMAPHORES

// créer un ensemble de sémaphores
int sem_creer(int val);

// accède à un ensemble de sémaphores
int sem_acceder(void);

// supprime un ensemble de sémaphores
void sem_supprimer(int id);


// SEGMENTS DE MEMOIRE

// créer un segment de mémoire
int shm_create();

// accède à un segment de mémoire
int shm_access(void);

// supprime un segment de mémoire à partir de son id
void shm_delete(int shmid);
