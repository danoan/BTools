#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$(dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"
BTOOLS_BIN="$(realpath "$1")"
OUTPUT_FOLDER="$(realpath "$2")"

python3 "${SCRIPT_FOLDER}/instance-generator/generator.py" "${BTOOLS_BIN}" "${OUTPUT_FOLDER}"
"${SCRIPT_FOLDER}/convert-flowimg-png.sh" "${SCRIPT_FOLDER}/${OUTPUT_FOLDER}" > /dev/null 2>&1
"${SCRIPT_FOLDER}/create-plots.sh" "${OUTPUT_FOLDER}" "${OUTPUT_FOLDER}/plots2"
