#!/bin/sh 

#
# Tests sur la gestion mémoire
#

. ./ftest.sh

###############################################################################
# Tester la gestion mémoire avec une arborescence
# Peu importe le code de retour du programme, c'est le code de retour
# de valgrind qui nous intéresse
#
# Note : creat_arbo et creat_arbo_long sont définis dans ftest.sh

creat_arbo
valgrind --leak-check=full --error-exitcode=100 $PROG $TMP-arbo > /dev/null
test $? = 100 && fail "test memoire 1/2"

# arborescence avec nom le plus long possible
creat_arbo_long
valgrind --leak-check=full --error-exitcode=100 $PROG $TMP-arbo > /dev/null
test $? = 100 && fail "test memoire 2/2"

echo "ok - 4/4"
nettoyer
exit 0
