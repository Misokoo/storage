touch f
ls -l f
mkdir d
cp f d/f
rmdir d
ls -l d
chmod 666 d
ls -l
cd d
find / -name "passwd"
#find -size +1 -perm 111 > hello avec locto cest exact
find -size +1M -perm -u=x
#option -amin n  ==> dernier acces il y a n minutes
find . -amin -60
find /home/mikoso/ -type d -user mikoso -perm /g=r,o=r
