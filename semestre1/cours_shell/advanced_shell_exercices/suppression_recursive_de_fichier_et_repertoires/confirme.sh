if [ $# -eq 1 ]
then
  echo "etes vous sur de vouloir supprimer le fichier $1 ? (o/n) "
  read r
  if [ $r = "o" ]
  then
    rm $1
    exit 1
  else
    exit 1
  fi
else
  echo il faut un seul parametre
  exit 2
fi
