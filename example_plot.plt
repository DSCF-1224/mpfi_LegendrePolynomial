set output  ('example/precision_' . ARG1 . '_left.svg')

set title ('mpfr\_precision: ' . ARG1)
set ylabel 'left'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:3:(i) \
     with lines linecolor palette \
     title str_degree



set output  ('example/precision_' . ARG1 . '_right.svg')

set title ('mpfr\_precision: ' . ARG1)
set ylabel 'right'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:4:(i) \
     with lines linecolor palette \
     title str_degree



set output  ('example/precision_' . ARG1 . '_diam.svg')

set title ('mpfr\_precision: ' . ARG1)
set ytics 5
set yrange [-35:5]
set ylabel 'log10(diam)'

plot for [i = 1:(|val_degree|)] \
     str_degree = sprintf("%3.3d", val_degree[i]) , \
     ('precision_' . ARG1 . '_degree_' . str_degree . '.dat') using 2:( log10($5) ):(i) \
     with lines linecolor palette \
     title str_degree

set ytics auto
set yrange [*:*]
