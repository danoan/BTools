#!/bin/sh

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
RADIUS_PLOT_APP=${PROJECT_FOLDER}/exp/utils/radius-plot.sh
FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/flow
SUMMARY_FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/make-summary-flow
MAX_IT=50

#MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

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
    MODE=$3

    LIST_FLOW_FOLDER=$(list_of_folders $FLOW_FOLDER)

    $RADIUS_PLOT_APP $FLOW_FOLDER BALL-$SUFFIX Ball.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER FLOWER-$SUFFIX Flower.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER TRIANGLE-$SUFFIX Triangle.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER SQUARE-$SUFFIX Square.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER PENTAGON-$SUFFIX Pentagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER HEPTAGON-$SUFFIX Heptagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER ELLIPSE-$SUFFIX Ellipse.txt $MODE ${LIST_FLOW_FOLDER}
}

#-------------RADIUS----------------
OUTPUT_SUBFOLDER=pixel/radius

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-ps-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 3 -q 1 -t 0 -g 0 double-ps-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 7 -q 1 -t 0 -g 0 single-ps-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 7 -q 1 -t 0 -g 0 double-ps-r7 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 0
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 1
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 2
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}



#-------------NEIGHBORHOOD----------------
OUTPUT_SUBFOLDER=pixel/neighborhood

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-ps-n4 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 4 -l 3 -q 1 -t 0 -g 0  double-ps-n4 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p single -n 8 -l 3 -q 1 -t 0 -g 0  single-ps-n8 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -a 0 -c 0 -s 0 -p double -n 8 -l 3 -q 1 -t 0 -g 0  double-ps-n8 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-NEIGH 0
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-NEIGH 1
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-NEIGH 2
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
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 0
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 1
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 2
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}