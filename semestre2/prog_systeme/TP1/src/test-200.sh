#!/bin/sh 

#
# Tests avec des motifs simples
#

. ./ftest.sh

# creer_fichier est dans ftest.sh
creer_fichier

###############################################################################
# Vérification que la substitution demandée est correctement réalisée
# (on compare le resultat du programme avec le résultat d'un remplacement
# équivalent effectué avec la commande sed (de base sous Unix)
#
# Note : test_file est dans ftest.sh
#

# remplacement d'un seul caractère
$PROG a b $TMP-src                > $TMP-resu || fail "$PROG: remplacement d'un caractère - pg terminé avec une erreur"
test_file a b $TMP-src $TMP-resu 2> /dev/null || fail "$PROG: remplacement d'un caractère - le résultat produit non valide"

# remplacement par une chaîne de même longueur
$PROG allo word $TMP-src		> $TMP-resu	|| fail "$PROG: remplacement d'une chaîne de même longueur - pg terminé avec une erreur"
test_file allo word $TMP-src $TMP-resu	2> /dev/null	|| fail "$PROG: remplacement d'une chaîne de même longueur - résultat produit non valide"

# remplacement par une chaîne plus longue
$PROG smooth XXXXXXXXXX $TMP-src		> $TMP-resu	|| fail "$PROG: remplacement par une chaîne plus longue - pg terminé avec une erreur"
test_file smooth XXXXXXXXXX $TMP-src $TMP-resu	2> /dev/null	|| fail "$PROG: remplacement par une chaîne plus longue - résultat produit non valide"

# remplacement par une chaîne plus courte
$PROG ement X $TMP-src			> $TMP-resu	|| fail "$PROG: remplacement par une chaîne plus courte - pg terminé avec une erreur"
test_file ement X $TMP-src $TMP-resu	2> /dev/null	|| fail "$PROG: remplacement par une chaîne plus courte - résultat produit non valide"

echo "ok - 2/4"
nettoyer
exit 0
