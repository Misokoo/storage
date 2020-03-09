
read user
while [ $user != "/quit" ]
do
  ps -u $user
  read user
done
