#!/usr/bin/env bash

SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
GRAPH_PLOT_APP=${SCRIPT_FOLDER}/graph-plot.sh

function square_e1_length()
{
    SHAPE="triangle"
    DATA_FOLDER=$(realpath $1)
    OUTPUT_FOLDER="$2" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)
    MODE=0

    DATA_triangle=$DATA_FOLDER/triangle/improve/double/neigh_4/radius_5/level_5/no-opt/count-optApp/gs_0.50/length_0.00/triangle.txt
    DATA_square=$DATA_FOLDER/square/improve/double/neigh_4/radius_5/level_5/no-opt/count-optApp/gs_0.50/length_0.00/square.txt
    DATA_flower=$DATA_FOLDER/flower/improve/double/neigh_4/radius_5/level_5/no-opt/count-optApp/gs_0.50/length_0.00/flower.txt

    $GRAPH_PLOT_APP "$OUTPUT_FOLDER/r5h05.eps" "h=0.5 r=5" $MODE \
    $DATA_triangle "Triangle" \
    $DATA_square "Square" \
    $DATA_flower "Flower"
}

function create_all_paper_plots()
{
    square_e1_length $@
}

create_all_paper_plots $@
