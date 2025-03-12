# vim: set syntax=gnuplot:
set term epslatex size 12cm,10cm;
set output "lpas9/oscil/bode.tex";

w(t) = 10**t;
wr(z) = sqrt(1-2*z**2);
Ar(z) = A(wr(z),z);
T1(z) = 2 * z;
D(w,z) = (1-w**2)**2 + (T1(z)*w)**2;
P(w,z) = (1-w**2)/D(w,z);
Q(w,z) = -T1(z)*w/D(w,z);
A(w,z) = sqrt(P(w,z)**2 + Q(w,z)**2);
M(w,z) = 20 * log10(A(w,z));
phi(w,z) = 180/pi * atan2(Q(w,z), P(w,z));

set multiplot layout 2,1;
set lmargin at screen 0.15;

set key left bottom;
set xtics (0.01, 0.10, 1.00, 10.00, 100.00);
set ytics ('10 dB' 10, '0 dB' 0, '-40 dB' -40, '-80 dB' -80);
set yrange [-80:10];
set grid;
set ylabel '$M(\omega)$';


set style line 1 lc "black"      lt 1 lw 2 pt 7 ps 1;
set style line 2 lc "red"        dt 2 lw 2 pt 7 ps 1;
set style line 3 lc "dark-green" dt 3 lw 2 pt 7 ps 1;
set style line 4 lc "blue"       dt 4 lw 2 pt 7 ps 1;
set style line 5 lc "brown"      dt 5 lw 2 pt 7 ps 1;
set style line 6 lc "black"      lt 1 lw 1 pt 7 ps 1;

set logscale x 10;
set label 1 '-40 dB/dek' at 10, -40 offset 0.5,0.5 rotate by -35 left front;
set label 2 '$(\omega_A, M_A)$' at 10, M(10,1.0) right point ls 1 offset -0.5, -0.5;
set label 3 '$(\omega_B, M_B)$' at 60, M(60,1.0) right point ls 1 offset -0.5,-0.5;

set arrow 1 from 1,0 to 1E2,-80 ls 6 nohead;

plot sample [t=-2:2:0.02] '+' using (w(t)):(M(w(t),0.20)) with lines ls 1 title '$\zeta=0.20$', \
            [t=-2:2:0.02] '+' using (w(t)):(M(w(t),0.30)) with lines ls 2 title '$\zeta=0.30$', \
            [t=-2:2:0.02] '+' using (w(t)):(M(w(t),0.50)) with lines ls 3 title '$\zeta=0.50$', \
            [t=-2:2:0.02] '+' using (w(t)):(M(w(t),1.00)) with lines ls 4 title '$\zeta=1.00$', \
            [t=-2:2:0.02] '+' using (w(t)):(M(w(t),2.00)) with lines ls 5 title '$\zeta=2.00$';

unset key;
unset label 1;
unset label 2;
unset label 3;
unset arrow 1;

set yrange [-180:0];
set ytics ('$0\degree$' 0, '$-90\degree$' -90, '$-180\degree$' -180);
set ylabel '$\varphi(\omega)$';
set xlabel '$\omega/\omega_0$';

plot sample [t=-2:2:0.02] '+' using (w(t)):(phi(w(t),0.20)) with lines ls 1 title '$\zeta=0.20$', \
            [t=-2:2:0.02] '+' using (w(t)):(phi(w(t),0.30)) with lines ls 2 title '$\zeta=0.30$', \
            [t=-2:2:0.02] '+' using (w(t)):(phi(w(t),0.50)) with lines ls 3 title '$\zeta=0.50$', \
            [t=-2:2:0.02] '+' using (w(t)):(phi(w(t),1.00)) with lines ls 4 title '$\zeta=1.00$', \
            [t=-2:2:0.02] '+' using (w(t)):(phi(w(t),2.00)) with lines ls 5 title '$\zeta=2.00$';
unset multiplot;
