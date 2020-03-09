if [ "$#" -lt 1 ]
then
  echo il faut au moins un param
  echo code derreur "$?"
else
  for i in $*
  do
    sh type_fichier.sh $i
  done
fi
