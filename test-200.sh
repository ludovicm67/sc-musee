#!/bin/sh

#
# Tests supplémentaires
#

. ./ftest.sh

# on nettoie tout
$V ./directeur supprimer >&2
$V ./dump 2>&1 | grep "inexistant" >&2 \
  || fail "dump ne détecte pas que le musée est inexistant"

# on lance notre batterie de tests
$V ./directeur ouvrir >&2 && fail "ne peut pas ouvrir un musée inexistant !"
$V ./directeur fermer >&2 && fail "ne peut pas fermer un musée inexistant !"
$V ./controleur >&2 && fail "il ne faut pas de controleur sans musée !"
$V ./directeur creer 3 2 >&2 || fail "erreur de création"
$V ./directeur ouvrir >&2 && fail "ne peut pas ouvrir sans controleur"
$V ./directeur fermer >&2 && fail "ne peut pas fermer un musée non ouvert !"
$V ./controleur& >&2 || fail "le controleur n'a pas pu se lancer correctement."
sleep 0.1
$V ./directeur ouvrir >&2 || fail "erreur d'ouverture"
$V ./directeur ouvrir >&2 && fail "musée déjà ouvert !"
$V ./visiteur 1000 &
$V ./visiteur 1000 &
sleep 0.5
$V ./directeur fermer >&2 || fail "erreur de fermeture"
sleep 2
$V ./dump >&2 || fail "erreur lors du debug"


# on nettoie tout, comme si de rien n'était
$V ./directeur supprimer >&2

exit 0
