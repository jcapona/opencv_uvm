set term wxt 1

set xlabel "Green"
set ylabel "Red"
set zlabel "Blue"
unset key
set xrange [0:255]
set yrange [0:255]
set zrange [0:255]
set title "Solo manzana roja"
set ticslevel 0
splot 'apple_3_mask.csv' using 1:2:3 with points palette pointsize 1 pointtype 0

set term wxt 2

set xlabel "Green"
set ylabel "Red"
set zlabel "Blue"
unset key
set xrange [0:255]
set yrange [0:255]
set zrange [0:255]
set title "Foto completa"
set view 127,93
set ticslevel 0
splot 'apple_3.csv' using 1:2:3 with points palette pointsize 1 pointtype 0
pause -1

