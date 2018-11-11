FLOW_APP=/home/daniel/Projects/GIT/PhD/BTools/cmake-build-debug/Applications/flow/flow
MAX_IT=10
FOLDER=interpixel

$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 1 -s 1 -p single -r 3 -i $MAX_IT single-ps-cptl-r3 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 1 -s 1 -p double -r 3 -i $MAX_IT double-ps-cptl-r3 $FOLDER&

$FLOW_APP -q 1 -t 0 -g 0 -a 1 -c 0 -s 1 -p single -r 3 -i $MAX_IT single-ps-cpxl-r3 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 1 -c 0 -s 1 -p double -r 3 -i $MAX_IT double-ps-cpxl-r3 $FOLDER&

$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 1 -s 1 -p single -r 7 -i $MAX_IT single-ps-cptl-r7 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 1 -s 1 -p double -r 7 -i $MAX_IT double-ps-cptl-r7 $FOLDER&

$FLOW_APP -q 1 -t 0 -g 0 -a 1 -c 0 -s 1 -p single -r 7 -i $MAX_IT single-ps-cpxl-r7 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 1 -c 0 -s 1 -p double -r 7 -i $MAX_IT double-ps-cpxl-r7 $FOLDER&
