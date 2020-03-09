var=$(ls -l $1 | cut -f1 -d" ")
echo $var
if [ ! -e $1 ]
then
  echo fichier doesnt exists
  exit 1
elif [ $var = "-rw-------" ]
then
  echo fichier ordinaire, seul le propriétiare peut lire/écrire
elif [ $var = "-rw-r--r--" ]
then
  echo fichier ordinaire, le groupe et les autres peuvent seulement lire
elif [ $var = "-rwxr-xr-x" ]
then
  echo executable, le groupe et les autres peuvent seulement lire et exécuter
else
  echo Type non enreregistré
fi
