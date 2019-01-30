#!/bin/bash

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
source ${PROJECT_FOLDER}/exp/utils/utils.sh


FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/flow

#MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

INPUT_MAX_IT=$1
INPUT_OPTMETHOD=$2
INPUT_PREFIX_FOLDER=$3
INPUT_APP_MODE=$4

if [ "${INPUT_APP_MODE}" = "opt" ]
then
    SINGLE_FLOW="single-opt"
    DOUBLE_FLOW="double-opt"
elif [ "${INPUT_APP_MODE}" = "around" ]
then
    SINGLE_FLOW="single"
    DOUBLE_FLOW="double"
elif [ "${INPUT_APP_MODE}" = "inner" ]
then
    SINGLE_FLOW="single-inner"
    DOUBLE_FLOW="double-inner"
fi


#-------------RADIUS----------------
OUTPUT_SUBFOLDER=${INPUT_PREFIX_FOLDER}/pixel/radius

$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${SINGLE_FLOW} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${SINGLE_FLOW}-ps-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${DOUBLE_FLOW} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} ${DOUBLE_FLOW}-ps-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${SINGLE_FLOW} -n 4 -l 7 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} ${SINGLE_FLOW}-ps-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${DOUBLE_FLOW} -n 4 -l 7 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} ${DOUBLE_FLOW}-ps-r7 $OUTPUT_SUBFOLDER&


#-------------LEVELS----------------
OUTPUT_SUBFOLDER=${INPUT_PREFIX_FOLDER}/pixel/levels

if [ "${INPUT_APP_MODE}" = "around" ]
then
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${SINGLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${SINGLE_FLOW}-ps-l1 $OUTPUT_SUBFOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${SINGLE_FLOW} -n 4 -l 2 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${SINGLE_FLOW}-ps-l2 $OUTPUT_SUBFOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${SINGLE_FLOW} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${SINGLE_FLOW}-ps-l3 $OUTPUT_SUBFOLDER&

    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${DOUBLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${DOUBLE_FLOW}-ps-l1 $OUTPUT_SUBFOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${DOUBLE_FLOW} -n 4 -l 2 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${DOUBLE_FLOW}-ps-l2 $OUTPUT_SUBFOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p ${DOUBLE_FLOW} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  ${DOUBLE_FLOW}-ps-l3 $OUTPUT_SUBFOLDER&
fi

wait

##RADIUS PLOTS
OUTPUT_SUBFOLDER=${INPUT_PREFIX_FOLDER}/pixel/radius
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 0
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 1
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-RADIUS 2
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}


#LEVELS PLOTS
if [ "${INPUT_APP_MODE}" = "around" ]
then
    OUTPUT_SUBFOLDER=${INPUT_PREFIX_FOLDER}/pixel/levels
    create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 0
    create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 1
    create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} PS-LEVELS 2
    summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}
fi