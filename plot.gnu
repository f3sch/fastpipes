set terminal png size 700,500
set output 'plot.png'

set style data histograms
set style fill solid
set title 'Improvement History'
set ylabel 'Throughput (GiB/sec)'
plot 'mess.data' using 2:xtic(1) title 'Method'
