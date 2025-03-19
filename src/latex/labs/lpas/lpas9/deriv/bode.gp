# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 14cm,7cm;
set output "lpas9/deriv/bode.tex";
set key right top Left;
set xtics (0.01, 0.10,  1.00, 10.00, 100.00);
set ytics ('-3 dB' -3, '-20 dB' -20, '-40 dB' -40, '-60 dB' -60);
set y2tics ('$0\degree$' 0, '$45\degree$' 45, '$90\degree$' 90);
set grid xtics ytics y2tics;
set xlabel '$\omega/\omega_s$';
set ylabel '$M(\omega)$';
set y2label '$\varphi(\omega)$';

set style line 1 lc "black" lt 1 lw 3 pt 7 ps 1;
set style line 2 lc "black" dt 4 lw 3 pt 7 ps 1;
set style line 3 lc "black" lt 1 lw 1 pt 7 ps 1;

set logscale x 10;

w(t) = 10**t;
P(w) = w**2/(1+w**2);
Q(w) = w/(1+w**2);
A(w) = sqrt(P(w)**2 + Q(w)**2);
M(w) = 20 * log10(A(w));
phi(w) = 180/pi * atan2(Q(w), P(w));

set label 1 '20 dB/dek' at 0.1, -20 offset -0.5,0.5 rotate by 50 right front;
set label 2 '$(\omega_A, M_A)$' at 2E-3, M(2E-3) point ls 1 offset 0.5,-0.5;
set label 3 '$(\omega_B, M_B)$' at 0.2, M(0.2) right point ls 1 offset -0.5,0.5;

set arrow from 1,0 to 1E-3,-60 ls 3 nohead;

plot sample [t=-3:3:0.03] '+' using (w(t)):(M(w(t))) with lines ls 1 title '$M(\omega)$' axes x1y1, \
     [t=-3:3:0.03] '+' using (w(t)):(phi(w(t))) with lines ls 2 title '$\varphi(\omega)$' axes x1y2;
