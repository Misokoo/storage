chaine=$1
grep $chaine personnes.dat | cut -f1,3 -d' ' | tee acompter
wc -l acompter
