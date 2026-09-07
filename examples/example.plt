reset session

array val_degree[18]
      val_degree[ 1] =  2
      val_degree[ 2] =  3
      val_degree[ 3] =  4
      val_degree[ 4] =  5
      val_degree[ 5] =  6
      val_degree[ 6] =  7
      val_degree[ 7] =  8
      val_degree[ 8] =  9
      val_degree[ 9] = 10
      val_degree[10] = 11
      val_degree[11] = 22
      val_degree[12] = 33
      val_degree[13] = 44
      val_degree[14] = 55
      val_degree[15] = 66
      val_degree[16] = 77
      val_degree[17] = 88
      val_degree[18] = 99

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
