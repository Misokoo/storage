#
# Fonctions et variables auxiliaires utilisées pour les différents
# tests.
#

PROG=./myrmdir

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
# Renvoie vrai si sortie vide, faux sinon

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
    set -x
}

###############################################################################
# création d'un répertoire avec un nb aléatoire de fichiers reg
# la taille et le contenu de chaque fichier est également aléatoire

mkdir_full ()
{
    mkdir $1
    NBFILE=$(od -An -N1 -i /dev/urandom)
    for i in $(seq $NBFILE); do
	SIZE=$(od -An -N2 -d /dev/urandom)
	head -c $SIZE /dev/urandom > $1/$i
    done
}

###############################################################################
# création d'une arborescence de répertoires
# chaque sous-répertoire est créé via la fonction mkdir_full

creat_arbo ()
{
    mkdir $TMP-arbo
    for l1 in 1 2 3; do
	D1=l1$l1
	mkdir_full $TMP-arbo/$D1
	for l2 in 1 2 3 4; do
	    D2=l2$l2
	    mkdir_full $TMP-arbo/$D1/$D2
	done
    done
}

###############################################################################
# création d'une arborescence de répertoires
# proche de la taille max d'un chemin

creat_arbo_long ()
{
    CUR_DIR=`pwd`

    D="$TMP-arbo/"
    mkdir $D
    cd $D

    for i in `seq 0 14`; do
	D=`cat /dev/urandom | tr -dc "a-zA-Z0-9" | fold -w 255 | head -n 1`
	mkdir $D
	cd $D

	if [ $i -eq 14 ]; then
	    NB=`pwd | wc -c`
	    NB=$((4096 - $NB))
	    touch `cat /dev/urandom | tr -dc "a-zA-Z0-9" | fold -w $NB | head -n 1`
	fi
    done

    cd $CUR_DIR
}

set -x # demander au shell la trace des commandes exécutées
