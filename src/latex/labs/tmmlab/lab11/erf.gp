# vim: set syntax=gnuplot:
set term epslatex size 10cm,6cm;
set output "lab11/erf.tex";
set key right bottom Left;
set grid;
set xrange [0:4];
set xtics (0, 1, 2, 3, 4);
set ytics (0, 50, 68, 95.4);
set format y '%2.1f\%%';
set xlabel "t";
set ylabel "P(t)";
set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;
set style line 2 lc "black" lt 1 lw 2 pt 2 ps 1;
plot 100*erf(x/sqrt(2)) with lines ls 1 title '$P(t)$';
