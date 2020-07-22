#!/usr/bin/env bash


INITIAL_DIR=$PWD
SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"

cd ${SCRIPT_FOLDER}
cd ../../..
BTOOLS_FOLDER=$PWD
cd ${INITIAL_DIR}

source ${BTOOLS_FOLDER}/plot-scripts/graph-plot.sh
source ${BTOOLS_FOLDER}/plot-scripts/input-utils.sh

SHAPES="triangle square ellipse flower ball wave bean"
CFG_RADIUS=7
CFG_GS=0.25
CFG_NLEVELS="1:7"
CFG_IT=10
DATA_FOLDER=$(realpath $1)
OUTPUT_FOLDER=$(realpath $2)

function create_shape_plots()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3

    source ${SCRIPT_FOLDER}/plot-scripts/levels.sh $SHAPE $CFG_RADIUS $CFG_GS $CFG_NLEVELS $CFG_IT $DATA_FOLDER $OUTPUT_FOLDER
}

for SHAPE in $SHAPES
do
    create_shape_plots $SHAPE $DATA_FOLDER $OUTPUT_FOLDER
    source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh $SHAPE $CFG_RADIUS $CFG_GS $CFG_NLEVELS $CFG_IT  $DATA_FOLDER $OUTPUT_FOLDER
done


