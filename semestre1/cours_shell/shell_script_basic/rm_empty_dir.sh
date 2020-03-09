read n
if [ -d "$n" ]
then
  if [ `ls $n/ | wc -c` -eq 0 ]
  then
    rmdir $n
    echo le dossier a ete supprime
  else
    echo dossier pas vide
  fi
else
  echo $n pas un dossier
fi
