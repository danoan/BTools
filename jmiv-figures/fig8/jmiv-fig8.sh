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

    $SHAPE_FLOW_APP -r5 -i150 -f around-contour -l1 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5-m1
    $SHAPE_FLOW_APP -r5 -i150 -f around-contour -l2 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5-m2
    $SHAPE_FLOW_APP -r5 -i150 -f around-contour -l3 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5-m3
    $SHAPE_FLOW_APP -r5 -i150 -f around-contour -l4 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5-m4
    $SHAPE_FLOW_APP -r5 -i150 -f around-contour -l5 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5-m5
}

produce_figures()
{
    SUMMARY_FLOW_APP=${BTOOLS_BIN}/summary-flow

    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5-m1 ${OUTPUT_FOLDER}/summary-square-r5-m1.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5-m2 ${OUTPUT_FOLDER}/summary-square-r5-m2.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5-m3 ${OUTPUT_FOLDER}/summary-square-r5-m3.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5-m4 ${OUTPUT_FOLDER}/summary-square-r5-m4.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5-m5 ${OUTPUT_FOLDER}/summary-square-r5-m5.eps 10
}

produce_data
produce_figures
