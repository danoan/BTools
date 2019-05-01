#!/bin/bash

#$1: Flow root folder
#$2: Plot Title
#$3: Data file
#$4: Mode (0: Energy; 1:Energy/Length)
#$5-..: List of flow folder path relative to flow root folder

source interpixel-space
source pixel-space

DATA_FOLDER=$1
OUTPUT_FOLDER=$2
MODE=$3
LIST_SHAPES=triangle square pentagon heptagon ball ellipse flower

function create_plot_space()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3
    MODE=$4

    DATA_PIXEL=$DATA_FOLDER/$SHAPE/improve/pixel/double/radius_3/level-2_/${Shape}.txt
    DATA_INTERPIXEL=$DATA_FOLDER/$SHAPE/improve/interpixel/double/radius_3/level-2_/${Shape}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/space.eps" "Pixel x Interpixel" $MODE \
    $DATA_PIXEL "Pixel Space" \
    $DATA_INTERPIXEL "Interpixel Space"
}


function create_plots_all_shapes()
{
    for SHAPE in $LIST_SHAPES
    do
        create_plot_space $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
        create_all_plots_pixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
        create_all_plots_interpixel $SHAPE $DATA_FOLDER $OUTPUT_FOLDER $MODE
    done
}
