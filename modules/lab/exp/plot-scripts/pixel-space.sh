#!/usr/bin/env bash

GRAPH_PLOT_APP=$(realpath plot-scripts/graph-plot.sh)

function create_plot_opt_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/pixel" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_OPT=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_opt/${SHAPE}.txt
    DATA_NO_OPT=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/opt.eps" With_opt_x_No_Opt $MODE \
    $DATA_OPT "Opt" \
    $DATA_NO_OPT "No_Opt"
}

function create_plot_levels_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/pixel" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_LEVEL3=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-3_/${SHAPE}.txt
    DATA_LEVEL2=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/levels.eps" "Level_-3_x_Level_-2" $MODE \
    $DATA_LEVEL3 "Level_-3" \
    $DATA_LEVEL2 "Level_-2"
}

function create_plot_radius_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/pixel" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_RADIUS3=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt
    DATA_RADIUS5=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_5/level-2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/radius.eps" "Radius_3_x_Radius_5" $MODE \
    $DATA_RADIUS3 "Radius_3" \
    $DATA_RADIUS5 "Radius_5"
}

function create_plot_profile_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/pixel" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_SINGLE=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/single/radius_3/level-2_/${SHAPE}.txt
    DATA_SINGLEOPT=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/single-opt/radius_3/level-2_/${SHAPE}.txt
    DATA_DOUBLE=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt
    DATA_DOUBLEOPT=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double-opt/radius_3/level-2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/profile.eps" "Profiles" $MODE \
    $DATA_SINGLE "Single" \
    $DATA_SINGLEOPT "Single_Opt" \
    $DATA_DOUBLE "Double" \
    $DATA_DOUBLEOPT "Double_Opt"
}

function create_plot_method_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/pixel" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_PROBE=$DATA_FOLDER/$SHAPE/probe/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt
    DATA_IMPROVE=$DATA_FOLDER/$SHAPE/improve/pixel-space/pixel/double/radius_3/level-2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/method.eps" "Methods" $MODE \
    $DATA_PROBE "Probe" \
    $DATA_IMPROVE "Improve"
}


function create_all_plots_pixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    create_plot_levels_pixel $@
    create_plot_method_pixel $@
    create_plot_opt_pixel $@
    create_plot_profile_pixel $@
    create_plot_radius_pixel $@
}