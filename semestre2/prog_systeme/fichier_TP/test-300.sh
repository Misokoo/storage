#!/bin/sh 

#
# Tests avancés sur la suppression d'un répertoire
#

. ./ftest.sh

###############################################################################
# Vérification que la suppression fonctionne sur une arborescence de
# répertoires
#
# Note : creat_arbo est défini dans ftest.sh
#

# suppression d'une arborescence de répertoires
creat_arbo
$PROG $TMP-arbo                 2> /dev/null >&2 || fail "$PROG: code retour suppression arborescence"
test -e $TMP-arbo               2> /dev/null >&2 && fail "$PROG: suppression d'une arborescence : répertoire non supprimé"

# suppression d'une arborescence avec répertoire non modifiable
creat_arbo ; chmod -w $TMP-arbo/l11
$PROG $TMP-arbo                 2> /dev/null >&2 && fail "$PROG: code retour suppression arbo avec répertoire non W"
test -e $TMP-arbo/l12           2> /dev/null >&2 && fail "$PROG: suppression d'une arborescence : répertoire non supprimé"
chmod +w $TMP-arbo/l11

echo "ok - 3/4"
nettoyer
exit 0
