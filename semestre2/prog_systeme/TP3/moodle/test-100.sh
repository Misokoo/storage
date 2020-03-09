#!/bin/sh 

#
# Tests basiques de vérification de syntaxe
#

. ./ftest.sh

###############################################################################
# Tests d'arguments invalides
# (on attend un code de retour non nul et un message
# d'erreur du type "usage: ..." pour être sûr que le
# problème de syntaxe est bien détecté)
#
# Note  : tu   = "test usage", défini dans ftest.sh

$PROG                 2> $TMP > /dev/null || tu && fail "$PROG: nb arg (0) invalide"
$PROG a               2> $TMP > /dev/null || tu && fail "$PROG: nb arg (1) invalide"
$PROG `seq 1026`      2> $TMP > /dev/null || tu && fail "$PROG: trop de valeurs"

# valeurs interdites sur max_chunk_size
$PROG a 1 2 3 4       2> $TMP > /dev/null || tu && fail "$PROG: max_chunck_size n'est pas un nombre"
$PROG 0 1 2 3 4       2> $TMP > /dev/null || tu && fail "$PROG: max_chunck_size < 1"
$PROG 1025 1 2 3 4    2> $TMP > /dev/null || tu && fail "$PROG: max_chunck_size  > 1024"

# valeurs interdites sur les nombres
$PROG 3 1 a 127 2     2> $TMP > /dev/null || tu && fail "$PROG: valeur n'est pas un nombre"
$PROG 3 1 127 4 -2    2> $TMP > /dev/null || tu && fail "$PROG: valeur négative"
$PROG 3 1 127 243     2> $TMP > /dev/null || tu && fail "$PROG: valeur > 127"

# syntaxe valide : ici ça doit fonctionner sans erreur
$PROG 3 0 0 0         2> $TMP > /dev/null || fail "$PROG: syntaxe valide produit une erreur"

echo "ok - 1/4"
nettoyer
exit 0
