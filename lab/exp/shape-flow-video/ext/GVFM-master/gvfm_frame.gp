# Put your plot command here. Take full advantage 
# of the variable 'frame'. See examples below:

set label 1 "it=".frame at graph 0.1, graph 0.1 left

# A simple plot:
#p sin(0.1*frame*x)/(x-0.04*frame) lw 3 t "Square"

# If you have your data in multiple files like 
# data1.txt, data2.txt etc. then plot like this:

#p "data".frame.".txt" t "simulation data"


# If you have all your data in a single file 
# separated by blank lines then plot like this:

p DATA_FILE u 0:5 every ::0::frame w lp ls 1 title TITLE
