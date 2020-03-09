#!/bin/sh 

#
# Tests avec des répertoires ne contenant que des fichiers reg
#

. ./ftest.sh

###############################################################################
# Vérification que la suppression d'un répertoire (vide ou ne
# contenant que des fichiers réguliers est réalisée correctement)
#
# Note : mkdir_full est défini dans ftest.sh
#

# suppression d'un répertoire vide
mkdir $TMP-empty
$PROG $TMP-empty                 2> /dev/null >&2 || fail "$PROG: code retour suppression répertoire vide"
test -e $TMP-empty               2> /dev/null >&2 && fail "$PROG: suppression répertoire vide : répertoire non supprimé"

# suppression d'un répertoire non vide
mkdir_full $TMP-full
$PROG $TMP-full                  2> /dev/null >&2 || fail "$PROG: code retour suppression répertoire plein"
test -e $TMP-full                2> /dev/null >&2 && fail "$PROG: suppression répertoire plein : répertoire non supprimé"

echo "ok - 2/4"
nettoyer
exit 0
