#define FTOK_FILENAME "musee.c"

enum sem_name {
  SEM_MUSEE_OUVERT = 1,
  SEM_MUSEE_ENTRER
};

struct shm_data {
  int capacite;
  int file;
  int est_ouvert;

  int sem_ouvert;
  int sem_entrer;
};

  // int nb_visiteurs;
  // int est_ouvert;
  // int controleur_present;

void debug(int level, char * msg);

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
int sem_creer(enum sem_name n, int val);

// accède à un ensemble de sémaphores
int sem_acceder(void);

// supprime un ensemble de sémaphores
void sem_supprimer(int id);

void P(int id);
void V(int id);


// SEGMENTS DE MEMOIRE

// créer un segment de mémoire
int shm_creer();

// accède à un segment de mémoire
int shm_acceder_no_err(void);
int shm_acceder(void);

// supprime un segment de mémoire à partir de son id
void shm_supprimer(int shmid);
