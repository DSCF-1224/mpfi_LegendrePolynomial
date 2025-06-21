set output  ('precision_' . ARG1 . '_left.svg')

set title ('mpfr\_precision: ' . ARG1)
set ylabel 'left'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:3:(i) \
     with lines linecolor palette \
     title str_degree



set output  ('precision_' . ARG1 . '_right.svg')

set title ('mpfr\_precision: ' . ARG1)
set ylabel 'right'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:4:(i) \
     with lines linecolor palette \
     title str_degree



set output  ('precision_' . ARG1 . '_width.svg')

set title ('mpfr\_precision: ' . ARG1)
set ytics 
set yrange [-25:5]
set ylabel 'log10(right-left)'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:( log10($4 - $3) ):(i) \
     with lines linecolor palette \
     title str_degree

unset ytics
unset yrange
