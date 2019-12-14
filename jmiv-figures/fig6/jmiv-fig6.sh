#!/usr/bin/env bash

FIG6_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BTOOLS_BIN=$(realpath $1)

FIG6_APP=${BTOOLS_BIN}/jmiv-fig6

OUTPUT_FOLDER=${FIG6_ROOT}/output
DATA_FOLDER=${FIG6_ROOT}/data/square
$FIG6_APP $DATA_FOLDER/1.png $OUTPUT_FOLDER