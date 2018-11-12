#!/bin/sh

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
RADIUS_PLOT_APP=${PROJECT_FOLDER}/exp/radius-plot.sh
FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/flow
SUMMARY_FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/make-summary-flow
MAX_IT=50

list_of_folders()
{
    MAIN_FOLDER=$1

    LIST_FILES=`ls $MAIN_FOLDER`
    LIST_FLOW_FOLDER=""
    for F in $LIST_FILES
    do
     if [ -d "${MAIN_FOLDER}/${F}" ]
     then
        LIST_FLOW_FOLDER="${LIST_FLOW_FOLDER} $F"
     fi
    done

    echo $LIST_FLOW_FOLDER
}

summary_flow()
{
    FLOW_FOLDER=$1
    LIST_FLOW_FOLDER=$(list_of_folders $FLOW_FOLDER)

    for F in $LIST_FLOW_FOLDER
    do
        $SUMMARY_FLOW_APP ${FLOW_FOLDER}/${F} 5
    done

}

create_plots()
{
    FLOW_FOLDER=$1
    SUFFIX=$2

    LIST_FLOW_FOLDER=$(list_of_folders $FLOW_FOLDER)

    $RADIUS_PLOT_APP $FLOW_FOLDER BALL-$SUFFIX Ball.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER FLOWER-$SUFFIX Flower.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER TRIANGLE-$SUFFIX Triangle.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER SQUARE-$SUFFIX Square.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER PENTAGON-$SUFFIX Pentagon.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER HEPTAGON-$SUFFIX Heptagon.txt ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER ELLIPSE-$SUFFIX Ellipse.txt ${LIST_FLOW_FOLDER}
}

#-------------RADIUS----------------
OUTPUT_SUBFOLDER=pixel/radius

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-ps-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 3 -q 1 -t 0 -g 0 double-ps-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 7 -q 1 -t 0 -g 0 single-ps-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 7 -q 1 -t 0 -g 0 double-ps-r7 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}



#-------------NEIGHBORHOOD----------------
OUTPUT_SUBFOLDER=pixel/neighborhood

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-ps-n4 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 3 -q 1 -t 0 -g 0  double-ps-n4 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 8 -l 3 -q 1 -t 0 -g 0  single-ps-n8 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 8 -l 3 -q 1 -t 0 -g 0  double-ps-n8 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-NEIGH
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}


#-------------LEVELS----------------
OUTPUT_SUBFOLDER=pixel/levels

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 1 -q 1 -t 0 -g 0  single-ps-l1 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 2 -q 1 -t 0 -g 0  single-ps-l2 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-ps-l3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 1 -q 1 -t 0 -g 0  double-ps-l1 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 2 -q 1 -t 0 -g 0  double-ps-l2 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 3 -q 1 -t 0 -g 0  double-ps-l3 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}