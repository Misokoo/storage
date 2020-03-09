#!/bin/sh 

#
# Tests avec des valeurs aléatoires et 1 ou 2 processus
#

. ./ftest.sh

###############################################################################
# Vérification que le programme termine bien avec la valeur max passée en param
#
# Note gen_value et max_value sont définies dans ftest.sh

# un seul processus
$PROG 10 1 2 3 4 5 6 7 8   2> /dev/null >&2 || ! test $? -eq 8 && fail "exit code != du max (8 valeurs)"

VAL=`gen_value 100`
$PROG 100 $VAL             2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (100 valeurs)"

VAL=`gen_value 1000`
$PROG 1000 $VAL            2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (1000 valeurs)"

# deux processus fils
$PROG 4 1 2 3 4 5 6 7 8    2> /dev/null >&2 || ! test $? -eq 8 && fail "exit code != du max (8 valeurs - 2 processus)"

VAL=`gen_value 100`
$PROG 50 $VAL              2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (100 valeurs - 2 processus)"

VAL=`gen_value 1000`
$PROG 500 $VAL             2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (1000 valeurs - 2 processus)"

echo "ok - 2/4"
nettoyer
exit 0
