#!/bin/bash

PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
source ${PROJECT_FOLDER}/exp/utils/utils.sh


FLOW_APP=${PROJECT_FOLDER}/cmake-build-debug/Applications/flow/flow

#MODE=1  #0 MDCA; 1 MDCA/Perimeter; 2 Unlabeled

INPUT_MAX_IT=$1
INPUT_OPTMETHOD=$2
INPUT_PREFIX_FOLDER=$3
INPUT_OPT=$4


#-------------RADIUS----------------
OUTPUT_SUBFOLDER=${INPUT_PREFIX_FOLDER}/real/

$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p single${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD}  single${INPUT_OPT}-ps-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p double${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-ps-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p single${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} single${INPUT_OPT}-ps-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 0 -s 0 -p double${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0 -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-ps-r7 $OUTPUT_SUBFOLDER&


$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 1 -s 1 -p single${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} single${INPUT_OPT}-cptl-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 0 -c 1 -s 1 -p double${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-cptl-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 1 -s 1 -p single${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} single${INPUT_OPT}-cptl-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 0 -c 1 -s 1 -p double${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-cptl-r7 $OUTPUT_SUBFOLDER&


$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 1 -c 0 -s 1 -p single${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} single${INPUT_OPT}-cpxl-r3 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 3 -i ${INPUT_MAX_IT} -a 1 -c 0 -s 1 -p double${INPUT_OPT} -n 4 -l 3 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-cpxl-r3 $OUTPUT_SUBFOLDER&

$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 1 -c 0 -s 1 -p single${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} single${INPUT_OPT}-cpxl-r7 $OUTPUT_SUBFOLDER&
$FLOW_APP -r 7 -i ${INPUT_MAX_IT} -a 1 -c 0 -s 1 -p double${INPUT_OPT} -n 4 -l 7 -q 1 -t 0 -g 0  -m ${INPUT_OPTMETHOD} double${INPUT_OPT}-cpxl-r7 $OUTPUT_SUBFOLDER&

wait
create_plots ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER} DIG-REAL-AREA 0
summary_flow ${PROJECT_FOLDER}/output/flow/${OUTPUT_SUBFOLDER}
