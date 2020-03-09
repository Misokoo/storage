./select_month.sh trafic.dat $1
cat << EOT
set terminal png
set xtics 1
plot "$1.dat" using 1:2 with linespoints
EOT
| gnuplot > blabla.png
