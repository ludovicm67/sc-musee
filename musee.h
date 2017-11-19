#define FTOK_FILENAME "musee.c"

// juste pour rendre le code plus beau à lire
enum sem_name {
  SEM_MUSEE_CONTROLEUR = 1,
  SEM_MUSEE_VISITEURS,
  SEM_MUSEE_LASTS
};

struct shm_data {
  int capacite; // argument capa passé lors de la création
  int file; // argument file passé lors de la création
  int est_ouvert; // 0 = fermé, 1 = ouvert

  int sem_controleur; // pour réveiller le controleur
  int sem_visiteurs; // pour gérer les visiteurs et le file (en attente dessus)
  int sem_lasts; // les derniers visiteurs
};

// permet d'afficher les messages de debug en fonction de DEBUG_MUSEE
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
int sem_creer(enum sem_name n, int val);
void sem_set_value(int id, int val);
int sem_get_value(int id);
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
