#
# Fonctions et variables auxiliaires utilisées pour les différents
# tests.
#

PROG=./backup

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
# comparaison de tous les fichiers d'une sauvegarde avec leur version
# originale

test_backup ()
{
    name=$(basename $1)
    bpath=".BACKUP_$name/$2"
    diff -arq $1 $bpath
}

###############################################################################
# vérifie si le nombre de liens physiques de chaque fichier régulier
# d'une arborescence régulier est égal à 2

test_subdir()
{
    for i in $(ls $1); do
	HL=$(stat $1/$i -c "%F/%h")
	echo $1/$i
	if [ $(dirname $HL) = "fichier" ]; then
	    if [ $(basename $HL) -ne 2 ]; then
		return 1
	    fi
	else
	    test_subdir $1/$i
	fi
    done
}

###############################################################################
# lance la fonction récursive test_subdir avec le bon nom de répertoire

test_version ()
{
    NAME=$(basename $1)
    DIR=".BACKUP_$NAME/1"

    test_subdir $DIR
}

###############################################################################
# comparaison de deux fichiers de deux sauvegardes différentes
# renvoie vrai si les fichiers sont différents, faux s'ils sont identiques

test_fichier ()
{
    NAME=$(basename $1)
    PREV=".BACKUP_$NAME/$3/$2"
    NEXT=".BACKUP_$NAME/$4/$2"
    ! cmp $PREV $NEXT
}

set -x # demander au shell la trace des commandes exécutées
