#!/usr/bin/env bash

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${BASE_DIR}/gnu-config/elastica.sh

SHAPE=$1
DATA_FOLDER=$(realpath $2)
OUTPUT_FOLDER="$3/$1" && mkdir -p ${OUTPUT_FOLDER}
OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

DATA_LEVEL_1=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_1/gs_0.50/${SHAPE}.txt
DATA_LEVEL_2=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_2/gs_0.50/${SHAPE}.txt
DATA_LEVEL_3=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_3/gs_0.50/${SHAPE}.txt
DATA_LEVEL_4=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_4/gs_0.50/${SHAPE}.txt
DATA_LEVEL_5=$DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${SHAPE}.txt

create_multiplot "$OUTPUT_FOLDER/levels.eps" "Levels"  \
$DATA_LEVEL_1 "Level_1" \
$DATA_LEVEL_2 "Level_2" \
$DATA_LEVEL_3 "Level_3" \
$DATA_LEVEL_4 "Level_4" \
$DATA_LEVEL_5 "Level_5"