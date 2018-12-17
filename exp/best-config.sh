#!/bin/sh

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
RADIUS_PLOT_APP=${PROJECT_FOLDER}/exp/utils/radius-plot.sh
MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

create_plots()
{
    FLOW_FOLDER=$1
    SUFFIX=$2

    LIST_FLOW_FOLDER=$3


    $RADIUS_PLOT_APP $FLOW_FOLDER BALL-$SUFFIX Ball.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER FLOWER-$SUFFIX Flower.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER TRIANGLE-$SUFFIX Triangle.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER SQUARE-$SUFFIX Square.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER PENTAGON-$SUFFIX Pentagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER HEPTAGON-$SUFFIX Heptagon.txt $MODE ${LIST_FLOW_FOLDER}
    $RADIUS_PLOT_APP $FLOW_FOLDER ELLIPSE-$SUFFIX Ellipse.txt $MODE ${LIST_FLOW_FOLDER}
}

OUTPUT_SUBFOLDER=best-plot
FLOW_FOLDER="${PROJECT_FOLDER}/output/flow"
LIST_FLOW_FOLDER="pixel/levels/double-ps-l2 pixel/levels/double-ps-l3 \
interpixel-cptl/radius/double-cptl-r7 interpixel-cpxl/levels/double-cpxl-l2 \
interpixel-cpxl/levels/double-cpxl-l3 interpixel-cptl/radius/single-cptl-r7"

create_plots $FLOW_FOLDER "BEST-PLOT" "$LIST_FLOW_FOLDER"