donnee=$1
shift
for i in $*
do
  sh select_month.sh $donnee $i
  sh make_gplot.sh $i | gnuplot > $i.png
done
