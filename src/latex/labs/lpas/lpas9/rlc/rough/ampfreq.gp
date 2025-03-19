# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 12cm,8cm;
set output "lpas9/rlc/rough/ampfreq.tex";

set key right top;
set xlabel '$f_i$';

set logscale x 10;
set xrange [10-1E-10:10000];
set mxtics 10;
set format x "$10^{%T}$ Hz";

set ylabel '$A(f_i)$';
set yrange [0:2];
set ytics 0.5;
set mytics 5;
set format y '%2.1f';

set grid xtics mxtics ytics mytics lt -1, lt 0;

set style line 1 lc "black"      lt 1 lw 2 pt 7 ps 1;

set datafile separator ",";
plot 'lpas9/rlc/rough/experiment.csv' using 1:7 with linespoints ls 1 title columnheader;
