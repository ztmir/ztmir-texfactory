# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 9cm, 9cm;
set output "lpas9/oscil/nyquist.tex";
set key right bottom opaque;
set grid;
set parametric;
set xrange [-1.20: 1.70];
set yrange [-2.70: 0.70];
set xlabel '$P(\omega)$';
set ylabel '$Q(\omega)$';
set style line 1 lc "black" lt 1 lw 2;
set style line 2 lc "red"   dt 2 lw 2;
set style line 3 lc "green" dt 3 lw 2;
set style line 4 lc "blue"  dt 4 lw 2;
set style line 5 lc "brown" dt 5 lw 2;

set arrow from -1.00, 0.00 to 1.60, 0.00 filled ls 1;
set arrow from  0.00,-2.50 to 0.00, 0.50 filled ls 1;

set style textbox 1 opaque noborder;

w(t) = -tan(t*pi/360.0);
T1(z) = 2 * z;
D(w,z) = (1-w**2)**2 + (T1(z)*w)**2;
P(w,z) = (1-w**2)/D(w,z);
Q(w,z) = -T1(z) * w/D(w,z);

set label 1 '$\omega=0$'        at 1.00, 0.00 point pt 7 offset 0.00, 0.50;
set label 2 '$\omega=\infty$'   at 0.00, 0.00 point pt 7 offset 0.00, 0.50;
set label 3 '$\omega=\omega_0$' at 0.00, Q(1,2.00) left  point pt 7 offset  0.30, 0.30 boxed bs 1 front;
set label 4 '$\omega=\omega_0$' at 0.00, Q(1,1.00) right point pt 7 offset -0.50,-0.30 boxed bs 1 front;
set label 5 '$\omega=\omega_0$' at 0.00, Q(1,0.50) right point pt 7 offset -0.50,-0.30 boxed bs 1 front;
set label 6 '$\omega=\omega_0$' at 0.00, Q(1,0.30) right point pt 7 offset -0.50,-0.30 boxed bs 1 front;
set label 7 '$\omega=\omega_0$' at 0.00, Q(1,0.20) right point pt 7 offset -0.50,-0.30 boxed bs 1 front;

plot sample [t=0:-180:-0.9] '+' using (P(w(t),0.20)):(Q(w(t),0.20)) with lines ls 1 title '$\zeta=0.20$', \
            [t=0:-180:-0.9] '+' using (P(w(t),0.30)):(Q(w(t),0.30)) with lines ls 2 title '$\zeta=0.30$', \
            [t=0:-180:-0.9] '+' using (P(w(t),0.50)):(Q(w(t),0.50)) with lines ls 3 title '$\zeta=0.50$', \
            [t=0:-180:-0.9] '+' using (P(w(t),1.00)):(Q(w(t),1.00)) with lines ls 4 title '$\zeta=1.00$', \
            [t=0:-180:-0.9] '+' using (P(w(t),2.00)):(Q(w(t),2.00)) with lines ls 5 title '$\zeta=2.00$';
