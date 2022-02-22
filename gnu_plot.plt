set boxwidth 3
set xlabel "Square Matrix Size"
set ylabel "Time(s)"
set yrange [-0.1:0.7]
set ytics -0.1,0.1,0.7
set xrange [-20:520]
set xtics -20,20,520
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb"#daf7a6" behind
plot 'pthread_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set terminal png size 1920,1080
set output "pthread_plot.png"
replot
set term postscript eps color blacktext "Helvetica" 24
set output "pthread_plot.eps"
plot 'pthread_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set output
set terminal qt
set boxwidth 3
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb"#daf7a6" behind
set yrange [-0.01:0.11]
set ytics -0.01,0.01,0.11
plot 'mkl_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set terminal png size 1920,1080
set output "mkl_plot.png"
replot
set term postscript eps color blacktext "Helvetica" 24
set output "mkl_plot.eps"
plot 'mkl_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set output
set terminal qt
set boxwidth 3
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb"#daf7a6" behind
set yrange [-0.01:0.12]
set ytics -0.01,0.01,0.12
plot 'openblas_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set terminal png size 1920,1080
set output "openblas_plot.png"
replot
set term postscript eps color blacktext "Helvetica" 24
set output "openblas_plot.eps"
plot 'openblas_data.txt' using 1:3:2:6:5 with candlesticks lt -1 lw 2 whiskerbars,\
'' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle
set output
set terminal qt
quit