FLOW_APP=cmake-build-debug/Applications/flow/flow

$FLOW_APP -a 0 -c 0 -s 0 -p single -r 3 -i 10 single0
$FLOW_APP -a 1 -c 0 -s 1 -p single -r 3 -i 10 single1
$FLOW_APP -a 0 -c 1 -s 1 -p single -r 3 -i 10 single2
$FLOW_APP -a 0 -c 0 -s 0 -p double -r 3 -i 10 double0
$FLOW_APP -a 0 -c 1 -s 1 -p double -r 3 -i 10 double1
$FLOW_APP -a 1 -c 0 -s 1 -p double -r 3 -i 10 double2
