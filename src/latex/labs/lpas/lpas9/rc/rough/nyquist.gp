# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 14cm, 8cm;
set output "lpas9/rc/rough/nyquist.tex";
set key right bottom;

set xrange [-0.20: 1.20];
set xtics 0.2;
set mxtics 2;

set yrange [-0.60: 0.20];
set ytics 0.2;
set mytics 2;

set grid xtics mxtics ytics mytics;

set xlabel '$P(f_i)$';
set ylabel '$Q(f_i)$';
set title "Charakterystyka Nyquista";
set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;

set arrow from -0.20, 0.00 to 1.25, 0.00 filled ls 1;
set arrow from  0.00,-0.60 to 0.00, 0.25 filled ls 1;

set datafile separator ",";
plot 'lpas9/rc/rough/experiment.csv' using 5:6 with linespoints ls 1 notitle;
