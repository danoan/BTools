#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATA_FOLDER=${SCRIPT_FOLDER}/data
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p ${DATA_FOLDER}
mkdir -p ${OUTPUT_FOLDER}

cd ${SCRIPT_FOLDER}
cd ..
JMIV_FIG_FOLDER=$PWD
cd ${SCRIPT_FOLDER}
PLOT_SCRIPT_FOLDER=${JMIV_FIG_FOLDER}/plot-scripts

BTOOLS_BIN=$(realpath $1)

produce_data()
{
    SHAPE_FLOW_APP=${BTOOLS_BIN}/shape-flow

    $SHAPE_FLOW_APP -r3 -i150 -p double -l3 -n4 -q1 -t0 -g0 -mimprove -Striangle -h0.5 ${DATA_FOLDER}/triangle-r3
    $SHAPE_FLOW_APP -r3 -i150 -p double -l3 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r3
    $SHAPE_FLOW_APP -r3 -i150 -p double -l3 -n4 -q1 -t0 -g0 -mimprove -Sflower -h0.5 ${DATA_FOLDER}/flower-r3

    $SHAPE_FLOW_APP -r5 -i150 -p double -l5 -n4 -q1 -t0 -g0 -mimprove -Striangle -h0.5 ${DATA_FOLDER}/triangle-r5
    $SHAPE_FLOW_APP -r5 -i150 -p double -l5 -n4 -q1 -t0 -g0 -mimprove -Ssquare -h0.5 ${DATA_FOLDER}/square-r5
    $SHAPE_FLOW_APP -r5 -i150 -p double -l5 -n4 -q1 -t0 -g0 -mimprove -Sflower -h0.5 ${DATA_FOLDER}/flower-r5
}

produce_figures()
{
    SUMMARY_FLOW_APP=${BTOOLS_BIN}/summary-flow

    $SUMMARY_FLOW_APP ${DATA_FOLDER}/triangle-r3 ${OUTPUT_FOLDER}/summary-triangle-r3.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r3 ${OUTPUT_FOLDER}/summary-square-r3.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/flower-r3 ${OUTPUT_FOLDER}/summary-flower-r3.eps 10

    $SUMMARY_FLOW_APP ${DATA_FOLDER}/triangle-r5 ${OUTPUT_FOLDER}/summary-triangle-r5.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/square-r5 ${OUTPUT_FOLDER}/summary-square-r5.eps 10
    $SUMMARY_FLOW_APP ${DATA_FOLDER}/flower-r5 ${OUTPUT_FOLDER}/summary-flower-r5.eps 10
}

produce_plots()
{
    OUTPUT_PLOT=${OUTPUT_FOLDER}/square-flower-triangle.eps

    create_multiplot ${OUTPUT_PLOT} "" ${DATA_FOLDER}/triangle-r5/triangle.txt "Triangle" \
    ${DATA_FOLDER}/square-r5/square.txt "Square" \
    ${DATA_FOLDER}/flower-r5/flower.txt "Flower"
}

source ${PLOT_SCRIPT_FOLDER}/graph-plot.sh

gp_plot_config()
{
    #set yrange [-0.1:1.1];
    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Elastica ({/Symbol a}=0, {/Symbol b}=1)';"
}

gp_add_plot()
{
    printf "'$1' u 1:3 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:3 w l title '$2';"
}

#produce_data
#produce_figures
produce_plots