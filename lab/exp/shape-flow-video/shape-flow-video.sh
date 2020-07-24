#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH="$( cd "$SCRIPT_PATH" && cd ../../.. && pwd)"

BC_APP="${PROJECT_PATH}/install/bin/shape-flow"
DATA_FOLDER="${SCRIPT_PATH}/data"

CACHE_TEMP_PATH="${SCRIPT_PATH}/cache"
mkdir -p $CACHE_TEMP_PATH

SHAPES="square 150 triangle 90 flower 500 bean 500"

flow()
{
    s=$1; shift;
    it=$1; shift;
    while [ -n "$s" ]
    do
       echo "Executing flow for shape ${s^}"
       ${BC_APP} -S"$s" -i$it -r15 -h0.1 -l-3 -q1 -g0.01 -o${DATA_FOLDER}/${s}

       s="$1"; shift;
       it="$1"; shift;
    done
}

animated_gif()
{
    s=$1; shift;
    it=$1; shift;
    while [ -n "$s" ]
    do

       OUTPUT_FOLDER=${SCRIPT_PATH}/output
       ${SCRIPT_PATH}/make-plot-frames.sh ${s} ${OUTPUT_FOLDER} ${CACHE_TEMP_PATH}

       ${SCRIPT_PATH}/join-gifs.sh ${DATA_FOLDER}/${s} ${s} ${OUTPUT_FOLDER}/${s}/flow-plot.gif ${CACHE_TEMP_PATH}

       s="$1"; shift;
       it="$1"; shift;
    done

}

flow $SHAPES
animated_gif $SHAPES
