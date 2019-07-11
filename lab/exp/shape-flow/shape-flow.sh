#!/usr/bin/env bash

SCRIPT_FOLDER=$( cd $(dirname ${BASH_SOURCE[0]} ) > /dev/null 2>&1 && pwd )
BTOOLS_BIN=$(realpath $1)

python3 instance-generator/generator.py ${BTOOLS_BIN}
${SCRIPT_FOLDER}/convert-flowimg-png.sh ${SCRIPT_FOLDER}/output > /dev/null 2>&1
${SCRIPT_FOLDER}/create-plots.sh ${SCRIPT_FOLDER}/output ${SCRIPT_FOLDER}/output/plots
