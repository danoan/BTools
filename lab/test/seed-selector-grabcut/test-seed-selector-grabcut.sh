#!/bin/bash
SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PROJECT_FOLDER="$( cd "$SCRIPT_FOLDER" && cd ../../.. && pwd)"
BIN_FOLDER="$( cd "${PROJECT_FOLDER}/install/bin" && pwd)"
INPUT_FOLDER="${SCRIPT_FOLDER}/input"
OUTPUT_FOLDER="${SCRIPT_FOLDER}/output"

mkdir -p "$OUTPUT_FOLDER"

"${BIN_FOLDER}/seed-selector" "${INPUT_FOLDER}/coala.jpg" "${OUTPUT_FOLDER}" -u"${INPUT_FOLDER}/mask-pbfg-0.pgm" -f"${INPUT_FOLDER}/mask-fg-0.pgm" -b"${INPUT_FOLDER}/mask-bg-0.pgm" -T"+-pbfsrq"
"${BIN_FOLDER}/grab-cut" "${INPUT_FOLDER}/coala.jpg" "${INPUT_FOLDER}/mask-fg-0.pgm" "${INPUT_FOLDER}/mask-bg-0.pgm" "${OUTPUT_FOLDER}/gc-object.xml" -i1 -u"${INPUT_FOLDER}/mask-pbfg-0.pgm" -o"${OUTPUT_FOLDER}/gc-seg.png"
