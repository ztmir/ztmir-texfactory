# vim: set syntax=gnuplot:
#set term epslatex size 16cm,22cm;
#set term epslatex size 12cm,16.5cm;
set term epslatex size 16cm,7.3cm;
set output "lab11/sredsin.tex";
#set multiplot layout 3,1 rowsfirst
set grid;
set yrange [-1.25:1.25];
set xrange [-pi-0.25:pi+0.25];
set style line 1 lc "black" lt 1 lw 2 pt 7 ps 1;
set style line 2 lc "black" lt 1 lw 2 pt 2 ps 1;
set y2range [-0.005:0.005]
set y2tics
set key spacing 1.30
unset xlabel
set key right bottom Right autotitle columnhead;
set ylabel "$u,\\hat{u}$";
set y2label "$u_i-\\hat{u}_i$";
plot [-pi:pi] sin(x) with lines ls 1 title "$u(\\varphi) = \\sin{\\varphi}$" axes x1y1, \
     input1 using 2:4 with points ls 1 axes x1y1, \
     input1 using 2:5 with points ls 2 axes x1y2;
#set key center bottom Right autotitle columnhead;
#set ylabel "$\\dot{u},\\dot{\\hat{u}}$";
#set y2label "$\\dot{u}_i-\\dot{\\hat{u}}_i$";
#plot [-pi:pi] cos(x) with lines ls 1 title "$\\dot{u}(\\varphi) = \\cos{\\varphi}$" axes x1y1, \
#     input1 using 2:7 with points ls 1 axes x1y1, \
#     input1 using 2:8 with points ls 2 axes x1y2;
#set key left bottom Right autotitle columnhead;
#set ylabel "$\\ddot{u},\\ddot{\\hat{u}}$";
#set y2label "$\\ddot{u}_i-\\ddot{\\hat{u}}_i$";
#set xlabel "$\\varphi$";
#plot [-pi:pi] -sin(x) with lines ls 1 title "$\\ddot{u}(\\varphi) = -\\sin{\\varphi}$" axes x1y1, \
#     input1 using 2:10 with points ls 1 axes x1y1, \
#     input1 using 2:11 with points ls 2 axes x1y2;
#unset multiplot
