# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 10.5cm,9cm;
set output "lpas9/oscil/zar.tex";

Ar(z) = 1/(2*z*sqrt(1-z**2));
Z(a) = sqrt(0.5*(1-sqrt(1-(1.0/a**2))));
cZ(z) = abs((1-z**2)/(2*z**2-1)); # cond_z(Ar(z))

set key top right offset -1,-1;
set grid;

set xlabel '$A_r$';
set xtics 1, 0.5, 5;
set mxtics;

set ytics;
set mytics;
set ylabel '$\zeta$';
set format y '%.3g';

set y2range [1:2.4];
set y2tics 1, 0.2, 2.4 add (cZ(Z(1.1)));
set y2label '$\text{cond}_{\zeta}$';
set format y2 '%.3g';

set style line 1 lc "black" lt 1 lw 3 pt 7 ps 1;
set style line 2 lc "blue"  dt 2 lw 3 pt 7 ps 1;
set style line 3 lc "blue"  dt 0 lw 1 pt 7 ps 1;

set label 1 at second 1.1, cZ(Z(1.1)) point ls 3;
set arrow from second 1.1, cZ(Z(1.1)) to second 5, cZ(Z(1.1)) ls 3 nohead;
set arrow from second 1.1, 1 to second 1.1, cZ(Z(1.1)) ls 3 nohead;

plot sample [z=0.1:sqrt(2)/2] '+' using (Ar(z)):(z)  with lines ls 1 title '$\zeta$' axes x1y1, \
            [z=0.1:0.60] '+' using (Ar(z)):(cZ(z)) with lines ls 2 title '$\text{cond}_{\zeta}$' axes x1y2;
