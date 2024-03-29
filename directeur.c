#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musee.h"

// créer le musée
void musee_creer(char * program_name, int capacite, int file) {
  int shmid;
  struct shm_data * shmaddr;

  // on vérifie les arguments
  if (capacite <= 0) usage(program_name, "creer capacite(> 0 !!) file");
  if (file < 0)      usage(program_name, "creer capacite file(>= 0 !!)");

  debug(1, "création du musée");

  shmid = shm_creer();
  shmaddr = shm_at(shmid);

  shmaddr->capacite = capacite;
  shmaddr->file = file;
  shmaddr->est_ouvert = 0;

  shmaddr->sem_controleur = sem_creer(SEM_MUSEE_CONTROLEUR, 0);
  shmaddr->sem_visiteurs = sem_creer(SEM_MUSEE_VISITEURS, 0);
  shmaddr->sem_lasts = sem_creer(SEM_MUSEE_LASTS, 0);

  debug(2, "le musée a bien été créé !");
}

// ouvre le musée
void musee_ouvrir(void) {
  int shmid, is_controleur;
  struct shm_data * shmaddr;

  
  shmid = shm_acceder();
  shmaddr = shm_at(shmid);
  if (shmaddr->est_ouvert) error("Le musée est déjà ouvert !");

  is_controleur = sem_nb_attente(shmaddr->sem_controleur);
  if (!is_controleur) error("Le contrôleur n'est pas encore en poste !");

  debug(1, "ouverture du musée");
  shmaddr->est_ouvert = 1;

  V(shmaddr->sem_controleur);
  debug(2, "le musée a bien été ouvert !");
}

// ferme le musée
void musee_fermer(void) {
  int shmid;
  struct shm_data * shmaddr;

  debug(1, "fermeture du musée");
  
  shmid = shm_acceder();
  shmaddr = shm_at(shmid);
  if (!shmaddr->est_ouvert) error("Le musée n'a pas encore été ouvert !");
  shmaddr->est_ouvert = 0;

  V(shmaddr->sem_controleur);
  debug(2, "le musée a bien été fermé !");
}

// supprime le musée
void musee_supprimer(void) {
  int shmid;
  struct shm_data * shmaddr;

  debug(1, "suppression du musée");

  shmid = shm_acceder();
  shmaddr = shm_at(shmid);
  sem_supprimer(shmaddr->sem_controleur);
  sem_supprimer(shmaddr->sem_visiteurs);
  sem_supprimer(shmaddr->sem_lasts);
  shm_supprimer(shmid);
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
      // fall through
    case 4:
      if (argc == 4 && !strcmp(argv[1], "creer")) {
        musee_creer(argv[0], atoi(argv[2]), atoi(argv[3]));
        break;
      }
      // fall through
    default:
      usage(argv[0], "[creer capacite file | ouvrir | fermer | supprimer]");
  }

  return EXIT_SUCCESS;
}
