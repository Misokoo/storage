if [ "$#" -ne "1" ]
then
  echo pas 1 seul argument
  exit
elif [ -f "$1" ]
then
  echo "$1 : fichier"
elif [ -d "$1" ]
then
  echo "$1 : dossier"
else
  echo "$1 rien du tout"
fi
