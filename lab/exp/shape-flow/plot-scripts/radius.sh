#!/usr/bin/env bash


BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${BASE_DIR}/gnu-config/elastica.sh

SHAPE=$1
DATA_FOLDER=$(realpath $2)
OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

DATA_RADIUS3=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_3/level_3/gs_0.50/${SHAPE}.txt
DATA_RADIUS5=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

create_multiplot "$OUTPUT_FOLDER/radius.eps" "Radius_3_x_Radius_5" \
$DATA_RADIUS3 "Radius_3" \
$DATA_RADIUS5 "Radius_5"