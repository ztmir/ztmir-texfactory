# vim: set syntax=gnuplot:
set term epslatex size 11cm, 6.875cm;
set output "lpas9/inert/nyquist.tex";
set key right top;
set grid;
set parametric;
set xrange [-0.50: 1.50];
set yrange [-0.75: 0.50];
set xtics ( 0.00, 0.50, 1.00);
set ytics (-0.50, 0.00);
set xlabel '$P(\omega)$';
set ylabel '$Q(\omega)$';
set style line 1 lc "black" lt 1 lw 2;

set arrow from -0.50, 0.00 to 1.60, 0.00 filled ls 1;
set arrow from  0.00,-0.75 to 0.00, 0.60 filled ls 1;
set arrow from  0.00, 0.00 to 0.50,-0.50 filled ls 1;

set label 1 '$\omega=0$'        at 1.00, 0.00 point pt 7 offset 0.00, 0.50;
set label 2 '$\omega=\infty$'   at 0.00, 0.00 point pt 7 offset 0.00, 0.50;
set label 3 '$\omega=\omega_s$' at 0.50,-0.50 point pt 7 offset 0.00,-0.50;

w(t) = -tan(t*pi/180.0);
P(w) = 1/(1+w**2);
Q(w) = -w/(1+w**2);
plot sample [t=0:-90:-0.9] '+' using (P(w(t))):(Q(w(t))) with lines ls 1 title '$G(j \omega)$';
