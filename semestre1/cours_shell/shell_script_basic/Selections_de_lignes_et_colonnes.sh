cut -f3 -d' ' personnes.dat > OUTPUT
cut -f1,3 -d' ' personnes.dat > OUTPUT
cut -c1-3 personnes.dat > OUTPUT
head -n 3 personnes.dat >OUTPU
tail -n 3 personnes.dat >OUTPUT
tail -n+2 personnes.dat >OUTPUT
cat personnes.dat | grep "Alice">OUTPUT
grep "Alice" personnes.dat>OUTPUT
sort -d personnes.dat>OUTPUT
sort +2d -3 personnes.dat>OUTPUT
tail -n 2 personnes.dat | cut -f1,3 -d' ' > OUTPUT

# rev underscoreFile > verlan
# cut -f1-3 -d'_' verlan>verlan2
# rev verlan2>OUTPUT
rev underscoreFile | cut -f1-3 -d'_' | rev > OUTPUT


#man tee à voir
#ctrl d ou e pour quitter 
