#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  // on vérifie s'il y a un bien un argument
  if (argc < 2) {
    fprintf(
      stderr,
      "usage: %s [creer capacite file| ouvrir | fermer | supprimer]\n",
      argv[0]
    );
    exit(EXIT_FAILURE);
  }

  // on vérifie si la commande est bonne
  if (strcmp(argv[1], "creer")
    && strcmp(argv[1], "ouvrir")
    && strcmp(argv[1], "fermer")
    && strcmp(argv[1], "supprimer")) {
    fprintf(
      stderr,
      "usage: %s [creer capacite file| ouvrir | fermer | supprimer]\n",
      argv[0]
    );
    exit(EXIT_FAILURE);
  }

  // si on est dans créer
  if (!strcmp(argv[1], "creer")) {
    int capacite, file;
    if (argc != 4) {
      fprintf(stderr, "usage: %s creer capacite file\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    capacite = atoi(argv[2]);
    file = atoi(argv[3]);

    if (capacite <= 0) {
      fprintf(stderr, "usage: %s creer capacite(> 0 !!) file\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    if (file <= 0) {
      fprintf(stderr, "usage: %s creer capacite file(> 0 !!)\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  // si on est dans ouvrir
  if (!strcmp(argv[1], "ouvrir")) {
    if (argc != 2) {
      fprintf(stderr, "usage: %s ouvrir\n", argv[0]);
      exit(EXIT_FAILURE);      
    }
  }

  // si on est dans fermer
  if (!strcmp(argv[1], "fermer")) {
    if (argc != 2) {
      fprintf(stderr, "usage: %s fermer\n", argv[0]);
      exit(EXIT_FAILURE);      
    }
  }

  // si on est dans supprimer
  if (!strcmp(argv[1], "supprimer")) {
    if (argc != 2) {
      fprintf(stderr, "usage: %s supprimer\n", argv[0]);
      exit(EXIT_FAILURE);      
    }
  }

  (void) argc;
  (void) argv;
  return EXIT_SUCCESS;
}
