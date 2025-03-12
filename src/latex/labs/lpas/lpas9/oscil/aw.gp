# vim: set syntax=gnuplot:
set term epslatex size 12cm,5cm;
set output "lpas9/oscil/aw.tex";

w(t) = 10**t;
wr(z) = sqrt(1-2*z**2);
Ar(z) = A(wr(z),z);
T1(z) = 2 * z;
D(w,z) = (1-w**2)**2 + (T1(z)*w)**2;
P(w,z) = (1-w**2)/D(w,z);
Q(w,z) = -T1(z)*w/D(w,z);
A(w,z) = sqrt(P(w,z)**2 + Q(w,z)**2);
phi(w,z) = 180/pi * atan2(Q(w,z), P(w,z));

set key right top;
set xlabel '$\omega/\omega_0$';
set xtics (0.01, 0.10, 1.00, 10.00, 100.00);
set grid;
set ylabel '$A(\omega)$';
set ytics (0.0, 0.5, 1.0, 1.5, 2.0);
set format y '%2.1f';


set style line 1 lc "black"      lt 1 lw 2 pt 7 ps 1;
set style line 2 lc "red"        dt 2 lw 2 pt 7 ps 1;
set style line 3 lc "dark-green" dt 3 lw 2 pt 7 ps 1;
set style line 4 lc "blue"       dt 4 lw 2 pt 7 ps 1;
set style line 5 lc "brown"      dt 5 lw 2 pt 7 ps 1;

set logscale x 10;

plot sample [t=-2:2:0.02] '+' using (w(t)):(A(w(t),0.20)) with lines ls 1 title '$\zeta=0.20$', \
            [t=-2:2:0.02] '+' using (w(t)):(A(w(t),0.30)) with lines ls 2 title '$\zeta=0.30$', \
            [t=-2:2:0.02] '+' using (w(t)):(A(w(t),0.50)) with lines ls 3 title '$\zeta=0.50$', \
            [t=-2:2:0.02] '+' using (w(t)):(A(w(t),1.00)) with lines ls 4 title '$\zeta=1.00$', \
            [t=-2:2:0.02] '+' using (w(t)):(A(w(t),2.00)) with lines ls 5 title '$\zeta=2.00$', \
            t=0.20 '+' using (wr(t)):(Ar(t))  with points ls 1 title '$A(\omega_r)$', \
            t=0.30 '+' using (wr(t)):(Ar(t))  with points ls 2 notitle, \
            t=0.50 '+' using (wr(t)):(Ar(t))  with points ls 3 notitle;
