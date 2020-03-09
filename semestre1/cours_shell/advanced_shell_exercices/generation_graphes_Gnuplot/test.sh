set terminal png
set output 'image.png'
plot 'nov.dat' using 1:3 with linespoints
