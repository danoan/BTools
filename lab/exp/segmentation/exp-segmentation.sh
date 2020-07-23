#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
GENERATOR_FOLDER="${SCRIPT_FOLDER}/instance-generator"

BTOOLS_BIN="$(realpath "$1")"

tar -xvf "${SCRIPT_FOLDER}/data/coala.tar.bz2" -C "${SCRIPT_FOLDER}/data"

python3 "${GENERATOR_FOLDER}/generator.py" "${BTOOLS_BIN}"
