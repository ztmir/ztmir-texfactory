# vim: set syntax=gnuplot:
set term epslatex size 10cm, 10cm;
set output "lpas9/rlc/rough/nyquist.tex";
set key right bottom;

set xrange [-0.75: 1.50];
set xtics 1;
set mxtics 5;
set xlabel '$P(f_i)$';

set yrange [-2.25: 0.25];
set ytics 1;
set mytics 5;
set ylabel '$Q(f_i)$';

set grid xtics mxtics ytics mytics lt -1, lt 0;

set title "Charakterystyka Nyquista";
set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;

set arrow from -0.75, 0.00 to 1.60, 0.00 filled ls 1;
set arrow from  0.00,-2.25 to 0.00, 0.35 filled ls 1;

set datafile separator ",";
plot 'lpas9/rlc/rough/experiment.csv' using 5:6 with linespoints ls 1 notitle;
