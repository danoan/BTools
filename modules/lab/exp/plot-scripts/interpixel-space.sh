#!/usr/bin/env bash

function create_plot_opt_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_OPT=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-2_opt/${Shape}.txt
    DATA_NO_OPT=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_2/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/interpixel/opt.eps" "With opt x No Opt" $MODE \
    $DATA_OPT "Opt" \
    $DATA_NO_OPT "No Opt"
}

function create_plot_levels_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_LEVEL3=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-3_/${Shape}.txt
    DATA_LEVEL2=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/interpixel/levels.eps" "Level -3 x Level -2" $MODE \
    $DATA_LEVEL3 "Level -3" \
    $DATA_LEVEL2 "Level -2"
}

function create_plot_radius_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_RADIUS3=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-2_/${Shape}.txt
    DATA_RADIUS5=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_5/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/interpixel/radius.eps" "Radius 3 x Radius 5" $MODE \
    $DATA_RADIUS3 "Radius 3" \
    $DATA_RADIUS5 "Radius 5"
}

function create_plot_profile_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_SINGLE_INNER=$DATA_FOLDER/$SHAPE/improve/interpixel/single-inner/radius_3/level-2_/${Shape}.txt
    DATA_SINGLEOPT=$DATA_FOLDER/$SHAPE/improve/interpixel/single-opt/radius_3/level-2_/${Shape}.txt
    DATA_DOUBLE_INNER=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-2_/${Shape}.txt
    DATA_DOUBLEOPT=$DATA_FOLDER/$SHAPE/improve/interpixel/double-opt/radius_3/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/interpixel/profile.eps" "Profiles" $MODE \
    $DATA_SINGLE "Single" \
    $DATA_SINGLEOPT "Single Opt" \
    $DATA_DOUBLE "Double" \
    $DATA_DOUBLEOPT "Double Opt"
}

function create_plot_method_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_PROBE=$DATA_FOLDER/$SHAPE/probe/interpixel/double-inner/radius_3/level-2_/${Shape}.txt
    DATA_IMPROVE=$DATA_FOLDER/$SHAPE/improve/interpixel/double-inner/radius_3/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/interpixel/method.eps" "Methods" $MODE \
    $DATA_PROBE "Probe" \
    $DATA_IMPROVE "Improve"
}

function create_all_plots_interpixel()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    create_plot_levels_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
    create_plot_method_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
    create_plot_opt_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
    create_plot_profile_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
    create_plot_radius_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
}