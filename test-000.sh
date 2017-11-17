#!/bin/sh

#
# Tests supplémentaires
#

. ./ftest.sh

# on nettoie tout
$V ./directeur supprimer >&2

# on lance notre batterie de tests
$V ./directeur ouvrir >&2    && fail "ne peut pas ouvrir un musée inexistant !"
$V ./directeur fermer >&2    && fail "ne peut pas fermer un musée inexistant !"
$V ./controleur >&2          && fail "il ne faut pas de controleur sans musée !"
$V ./directeur creer 1 1 >&2 || fail "erreur de création"
$V ./directeur fermer >&2    && fail "ne peut pas fermer un musée non ouvert !"
$V ./directeur ouvrir >&2    || fail "erreur d'ouverture"
$V ./directeur ouvrir >&2    && fail "musée déjà ouvert !"
$V ./directeur fermer >&2    || fail "erreur de fermeture"

# on nettoie tout, comme si de rien n'était
$V ./directeur supprimer >&2

exit 0
