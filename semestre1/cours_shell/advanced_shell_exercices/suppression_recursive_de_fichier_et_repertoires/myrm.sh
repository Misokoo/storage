chmod 777 myrm.sh
for d in $*
do
  for f in `ls $d`
  do
    if [ -f $d/$f ]
    then
      ./confirm.sh $d/$f
    elif [ -d $d/$f ]
    echo "$d/$f est un dossier"
    then
      nbligne=`ls $d/$f | wc -l`
      echo $nbligne
      if [ $nbligne -eq 0 ]
      then
      rmdir $d/$f
      echo "dossier $d/$f supprime"
      else
        echo le dossier $d/$f
        ./myrm.sh $d/$f
      fi
      rmdir $d/$f
      echo "dossier $d/$f supprime"
    fi
  done
done
