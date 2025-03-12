# vim: set syntax=gnuplot:
set term epslatex size 12cm,10cm;
set output "lpas9/rlc/rough/bode.tex";

set multiplot layout 2,1;
set lmargin at screen 0.15;

set datafile separator ",";

set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;

set key left bottom;

set logscale x 10;

set xrange [9.999:10000];
set mxtics 10;
set format x "$10^{%T}$ Hz";

set yrange [-80:10];
set ytics 40;
set mytics 4;
set format y "%g dB";
set ylabel '$M(f_i)$';

set grid xtics mxtics ytics mytics lt -1, lt 0;

plot 'lpas9/rlc/rough/experiment.csv' using 1:8 with linespoints ls 1 title columnheader;

unset label 1;
unset label 2;
unset label 3;
unset arrow 1;

set xlabel '$f_i$';

set yrange [-180:0];
set format y "$%g\\degree$"
set ytics 90;
set mytics 3;
set ylabel '$\varphi(f_i)$';


plot 'lpas9/rlc/rough/experiment.csv' using 1:9 with linespoints ls 1 title columnheader, \
     '' using 1:9:10 with labels offset 0.75,0.25 notitle;

unset multiplot;
