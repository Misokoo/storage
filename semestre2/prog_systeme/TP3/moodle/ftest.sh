#
# Fonctions et variables auxiliaires utilisées pour les différents
# tests.
#

PROG=./maxval

TEST=$(basename $0 .sh)

TMP=/tmp/$TEST-$$
LOG=$TEST.log

# Rediriger stderr vers le log pour voir les résultats des tests
# On conserve stdout inchangé, il faudra le rediriger à la demande
exec 2> $LOG

set -u # erreur si utilisation d'une variable non définie

###############################################################################
# Une fonction qu'il vaudrait mieux ne pas avoir à appeler...

fail ()
{
    echo "==> Échec du test '$TEST' sur '$1'."
    echo "==> Log : '$LOG'."
    echo "==> Exit"
    exit 1
}

###############################################################################
# Teste la présence du traditionnel message : "usage: prog arg..." dans $TMP
# Renvoie vrai si trouvé, faux si pas trouvé

tu ()
{
    # rappel: "! cmd" => inverse le code de retour de cmd
    ! grep -q "usage: " $TMP
}

###############################################################################
# Teste la présence d'un message sur la sortie erreur
# Renvoie vrai si trouvé, faux si pas trouvé

terr ()
{
    if [ $(wc -c < $TMP) -eq 0 ]; then
	return 0
    fi
    return 1
}

###############################################################################
# supprime les fichiers temporaires

nettoyer ()
{
    set +x
    rm -rf $TMP*
    rm $LOG
    rm -r .BACKUP_*
    set -x
}

###############################################################################
# comparaison de deux fichiers de deux sauvegardes différentes
# renvoie vrai si les fichiers sont différents, faux s'ils sont identiques

gen_value ()
{
    for i in `seq $1`; do
	NB=$((`od -An -N1 -i /dev/urandom` % 127))
	echo $NB
    done
}

max_value ()
{
    VAL=0
    for i in $@; do
	if [ $i -gt $VAL ]; then
	    VAL=$i
	fi
    done

    echo $VAL
}

set -x # demander au shell la trace des commandes exécutées
