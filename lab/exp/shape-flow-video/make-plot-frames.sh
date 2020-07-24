#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../ && pwd)

get_max()
{
    FILE=$1
    m=$( awk '{ print $5 }' $FILE | sort -r -n | head -n2 | tail -n1)
    echo $m
}

SHAPE="$1"
BASE_OUTPUT_PATH="$2"
CACHE_TEMP_PATH="$3"

OUTPUT_PATH="${BASE_OUTPUT_PATH}/${SHAPE}"

GVFM_PATH="${SCRIPT_PATH}/ext/GVFM-master"
DATA_FILE="${SCRIPT_PATH}/data/${SHAPE}/$SHAPE.txt"
FRAME_OUTPUT_PATH="${SCRIPT_PATH}/data/${SHAPE}/plot-frames"

NFRAMES=$( wc $DATA_FILE -l | cut -d" " -f1 )
NFRAMES=$(( NFRAMES-6 ))

MAX_Y=$(get_max $DATA_FILE)
HEIGHT=$(identify ${SCRIPT_PATH}/data/${SHAPE}/0000.pgm | cut -d" " -f3 | cut -d"x" -f2)

echo "Creating plot frames..."
mkdir -p ${FRAME_OUTPUT_PATH}
gnuplot -e "LOAD_PATH=\"${GVFM_PATH}\";DATA_FILE=\"${DATA_FILE}\";TITLE='${SHAPE^}';START_FRAME=0;END_FRAME=${NFRAMES};MAX_Y=${MAX_Y};HEIGHT=${HEIGHT};OUTPUT_PATH=\"${FRAME_OUTPUT_PATH}\"" ${GVFM_PATH}/gvfm.gp


mkdir -p ${OUTPUT_PATH}

#echo "Creating shape gif..."
#convert -delay 10 -layers Optimize -compress LZW  ${SCRIPT_PATH}/data/${SHAPE}/*.pgm ${OUTPUT_PATH}/flow.gif

#echo "Creating plot gif..."
#convert -delay 10 -layers Optimize -compress LZW  ${FRAME_OUTPUT_PATH}/*.png ${OUTPUT_PATH}/plot.gif
