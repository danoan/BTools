#!/bin/sh

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
RADIUS_PLOT_APP=${PROJECT_FOLDER}/exp/utils/radius-plot.sh
FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/flow
SUMMARY_FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/make-summary-flow
MAX_IT=50

MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

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

    $RADIUS_PLOT_APP $FLOW_FOLDER BALL-$SUFFIX Ball.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER FLOWER-$SUFFIX Flower.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER TRIANGLE-$SUFFIX Triangle.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER SQUARE-$SUFFIX Square.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER PENTAGON-$SUFFIX Pentagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER HEPTAGON-$SUFFIX Heptagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER ELLIPSE-$SUFFIX Ellipse.txt $MODE ${LIST_FLOW_FOLDER}
}

#-------------RADIUS----------------
OUTPUT_SUBFOLDER=interpixel-cptl/radius

$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-cptl-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 3 -q 1 -t 0 -g 0 double-cptl-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 7 -q 1 -t 0 -g 0 single-cptl-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 7 -q 1 -t 0 -g 0 double-cptl-r7 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} CPTL-RADIUS
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}


#-------------NEIGHBORHOOD----------------
OUTPUT_SUBFOLDER=interpixel-cptl/neighborhood

$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-cptl-n4 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 3 -q 1 -t 0 -g 0  double-cptl-n4 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 8 -l 3 -q 1 -t 0 -g 0  single-cptl-n8 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 8 -l 3 -q 1 -t 0 -g 0  double-cptl-n8 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} CPTL-NEIGH
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}


#-------------LEVELS----------------
OUTPUT_SUBFOLDER=interpixel-cptl/levels

$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 1 -q 1 -t 0 -g 0  single-cptl-l1 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 2 -q 1 -t 0 -g 0  single-cptl-l2 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p single -n 4 -l 3 -q 1 -t 0 -g 0  single-cptl-l3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 1 -q 1 -t 0 -g 0  double-cptl-l1 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 2 -q 1 -t 0 -g 0  double-cptl-l2 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i $MAX_IT -m around -a 0 -c 1 -s 1 -p double -n 4 -l 3 -q 1 -t 0 -g 0  double-cptl-l3 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} CPTL-LEVELS
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}