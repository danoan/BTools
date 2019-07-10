#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATA_FOLDER=${SCRIPT_FOLDER}/data
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p $DATA_FOLDER
mkdir -p $OUTPUT_FOLDER

cd ${SCRIPT_FOLDER}
cd ..
JMIV_FIG_FOLDER=$PWD
cd ${SCRIPT_FOLDER}
PLOT_SCRIPT_FOLDER=${JMIV_FIG_FOLDER}/plot-scripts


BTOOLS_BIN=$(realpath $1)
EXT_BIN=$(realpath $2)



produce_data()
{
    LOCAL_COMB_APP=${EXT_BIN}/exhaustive-gc-app-flow

    echo "Producing data for square h=1.0"
    $LOCAL_COMB_APP -m2 -M20 -j1 -i300 -eelastica -a0.005 -Ssquare -sbest -h1.0 -tmdca -n4 -k2000 ${DATA_FOLDER}/squareh1

    echo "Producing data for square h=0.5"
    $LOCAL_COMB_APP -m2 -M20 -j1 -i300 -eelastica -a0.005 -Ssquare -sbest -h0.5 -tmdca -n4 -k4000 ${DATA_FOLDER}/squareh05

    echo "Producing data for flower h=1.0"
    $LOCAL_COMB_APP -m2 -M20 -j1 -i300 -eelastica -a0.01 -Sflower -sbest -h1.0 -tmdca -n4 -k10000 ${DATA_FOLDER}/flowerh1

    echo "Producing data for flower h=0.5"
    $LOCAL_COMB_APP -m2 -M20 -j1 -i300 -eelastica -a0.01 -Sflower -sbest -h0.5 -tmdca -n4 -k16000 ${DATA_FOLDER}/flowerh05

}

produce_figures()
{
    SUMMARY_APP=${BTOOLS_BIN}/summary-flow

    echo "Summary flow for square h=1.0"
    $SUMMARY_APP ${DATA_FOLDER}/squareh1 ${OUTPUT_FOLDER}/summary-squareh1.eps 2

    echo "Summary flow for square h=0.5"
    $SUMMARY_APP ${DATA_FOLDER}/squareh05 ${OUTPUT_FOLDER}/summary-squareh05.eps 2

    echo "Summary flow for flower h=1.0"
    $SUMMARY_APP ${DATA_FOLDER}/flowerh1 ${OUTPUT_FOLDER}/summary-flowerh1.eps 7

    echo "Summary flow for flower h=0.5"
    $SUMMARY_APP ${DATA_FOLDER}/flowerh05 ${OUTPUT_FOLDER}/summary-flowerh05.eps 7

}

produce_plots()
{
    OUTPUT_PLOT=${OUTPUT_FOLDER}/square-flower.eps

    create_multiplot ${OUTPUT_PLOT} "" ${DATA_FOLDER}/squareh1/energy.txt "square(h=1)" \
    ${DATA_FOLDER}/squareh05/energy.txt "square(h=0.5)" \
    ${DATA_FOLDER}/flowerh1/energy.txt "flower(h=1)" \
    ${DATA_FOLDER}/flowerh05/energy.txt "flower(h=0.5)"
}

gp_plot_config()
{
    #set yrange [-0.1:1.1];
    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Elastica ({/Symbol a}=0.1, {/Symbol b}=1)';"
}

source ${PLOT_SCRIPT_FOLDER}/graph-plot.sh

produce_data
produce_figures
produce_plots
