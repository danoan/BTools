FLOW_APP=/home/daniel/Projects/GIT/PhD/BTools/cmake-build-debug/Applications/flow/flow
MAX_IT=10
FOLDER=pixel

$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 0 -s 0 -p single -r 3 -i $MAX_IT single-ps-r3 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 0 -s 0 -p double -r 3 -i $MAX_IT double-ps-r3 $FOLDER&

$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 0 -s 0 -p single -r 7 -i $MAX_IT single-ps-r7 $FOLDER&
$FLOW_APP -q 1 -t 0 -g 0 -a 0 -c 0 -s 0 -p double -r 7 -i $MAX_IT double-ps-r7 $FOLDER&
