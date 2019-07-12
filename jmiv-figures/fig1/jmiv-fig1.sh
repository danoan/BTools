#!/usr/bin/env bash

FIG1_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BTOOLS_BIN=$(realpath $1)

FIG1_APP=${BTOOLS_BIN}/jmiv-fig1

OUTPUT_FOLDER=${FIG1_ROOT}/output
$FIG1_APP $OUTPUT_FOLDER