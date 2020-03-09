if [ "$#" -ne 2 ]
then
  echo nb param different de 2
  exit 2
elif [ $1 -gt $2 ]
then
  echo le premier arg est gt the second
  exit 1
else
  for i in `seq $1 $2`
  do
    echo $i
  done
  exit 0
fi
