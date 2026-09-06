reset session

array val_degree[19]
      val_degree[ 1] =  1
      val_degree[ 2] =  2
      val_degree[ 3] =  3
      val_degree[ 4] =  4
      val_degree[ 5] =  5
      val_degree[ 6] =  6
      val_degree[ 7] =  7
      val_degree[ 8] =  8
      val_degree[ 9] =  9
      val_degree[10] = 10
      val_degree[11] = 11
      val_degree[12] = 22
      val_degree[13] = 33
      val_degree[14] = 44
      val_degree[15] = 55
      val_degree[16] = 66
      val_degree[17] = 77
      val_degree[18] = 88
      val_degree[19] = 99

set xlabel 'x'

set key outside
set key title 'degree'

set palette model RGB rgbformulae 35,13,10 #rainbow (blue-green-yellow-red)
unset colorbox

set terminal svg

call 'examples/example_plot.plt' '024'
call 'examples/example_plot.plt' '053'
call 'examples/example_plot.plt' '113'

set output
