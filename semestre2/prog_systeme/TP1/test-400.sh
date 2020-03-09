#!/bin/sh 

#
# Tests sur la gestion mémoire
#

. ./ftest.sh

# creer_fichier est dans ftest.sh
creer_fichier_std

###############################################################################
# Tester la gestion mémoire avec différents motifs
# Peu importe le code de retour du programme, c'est le code de retour
# de valgrind qui nous intéresse

valgrind --leak-check=full --error-exitcode=100 $PROG a b $TMP-src > /dev/null
test $? = 100 && fail "test memoire 1/3"

valgrind --leak-check=full --error-exitcode=100 $PROG inejad XXXXXXXXXXXX $TMP-src > /dev/null
test $? = 100 && fail "test memoire 2/3"

valgrind --leak-check=full --error-exitcode=100 $PROG ement XX $TMP-src > $TMP-resu /dev/null
test $? = 100 && fail "test memoire 3/3"

echo "ok - 4/4"
nettoyer
exit 0
