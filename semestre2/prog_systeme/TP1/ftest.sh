#
# Fonctions et variables auxiliaires utilisées pour les différents
# tests.
#

PROG=./mysed

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
# supprime les fichiers temporaires

nettoyer ()
{
    set +x
    rm -rf $TMP*
    rm $LOG
    set -x
}

###############################################################################
# vérifie si le résultat est identique à la commande sed

test_file ()
{
    sed "s/$1/$2/g" $3 > $TMP-true
    cmp $TMP-true $4 || exit 1 
}

###############################################################################
# Crée un fichier ASCII random

creer_fichier ()
{
    cat /usr/share/dict/words | sort -R > $TMP-src
}

###############################################################################
# Crée toujours le même fichier ASCII

creer_fichier_std ()
{
    cat /usr/share/dict/words > $TMP-src
}

##############################################################################
# une sorte de chronomètre
#
# La commande date ne permet pas de récupérer l'heure avec une précision
# supérieure à la seconde (si l'on s'en tient à POSIX). On se fait donc
# la nôtre.
#

CHRONO=$TMP-chrono	# notre chronomètre

init_chrono ()
{
    cat > $CHRONO.c <<'EOF'
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

/*
 * Un petit programme pour implémenter un chronomètre :
 * Syntaxe :
 *	./a.out			// affiche la date correspondant à maintenant
 *	./a.out t1		// affiche la durée entre t1 et maintenant
 *	./a.out t1 min max	// code retour = 0 si durée \in [min, max]
 *
 */


typedef long double temps ;	// un point dans le temps ou une durée

temps lire_temps (const char *str)
{
    temps t ;
    int n ;

    n = sscanf (str, "%Lf", &t) ;
    if (n == 0)
    {
	fprintf (stderr, "date invalide (%s)\n", str) ;
	exit (1) ;
    }
    return t ;
}

temps duree (const char *str)
{
    struct timeval tv ;
    temps t1, t2 ;

    t1 = lire_temps (str) ;
    gettimeofday (&tv, NULL) ;
    t2 = tv.tv_sec + tv.tv_usec / 1000000.0 ;
    return t2 - t1 ;
}

int main (int argc, char *argv [])
{
    struct timeval tv ;
    temps d ;
    temps min, max ;
    int r = 0 ;

    switch (argc)
    {
	case 1 :	// démarrer le chrono => date-début
	    gettimeofday (&tv, NULL) ;
	    printf ("%jd.%06jd\n", (intmax_t)tv.tv_sec, (intmax_t)tv.tv_usec) ;
	    break ;

	case 2 :	// date-début => durée (= maintenant - début)
	    d = duree (argv [1]) ;
	    printf ("%Lf\n", d) ;
	    break ;

	case 4 :	// date-début min max => durée+exit(0) OU erreur+exit(1)
	    d = duree (argv [1]) ;
	    min = lire_temps (argv [2]) ;
	    max = lire_temps (argv [3]) ;
	    if (d < min)
	    {
		fprintf (stderr, "durée %Lf < %Lf\n", d, min) ;
		r = 1 ;
	    }
	    if (d > max)
	    {
		fprintf (stderr, "durée %Lf > %Lf\n", d, max) ;
		r = 1 ;
	    }
	    printf ("%Lf ok\n", d) ;
	    break ;

	default :
	    fprintf (stderr, "usage: %s [début [min max]]\n", argv [0]) ;
	    r = 1 ;
	    break ;

    }
    exit (r) ;
}
EOF
    cc -Wall -Wextra -Werror -o $CHRONO $CHRONO.c
}

###############################################################################
# Démarrer le chronomètre

chrono_start ()
{
    if [ ! -f $CHRONO ]; then
	init_chrono
    fi
    CHRONO_DEBUT=$($CHRONO)
}

###############################################################################
# Arrêter le chronomètre et vérifier que la durée passée en paramètre
# est dans l'intervalle spécifié
# code retour = 0 (ok) ou 1 (erreur : durée hors de l'intervalle)

chrono_stop ()
{
    local min="$1" max="$2"
    $CHRONO $CHRONO_DEBUT "$min" "$max"
}

set -x # demander au shell la trace des commandes exécutées
