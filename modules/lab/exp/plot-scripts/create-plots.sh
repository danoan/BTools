#!/bin/bash

#$1: Flow root folder
#$2: Plot Title
#$3: Data file
#$4: Mode (0: Energy; 1:Energy/Length)
#$5-..: List of flow folder path relative to flow root folder

SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${SCRIPT_FOLDER}/interpixel-space.sh
source ${SCRIPT_FOLDER}/pixel-space.sh

function create_plot_space()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/space" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=$4

    DATA_PIXEL=$DATA_FOLDER/$SHAPE/improve/pixel/double/radius_3/level-2_/${SHAPE}.txt
    DATA_INTERPIXEL=$DATA_FOLDER/$SHAPE/improve/interpixel/double/radius_3/level2_/${SHAPE}.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/space.eps" "Pixel_x_Interpixel" $MODE \
    $DATA_PIXEL "Pixel_Space" \
    $DATA_INTERPIXEL "Interpixel_Space"
}


SHAPE=$1
DATA_FOLDER=$2
OUTPUT_FOLDER=$3
MODE=$4

create_plot_space $1 $2 $3 $4
create_all_plots_pixel $1 $2 $3 $4
create_all_plots_interpixel $1 $2 $3 $4
