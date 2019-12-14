#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATA_FOLDER=${SCRIPT_FOLDER}/data
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p ${DATA_FOLDER}
mkdir -p ${OUTPUT_FOLDER}

BTOOLS_BIN=$(realpath $1)

FIG7_APP=${BTOOLS_BIN}/jmiv-fig7
FLOW_APP=${BTOOLS_BIN}/shape-flow
SUMMARY_APP=${BTOOLS_BIN}/summary-flow


$FIG7_APP 20 80 15 ${DATA_FOLDER}/square-holes.pgm
$FLOW_APP -i100 -r6 -p double -q1.0 -t0 -g0 -l-1 -S${DATA_FOLDER}/square-holes.pgm ${DATA_FOLDER}/square-holes-flow
$SUMMARY_APP ${DATA_FOLDER}/square-holes-flow ${OUTPUT_FOLDER}/summary-square-holes.eps 10

$FLOW_APP -i100 -r9 -p double -q1.0 -t0 -g0 -l-1 -h0.1 -Swave ${DATA_FOLDER}/wave-flow
$SUMMARY_APP ${DATA_FOLDER}/wave-flow ${OUTPUT_FOLDER}/summary-wave.eps 14
