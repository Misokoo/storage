#erreur not found souvent pour les espaces, sans espaces autour du = pour laffectation, si on affecte une commance on met ` (du 7)`
x=1
y=2
#let "a=$a + 1" à utiliser quavec bash blabla.sh
z=$(($x+$y))
z=$(($z+1))
echo $z
x=5/2
echo $x #àa affiche 5/2 et pas 2.5
x=`echo "5/2"|bc -l` #attention aux espaces cest la merde
echo $x
u=`id -u`
d=`date`
echo utilisateur $u : $d
