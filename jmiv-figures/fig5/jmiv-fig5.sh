#!/usr/bin/env bash

FIG5_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BTOOLS_BIN=$(realpath $1)

FIG5_APP=${BTOOLS_BIN}/jmiv-fig5

OUTPUT_FOLDER=${FIG5_ROOT}/output
DATA_FOLDER=${FIG5_ROOT}/data/square
$FIG5_APP $DATA_FOLDER/1.png $OUTPUT_FOLDER