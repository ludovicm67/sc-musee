% Rapport pour le TP noté de systèmes concurrents
% Lundi 20 novembre 2017
% Ludovic Muller

# Introduction

Ce TP noté avait pour but de nous montrer un exemple concret de l'utilisation
des sémaphores, en simulant la gestion d'un musée avec un directeur capable de
créer, ouvrir, fermer et supprimer un musée et un controleur qui gère les
entrées et sorties des visiteurs.

# Le segment de mémoire partagé

J'utilise un segment de mémoire partagé, dans le but de stocker un certain
nombre d'informations, qui peuvent être accessibles pour l'ensemble des
programmes de ce TP. 

```c
struct shm_data {
  int capacite; // argument capa passé lors de la création
  int file; // argument file passé lors de la création
  int est_ouvert; // 0 = fermé, 1 = ouvert

  int sem_controleur; // pour réveiller le controleur
  int sem_visiteurs; // pour gérer les visiteurs et la file (en attente dessus)
  int sem_lasts; // les derniers visiteurs
};
```

Les champs commençant par `sem_` contiennent les références vers les sémaphores
utilisées, ce qui évite de récupérer leurs identifiants avec un `semget` à
chaque fois.

Les commentaires devraient être suffisants pour comprendre l'utilité des autres
champs.

# Les sémaphores utilisés

Pour réaliser ce TP, j'ai eu besoin de trois sémaphores :

  - un pour gérer les visiteurs (la valeur du sémaphore correspond au nombre de
    visiteurs qui peuvent encore entrer dans le musée, et le nombre de processus
    en attente sur ce sémaphore correspond au nombre de visiteurs dans la file).

  - un autre pour réveiller le controleur (lors de l'ouverture, de la fermeture,
    et si besoin pour attendre la sortie du dernier visiteur)

  - et finalement un dernier, qui une fois le musée déclaré fermé par le
    directeur, le controleur va l'initialiser avec le nombre de visiteurs
    restant + 1 (pour ne rien bloquer), et chaque sortie de visiteur fera un P
    dessus, ce qui fait que lorsque le dernier visiteur passera, la valeur sera
    à un, et là le dernier visiteur pourra réveiller le controleur pour qu'il
    puisse partir (dans le cas où il y avait encore des visiteurs dans le musée
    lors de la fermeture).

# Principe de fonctionnement

Lors de la création du musée, le directeur va créer le segment de mémoire, en
remplissant les champs `capacite` et `file` avec les valeurs passées en argument
et va dire que le musée est actuellement fermé. Il va aussi créer et initialiser
mes trois sémaphores à 0, et stocker leurs identifiants dans le segment de
mémoire.

Le controleur arrive, et va faire un P, et va donc attendre. Lorsque le
directeur déclare le musée ouvert, il modifie le champ concerné dans le segment
de mémoire et fait un V pour que le controleur puisse passer à la suite.

Le controleur va donc changer la valeur du sémaphore des visiteurs pour la
passer à `capacite`, ce qui aura pour effet de faire rentrer les visiteurs.
Comme le contrôleur est présent on peut l'imaginer vérifier les entrées une à
une par exemple. Il fait un P pour attendre.

Lorsqu'un visiteur arrive, vérifie la valeur du sémaphore des visiteurs.
S'il vaut 0, alors il regarde le nombre de personnes dans la file (qui attendent
sur ce sémaphore; si ce nombre est supérieur à `file`, alors il rentre chez lui,
car il n'a pas envie de faire la file, sinon il fait un P dessus pour attendre
dans la file). S'il y a des places disponibles, il rentre dans le musée, visite
un certain temps (passé en argument, en ms), et si le musée est encore ouvert,
en sortant par le portique, le portique va dire qu'une place s'est libéré V,
sinon le portique de sortie ne fait rien de particulier, sauf s'il s'agit du
dernier visiteur, dans quel cas il va réveiller le controleur pour qu'il puisse
rentrer chez lui.

Lorsque le directeur déclare le musée fermé, il va réveiller le controleur comme
précédemment, qui va à son tour passer la valeur du sémaphore des visiteurs à
nouveau à 0, histoire de bloquer les entrées. S'il y a encore des visiteurs à
ce moment dans le musée, il va attendre que tous les visiteurs soient sortis
avant de rentrer chez lui, sinon il peut rentrer directement.


# Couverture du code

J'ai rajouté quelques tests dans un fichier `test-200.sh` dans le but de
parvenir à une couverture de code de 100%.
