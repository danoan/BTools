#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATA_FOLDER=${SCRIPT_FOLDER}/data
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p ${DATA_FOLDER}
mkdir -p ${OUTPUT_FOLDER}

BTOOLS_BIN=$(realpath $1)

produce_data()
{
    SHAPE_FLOW_APP=${BTOOLS_BIN}/shape-flow

    $SHAPE_FLOW_APP -r3 -i150 -p double -l1 -n4 -q1 -t0 -g0 -mimprove -Striangle -h0.5 ${DATA_FOLDER}/triangle-r3-a0
    $SHAPE_FLOW_APP -r3 -i150 -p double -l1 -n4 -q1 -t0 -g0.15 -mimprove -Striangle -h0.5 ${DATA_FOLDER}/triangle-r3-a015
    $SHAPE_FLOW_APP -r5 -i150 -p double -l1 -n4 -q1 -t0 -g0.15 -mimprove -Striangle -h0.5 ${DATA_FOLDER}/triangle-r5-a015
}

produce_figures()
{
    SUMMARY_FLOW_APP=${BTOOLS_BIN}/summary-flow

    $SUMMARY_FLOW_APP ${DATA_FOLDER}/triangle-r3-a0 ${OUTPUT_FOLDER}/summary-triangle-r3-a0.eps 14
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/triangle-r3-a015 ${OUTPUT_FOLDER}/summary-triangle-r3-a015.eps 25
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/triangle-r5-a015 ${OUTPUT_FOLDER}/summary-triangle-r5-a015.eps 10
}

produce_data
produce_figures