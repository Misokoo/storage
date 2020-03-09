#!/bin/sh 

#
# Tests sur la gestion mémoire
#

. ./ftest.sh

###############################################################################
# Tester la gestion mémoire avec bcp de processus fils
# Peu importe le code de retour du programme, c'est le code de retour
# de valgrind qui nous intéresse
#
# Note gen_value est définie dans ftest.sh

VAL=`gen_value 1000`

valgrind --leak-check=full --trace-children=yes --error-exitcode=100 $PROG 100 $VAL > /dev/null
test $? = 100 && fail "test memoire 1/3"

valgrind --leak-check=full --trace-childre=yes --error-exitcode=100 $PROG 10 $VAL > /dev/null
test $? = 100 && fail "test memoire 2/3"

valgrind --leak-check=full --trace-children=yes --error-exitcode=100 $PROG 100 $VAL /dev/null
test $? = 100 && fail "test memoire 3/3"

echo "ok - 4/4"
nettoyer
exit 0
