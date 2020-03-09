#! /bin/bash
year=2015
value=100
echo "$year;$value"
OUTPUT=out.dat
echo "$year;$value" > OUTPUT
echo "$year;$value" >> OUTPUT
echo "on rajoute la boucle for ">>OUTPUT
for i in `seq  0 3`
do
  echo "$(($year+$i));$(($value+10*$i))">>OUTPUT
done

echo "on affiche la boucle avec un parametre defini par le user">>OUTPUT
for i in `seq  0 3`
do
  echo "$(($year+$i));$(($1+10*$i))">>OUTPUT
done

echo "value de 100 et les annees en paramètres">>OUTPUT
value=100
for i in $@
do
  echo "$i;$value">>OUTPUT
  value=$(($value+10))
  ##echo "$(($$i+$i));$(($value+10*$i))">>OUTPUT
done


if [ $# -lt 2 ]
then
  echo "wllh t'as pas assez de parametres">>OUTPUT
else
  echo "1er arg = value initial,les autres paramètres sont les années">>OUTPUT
  value=$1
  shift
  for i in $@
  do
    echo "$i;$value">>OUTPUT
    value=$(($value+10))
  done
fi
