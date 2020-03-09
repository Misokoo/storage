#!/bin/sh 

#
# Tests basiques de vérification de syntaxe
#

. ./ftest.sh

###############################################################################
# Tests d'arguments invalides
# (on attend un code de retour non nul et un message
# d'erreur du type "usage: ..." pour être sûr que le
# problème de syntaxe est bien détecté)
#
# Note  : tu   = "test usage", défini dans ftest.sh

$PROG                 2> $TMP >&2 || tu && fail "mysed: nb arg (0) invalide"
$PROG a b c d         2> $TMP >&2 || tu && fail "mysed: nb arg (4) invalide"

# fichier source inexistant
$PROG a b $TMP-nimp42 2> $TMP >&2 || tu && fail "mysed: fichier source inexistant"

# fichier source non lisible
touch $TMP-titi ; chmod -r $TMP-titi	# crée un fichier et retire les droits
$PROG a b $TMP-titi 2> $TMP >&2 || tu && fail "mysed: fichier source sans droit de lecture"

# fichier source non régulier
mkdir $TMP-toto				# ce n'est pas un fichier régulier
$PROG a b $TMP-toto 2> $TMP >&2 || tu && fail "$PROG: fichier source n'est pas un fichier régulier"

# motif d'entrée trop long
touch $TMP-valid
MOTIF=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 1025 | head -n 1)
$PROG $MOTIF b $TMP.valid 2> $TMP >&2 || tu && fail "$PROG: motif d'entrée trop long"

# motif de sortie trop long
$PROG a $MOTIF $TMP-valid 2> $TMP >&2 || tu && fail "$PROG: motif de sortie trop long"

# syntaxe valide : ici ça doit fonctionner
$PROG a b $TMP-valid 2> $TMP >&2 || fail "$PROG: syntaxe valide produit un code de retour != 0"

echo "ok - 1/4"
nettoyer
exit 0
