reset session

array val_degree[23]
      val_degree[ 1] =  1
      val_degree[ 2] =  2
      val_degree[ 3] =  3
      val_degree[ 4] =  4
      val_degree[ 5] =  5
      val_degree[ 6] =  9
      val_degree[ 7] = 19
      val_degree[ 8] = 20
      val_degree[ 9] = 29
      val_degree[10] = 30
      val_degree[11] = 39
      val_degree[12] = 40
      val_degree[13] = 49
      val_degree[14] = 50
      val_degree[15] = 59
      val_degree[16] = 60
      val_degree[17] = 69
      val_degree[18] = 70
      val_degree[19] = 79
      val_degree[20] = 80
      val_degree[21] = 89
      val_degree[22] = 90
      val_degree[23] = 99

set xlabel 'x'

set key outside
set key title 'degree'

set palette model RGB rgbformulae 35,13,10 #rainbow (blue-green-yellow-red)
unset colorbox

set terminal svg

call 'example_plot.plt' '024'
call 'example_plot.plt' '053'
call 'example_plot.plt' '113'

set output
