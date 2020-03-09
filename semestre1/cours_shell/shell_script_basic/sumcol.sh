maliste=`cut -f2 -d' ' qte.dat | tail -n+2`
sum=0
for i in $maliste
do
  sum=$(($sum+$i))
done
echo la somme est de la colonne $1 est $sum
