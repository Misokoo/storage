#!/bin/sh 

#
# Tests avancés sur le versionnage des sauvegardes
#

. ./ftest.sh

###############################################################################
# Vérification que le système de versionnage des sauvegardes est
# fonctionnel. On vérifie que chaque version est identique à
# l'original et qu'on utilise bien des liens physiques lorsqu'un
# fichier n'est pas modifié entre deux sauvegardes
#
# Note : test_backup, mkdir_full, creat_arbo, test_fichier et test_version sont dans ftest.sh
#

# test sur la limitation à 10 copie de sauvegarde
creat_arbo
for i in $(seq 10); do
    $PROG $TMP-arbo 2> /dev/null >&2       ||         fail "$PROG: code retour sauvegarde arborescence"
done
$PROG $TMP-arbo     2> $TMP > /dev/null    || terr && fail "$PROG: plus de 10 versions possibles"
nettoyer

# test sur 2 versions identiques
creat_arbo
$PROG $TMP-arbo              2> /dev/null >&2 || fail "$PROG: code retour version identique (1)"
$PROG $TMP-arbo              2> /dev/null >&2 || fail "$PROG: code retour version identique (2)"
test_backup  $TMP-arbo 1     2> /dev/null >&2 || fail "$PROG: version identique: fichiers différents" 
test_version $TMP-arbo       2> /dev/null >&2 || fail "$PROG: vresion identique: pb avec lien physique"

# test avec des fichiers en moins
rm $TMP-arbo/l12/l23/1
$PROG $TMP-arbo              2> /dev/null >&2 || fail "$PROG: code retour fichier en moins"
test_backup  $TMP-arbo 2     2> /dev/null >&2 || fail "$PROG: fichier en moins : fichiers différents"

# test avec des fichiers en plus
mkdir_full $TMP-arbo/toto
$PROG $TMP-arbo              2> /dev/null >&2 || fail "$PROG: code retour fichier en plus"
test_backup  $TMP-arbo 3     2> /dev/null >&2 || fail "$PROG: fichier en plus : fichiers différents"

# test avec fichier modifié
echo "salut" >> $TMP-arbo/toto/1
$PROG $TMP-arbo                   2> /dev/null >&2 || fail "$PROG: code retour fichier modifié"
test_fichier $TMP-arbo toto/1 3 4    2> /dev/null >&2 || fail "$PROG: fichier modifié : fichiers indentiques"

echo "ok - 3/4"
nettoyer
exit 0
