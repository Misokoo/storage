#!/bin/sh 

#
# Tests sur la gestion mémoire
#

. ./ftest.sh

# creat_arbo est dans ftest.sh
creat_arbo

###############################################################################
# Tester la gestion mémoire avec une arborescence
# Peu importe le code de retour du programme, c'est le code de retour
# de valgrind qui nous intéresse

valgrind --leak-check=full --error-exitcode=100 $PROG $TMP-arbo > /dev/null
test $? = 100 && fail "test memoire 1/3"

valgrind --leak-check=full --error-exitcode=100 $PROG $TMP-arbo > /dev/null
test $? = 100 && fail "test memoire 2/3"

valgrind --leak-check=full --error-exitcode=100 $PROG $TMP-arbo /dev/null
test $? = 100 && fail "test memoire 3/3"

echo "ok - 4/4"
nettoyer
exit 0
