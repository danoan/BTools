#!/bin/bash

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
source ${PROJECT_FOLDER}/exp/utils/utils.sh


FLOW_APP=${PROJECT_FOLDER}/cmake-build-release/Applications/flow/flow

#MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

INPUT_MAX_IT=$1
INPUT_OPTMETHOD=$2
INPUT_PREFIX_FOLDER=$3
INPUT_APP_MODE=$4
INPUT_OPT_IN_APP=$5
INPUT_LENGTH_WEIGHT=$6


if [ "${INPUT_APP_MODE}" = "opt" ]
then
    SINGLE_FLOW="single-opt"
    DOUBLE_FLOW="double-opt"
elif [ "${INPUT_APP_MODE}" = "around-inner" ]
then
    SINGLE_FLOW="single-around-inner"
    DOUBLE_FLOW="double-around-inner"
elif [ "${INPUT_APP_MODE}" = "inner" ]
then
    SINGLE_FLOW="single-inner"
    DOUBLE_FLOW="double-inner"
else
    echo "Application mode $INPUT_APP_MODE not recognized!"
fi

if [ "${INPUT_OPT_IN_APP}" = "add-opt" ]
then
    INPUT_OPT_IN_APP="-o"
else
    INPUT_OPT_IN_APP=""
fi



##-------------RADIUS----------------
OUTPUT_FOLDER=${PROJECT_FOLDER}/output/flow/${INPUT_PREFIX_FOLDER}/linel/radius/length${INPUT_LENGTH_WEIGHT}/$5

$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${DOUBLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${DOUBLE_FLOW}-r3-l1 $OUTPUT_FOLDER&
$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${SINGLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP}-m ${INPUT_OPTMETHOD} linel-${SINGLE_FLOW}-r3-l1 $OUTPUT_FOLDER&

$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${DOUBLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${DOUBLE_FLOW}-r7-l1 $OUTPUT_FOLDER&
$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${SINGLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${SINGLE_FLOW}-r7-l1 $OUTPUT_FOLDER&


#-------------LEVELS----------------
OUTPUT_FOLDER=${PROJECT_FOLDER}/output/flow/${INPUT_PREFIX_FOLDER}/linel/levels/length${INPUT_LENGTH_WEIGHT}/$5

if [ "${INPUT_APP_MODE}" = "inner" ]
then
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${DOUBLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${DOUBLE_FLOW}-l1 $OUTPUT_FOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${DOUBLE_FLOW} -n 4 -l 2 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${DOUBLE_FLOW}-l2 $OUTPUT_FOLDER&

    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${SINGLE_FLOW} -n 4 -l 1 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${SINGLE_FLOW}-l1 $OUTPUT_FOLDER&
    $FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 2 -c 0 -s 1 -p ${SINGLE_FLOW} -n 4 -l 2 -q 1 -t 0 -g ${INPUT_LENGTH_WEIGHT} ${INPUT_OPT_IN_APP} -m ${INPUT_OPTMETHOD} linel-${SINGLE_FLOW}-l2 $OUTPUT_FOLDER&
fi

wait

#RADIUS PLOTS
OUTPUT_FOLDER=${PROJECT_FOLDER}/output/flow/${INPUT_PREFIX_FOLDER}/linel/radius/length${INPUT_LENGTH_WEIGHT}/$5
create_plots ${OUTPUT_FOLDER} LINELS-RADIUS 0
create_plots ${OUTPUT_FOLDER} LINELS-RADIUS 1
create_plots ${OUTPUT_FOLDER} LINELS-RADIUS 2
summary_flow ${OUTPUT_FOLDER}


#LEVELS PLOTS
if [ "${INPUT_APP_MODE}" = "inner" ]
then
    OUTPUT_FOLDER=${PROJECT_FOLDER}/output/flow/${INPUT_PREFIX_FOLDER}/linel/levels/length${INPUT_LENGTH_WEIGHT}/$5
    create_plots ${OUTPUT_FOLDER} LINELS-LEVELS 0
    create_plots ${OUTPUT_FOLDER} LINELS-LEVELS 1
    create_plots ${OUTPUT_FOLDER} LINELS-LEVELS 2
    summary_flow ${OUTPUT_FOLDER}
fi