#!/bin/sh 

#
# Tests avec des sauvegardes uniques
#

. ./ftest.sh

###############################################################################
# Vérification que la sauvegarde d'un répertoire (ou d'une
# arborescence) est correctement réalisée (on compare le resultat du
# programme avec le répertoire original via la commande diff -arq
#
# Note : test_backup, mkdir_full et creat_arbo sont dans ftest.sh
#

# sauvegarde d'un répertoire vide
mkdir $TMP-empty
$PROG $TMP-empty                 2> /dev/null >&2 || fail "$PROG: code retour sauvegarde répertoire vide"
test_backup $TMP-empty 0         2> /dev/null >&2 || fail "$PROG: sauvegarde répertoire vide : fichiers différents"

# sauvegarde d'un répertoire avec fichiers reg
mkdir_full $TMP-full
$PROG $TMP-full                  2> /dev/null >&2 || fail "$PROG: code retour sauvegarde répertoire plein"
test_backup $TMP-full 0          2> /dev/null >&2 || fail "$PROG: sauvegarde répertoire plein : fichiers différents"

# sauvegarde d'une arborescence
creat_arbo
$PROG $TMP-arbo                  2> /dev/null >&2 || fail "$PROG: code retour sauvegarde arborescence"
test_backup $TMP-arbo 0          2> /dev/null >&2 || fail "$PROG: sauvegarde arborescence : fichiers différents"

echo "ok - 2/4"
nettoyer
exit 0
