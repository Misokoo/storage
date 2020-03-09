#!/bin/sh 

#
# Tests basiques de vérification de syntaxe
#

. ./ftest.sh

###############################################################################
# Tests d'arguments invalides
# (on attend un code de retour non nul et un message
# d'erreur pour être sûr que le problème de syntaxe est bien détecté)
#
# Note  : tu   = "test usage", défini dans ftest.sh
#         terr = "test sortie erreur", défini dans ftest.sh

$PROG                 2> $TMP > /dev/null || tu && fail "$PROG: nb arg (0) invalide"
$PROG a b             2> $TMP > /dev/null || tu && fail "$PROG: nb arg (2) invalide"

# fichier source inexistant
$PROG xyz             2> $TMP > /dev/null || terr && fail "$PROG: répertoire source inexistant"

# fichier source n'est pas un répertoire
touch $TMP-titi                      # crée un fichier régulier
$PROG $TMP-titi       2> $TMP > /dev/null || terr && fail "$PROG: répertoire source n'est pas un répertoire"

# répertoire source non lisible
mkdir $TMP-toto ; chmod -r $TMP-toto # crée un répertoire et retire le droit R
$PROG $TMP-toto       2> $TMP > /dev/null || terr && fail "$PROG: répertoire source n'est pas lisible"

# répertoire source non vide et non accessible
touch $TMP-toto/coucou               # crée un fichier régulier dans le répertoire
chmod +r-x $TMP-toto                 # remet le droit R et supprime le droit X sur le répertoire
$PROG $TMP-toto       2> $TMP > /dev/null || terr && fail "$PROG: répertoire source non vide et non accessible"

# syntaxe valide : ici ça doit fonctionner
chmod +x $TMP-toto
$PROG $TMP-toto       2> $TMP > /dev/null || fail "$PROG: syntaxe valide produit un code de retour != 0"

echo "ok - 1/4"
nettoyer
exit 0
