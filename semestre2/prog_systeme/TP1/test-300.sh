#!/bin/sh 

#
# Tests avancés
#

. ./ftest.sh

# creer_fichier est dans ftest.sh
creer_fichier_std

###############################################################################
# Test sur une occurence du motif située à cheval entre 2 tampons
#

$PROG inejad XXXXXXXXXXXX $TMP-src			> $TMP-resu	|| fail "$PROG: test avec motif tronqué - pg terminé avec une erreur"
test_file inejad XXXXXXXXXXXX $TMP-src $TMP-resu	2> /dev/null	|| fail "$PROG: test avec motif tronqué - résultat produit non valide"


###############################################################################
# Test sur un fichier binaire
# Note : ce fichier peut contenir toutes
# les combinaisons possibles d'écrire un octet, dont l'octet nul

$PROG a b /bin/ls  > $TMP-resu	|| fail "$PROG: test avec fichier binaire - pg terminé avec une erreur"
test_file a b /bin/ls $TMP-resu	2> /dev/null	|| fail "$PROG: test avec fichier binaire - résultat produit non valide"


###############################################################################
# Test de performance sur la vitesse d'exécution du programme
#
# On mesure le temps d'exécution du programme à l'aide d'un chronomètre
# initialisé et appelé dans ftest.sh.
#

init_chrono
chrono_start
$PROG inejad XXXXXXXXXXXX $TMP-src > $TMP-resu || fail "$PROG: test perf - pg terminé avec une erreur"
# le programme doit s'exécuter en moins de 0,5 s (entre 0 et 0,5 s)
chrono_stop 0 0.5 >&2			       || fail "$PROG: test perf - pg trop lent (lecture / écriture par caractère ?)"


echo "ok - 3/4"
nettoyer
exit 0
