#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATA_FOLDER=${SCRIPT_FOLDER}/data
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p $DATA_FOLDER
mkdir -p $OUTPUT_FOLDER

cd ${SCRIPT_FOLDER}
cd ../..
BTOOLS_FOLDER=$PWD
cd ${SCRIPT_FOLDER}
PLOT_SCRIPT_FOLDER=${BTOOLS_FOLDER}/plot-scripts


BTOOLS_BIN=$(realpath $1)
EXT_BIN=$(realpath $2)



produce_data()
{
    LOCAL_COMB_APP=${EXT_BIN}/exhaustive-gc-app-flow

    echo "Producing data for square h=1.0"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Ssquare -sbest -h1.0 -tii -r5 -n32 ${DATA_FOLDER}/squareh1

    echo "Producing data for square h=0.5"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Ssquare -sbest -h0.5 -tii -r5 -n32 ${DATA_FOLDER}/squareh05

    echo "Producing data for square h=0.25"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Ssquare -sbest -h0.25 -tii -r5 -n32 ${DATA_FOLDER}/squareh025

    echo "Producing data for flower h=1.0"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Sflower -sbest -h1.0 -tii -r5 -n32 ${DATA_FOLDER}/flowerh1

    echo "Producing data for flower h=0.5"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Sflower -sbest -h0.5 -tii -r5 -n32 ${DATA_FOLDER}/flowerh05

    echo "Producing data for flower h=0.25"
    $LOCAL_COMB_APP -m2 -M50 -j1 -i300 -eelastica -a0.01 -Sflower -sbest -h0.25 -tii -r5 -n32 ${DATA_FOLDER}/flowerh025

}

produce_figures()
{
    SUMMARY_APP=${BTOOLS_BIN}/summary-flow

    echo "Summary flow for square h=1.0"
    $SUMMARY_APP ${DATA_FOLDER}/squareh1 ${OUTPUT_FOLDER}/summary-squareh1.eps -j5

    echo "Summary flow for square h=0.5"
    $SUMMARY_APP ${DATA_FOLDER}/squareh05 ${OUTPUT_FOLDER}/summary-squareh05.eps -j5

    echo "Summary flow for square h=0.25"
    $SUMMARY_APP ${DATA_FOLDER}/squareh025 ${OUTPUT_FOLDER}/summary-squareh025.eps -j5

    echo "Summary flow for flower h=1.0"
    $SUMMARY_APP ${DATA_FOLDER}/flowerh1 ${OUTPUT_FOLDER}/summary-flowerh1.eps -j5

    echo "Summary flow for flower h=0.5"
    $SUMMARY_APP ${DATA_FOLDER}/flowerh05 ${OUTPUT_FOLDER}/summary-flowerh05.eps -j5

echo "Summary flow for flower h=0.25"
    $SUMMARY_APP ${DATA_FOLDER}/flowerh05 ${OUTPUT_FOLDER}/summary-flowerh025.eps -j5

}

produce_plots()
{
    OUTPUT_PLOT=${OUTPUT_FOLDER}/square.eps

    create_multiplot ${OUTPUT_PLOT} "" ${DATA_FOLDER}/squareh1/energy.txt "square(h=1)" \
    ${DATA_FOLDER}/squareh05/energy.txt "square(h=0.5)" \
    ${DATA_FOLDER}/squareh05/energy.txt "square(h=0.25)"

    OUTPUT_PLOT=${OUTPUT_FOLDER}/flower.eps

    create_multiplot ${OUTPUT_PLOT} "" ${DATA_FOLDER}/squareh1/energy.txt ${DATA_FOLDER}/flowerh1/energy.txt "flower(h=1)" \
    ${DATA_FOLDER}/flowerh05/energy.txt "flower(h=0.5)" \
    ${DATA_FOLDER}/flowerh05/energy.txt "flower(h=0.25)"
}

gp_plot_config()
{
    #set yrange [-0.1:1.1];
    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Elastica ({/Symbol a}=0.01, {/Symbol b}=1)';"
}

source ${PLOT_SCRIPT_FOLDER}/graph-plot.sh

produce_data
produce_figures
produce_plots
