#!/usr/bin/env bash


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

function create_shape_plots()
{
    SHAPE=$1
    DATA_FOLDER=$2
    OUTPUT_FOLDER=$3


    source ${SCRIPT_FOLDER}/plot-scripts/levels.sh $@
    source ${SCRIPT_FOLDER}/plot-scripts/method.sh $@
    source ${SCRIPT_FOLDER}/plot-scripts/radius.sh $@
}



DATA_FOLDER=$1
OUTPUT_FOLDER=$2

create_shape_plots triangle $1 $2
create_shape_plots square $1 $2
create_shape_plots flower $1 $2
create_shape_plots ellipse $1 $2

source ${SCRIPT_FOLDER}/plot-scripts/perimeter.sh $DATA_FOLDER $OUTPUT_FOLDER triangle square flower ellipse
source ${SCRIPT_FOLDER}/plot-scripts/squared-perimeter-area-ratio.sh $DATA_FOLDER $OUTPUT_FOLDER triangle square flower ellipse


