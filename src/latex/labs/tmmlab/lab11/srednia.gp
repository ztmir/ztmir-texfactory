# vim: set syntax=gnuplot:
set encoding utf8;
set term epslatex size 16cm,6cm;
set output "lab11/srednia.tex";
set key right bottom Left;
#set size ratio 1;
set grid;
set yrange [0:8];
set xrange [-4:4];
set xtics ("i-3" -3, "i-2" -2, "i-1" -1, "i" 0, "i+1" 1, "i+2" 2, "i+3" 3);
unset ytics;
set label 1 "$u_i$" at 0.3,4;
set label 2 "$\\upsilon_0 = \\hat{u}_i$" at -0.8,3.5;
set label 3 "$\\varepsilon_{-2}$" at -2.9,5.5;
set label 4 "$\\upsilon_{-2}$" at -1.7,2.5;
set arrow 1 from  0.2,0.0 rto  0.0,7.5;
set arrow 2 from  0.0,7.5 rto  0.2,0.0 nohead;
set arrow 3 from -0.2,0.0 rto  0.0,6.8;
set arrow 4 from  0.0,6.8 rto -0.2,0.0 nohead;
set arrow 5 from -2.5,5.0  to -2.5,6.0;
set arrow 6 from -2.5,5.0  to -1.8,5.0 nohead;
set arrow 7 from -2.5,6.0  to -1.9,6.0 nohead;
set arrow 8 from -1.8,0.0  to -1.8,5.0;
set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;
set style line 2 lc "black" lt 1 lw 2 pt 2 ps 1;
plot "-" with points ls 1 title "w. surowe", \
     "-" with linespoints ls 2 smooth csplines title "wielomian", \
     "-" with points ls 2 title "w. wyrównane";
-3 3
-2 6
-1 5
 0 7.5
 1 6
 2 6
 3 3
e
-3.5 2.7
-3 3.5
-2 5
-1 6
 0 6.8
 1 6.8
 2 5.5
 3 3.3
 3.5 3
e
 0 6.8
