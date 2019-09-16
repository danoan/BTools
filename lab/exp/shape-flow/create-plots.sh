#!/usr/bin/env bash

function create_plot_levels()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

    echo $DATA_FOLDER

    DATA_LEVEL_1=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_1/gs_0.50/${SHAPE}.txt
    DATA_LEVEL_2=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_2/gs_0.50/${SHAPE}.txt
    DATA_LEVEL_3=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_3/gs_0.50/${SHAPE}.txt
    DATA_LEVEL_4=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_4/gs_0.50/${SHAPE}.txt
    DATA_LEVEL_5=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

    create_multiplot "$OUTPUT_FOLDER/levels.eps" "Levels"  \
    $DATA_LEVEL_1 "Level_1" \
    $DATA_LEVEL_2 "Level_2" \
    $DATA_LEVEL_3 "Level_3" \
    $DATA_LEVEL_4 "Level_4" \
    $DATA_LEVEL_5 "Level_5"
}

function create_plot_radius()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

    DATA_RADIUS3=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_3/level_3/gs_0.50/${SHAPE}.txt
    DATA_RADIUS5=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

    create_multiplot "$OUTPUT_FOLDER/radius.eps" "Radius_3_x_Radius_5" \
    $DATA_RADIUS3 "Radius_3" \
    $DATA_RADIUS5 "Radius_5"
}

function create_plot_method()
{
    SHAPE=$1
    DATA_FOLDER=$(realpath $2)
    OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
    OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

    DATA_PROBE=$DATA_FOLDER/sp_$SHAPE/mt_probe/radius_5/level_5/gs_0.50/${SHAPE}.txt
    DATA_IMPROVE=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

    create_multiplot "$OUTPUT_FOLDER/method.eps" "Methods" \
    $DATA_PROBE "Probe" \
    $DATA_IMPROVE "Improve"
}


function create_all_plots()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3

    create_plot_levels $@
    create_plot_method $@
    create_plot_radius $@
}



#$1: Shape
#$2: Data Folder
#$3: Output Folder

INITIAL_DIR=$PWD
SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"

cd ${SCRIPT_FOLDER}
cd ../../..
BTOOLS_FOLDER=$PWD
cd ${INITIAL_DIR}

source ${BTOOLS_FOLDER}/plot-scripts/graph-plot.sh

gp_plot_config()
{
    mode=$1;shift;

    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Integral Square Curvature (MDCA+MDSS)';"
}

gp_add_plot()
{
    printf "'$1' u 1:3 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:3 w l title '$2';"
}

DATA_FOLDER=$1
OUTPUT_FOLDER=$2

create_all_plots triangle $1 $2
create_all_plots square $1 $2
create_all_plots flower $1 $2
create_all_plots ellipse $1 $2


