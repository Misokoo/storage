#!/bin/sh 

#
# Tests avancés avec bcp de processus et de valeurs
#

. ./ftest.sh

###############################################################################
# Vérification que le programme termine bien avec la valeur max passée en param
#
# Note : gen_value et max_value sont définies dans ftest.sh

# 1000 valeurs et 18 process fils"
VAL=`gen_value 1000`
$PROG 100 $VAL          2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (18 process)"

# 1000 valeurs et 180 process fils"
VAL=`gen_value 1000`
$PROG 10 $VAL           2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (180 process)"

# 1000 valeurs et 1800 process fils"
VAL=`gen_value 1000`
$PROG 1 $VAL            2> /dev/null >&2 || ! test $? -eq `max_value $VAL` && fail "exit code != du max (1800 process)"

echo "ok - 3/4"
nettoyer
exit 0
