#!/usr/bin/env bash


INITIAL_DIR=$PWD
SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"

cd ${SCRIPT_FOLDER}
cd ../../..
BTOOLS_FOLDER=$PWD
cd ${INITIAL_DIR}

source ${BTOOLS_FOLDER}/plot-scripts/graph-plot.sh
source ${BTOOLS_FOLDER}/plot-scripts/input-utils.sh


CFG_RADIUS=9
CFG_GS=0.25
CFG_UP=True
CFG_NLEVELS="6:9"
DATA_FOLDER=$(realpath $1)
OUTPUT_FOLDER=$(realpath $2)

function create_shape_plots()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3

    source ${SCRIPT_FOLDER}/plot-scripts/levels.sh $SHAPE $CFG_RADIUS $CFG_GS $CFG_UP $CFG_NLEVELS $DATA_FOLDER $OUTPUT_FOLDER
}

create_shape_plots triangle $DATA_FOLDER $OUTPUT_FOLDER
create_shape_plots square $DATA_FOLDER $OUTPUT_FOLDER
create_shape_plots flower $DATA_FOLDER $OUTPUT_FOLDER
create_shape_plots ellipse $DATA_FOLDER $OUTPUT_FOLDER

source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh triangle $CFG_RADIUS $CFG_GS $CFG_UP $CFG_NLEVELS  $DATA_FOLDER $OUTPUT_FOLDER
source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh square $CFG_RADIUS $CFG_GS $CFG_UP $CFG_NLEVELS  $DATA_FOLDER $OUTPUT_FOLDER
source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh ellipse $CFG_RADIUS $CFG_GS $CFG_UP $CFG_NLEVELS  $DATA_FOLDER $OUTPUT_FOLDER
source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh flower $CFG_RADIUS $CFG_GS $CFG_UP $CFG_NLEVELS  $DATA_FOLDER $OUTPUT_FOLDER


