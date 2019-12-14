#!/usr/bin/env bash

FIG2_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BTOOLS_BIN=$(realpath $1)

FIG2_APP=${BTOOLS_BIN}/jmiv-fig2

OUTPUT_FOLDER=${FIG2_ROOT}/output
$FIG2_APP $OUTPUT_FOLDER