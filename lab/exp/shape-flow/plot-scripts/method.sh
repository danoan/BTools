#!/usr/bin/env bash

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${BASE_DIR}/gnu-config/elastica.sh

SHAPE=$1
DATA_FOLDER=$(realpath $2)
OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

DATA_PROBE=$DATA_FOLDER/sp_$SHAPE/mt_probe/radius_5/level_5/gs_0.50/${SHAPE}.txt
DATA_IMPROVE=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

create_multiplot "$OUTPUT_FOLDER/method.eps" "Methods" \
$DATA_PROBE "Probe" \
$DATA_IMPROVE "Improve"
