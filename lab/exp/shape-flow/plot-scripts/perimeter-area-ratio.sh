#!/usr/bin/env bash

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${BASE_DIR}/gnu-config/perimeter-area-ratio.sh

DATA_FOLDER=$(realpath $1)
OUTPUT_FOLDER="$2" && mkdir -p ${OUTPUT_FOLDER}
OUTPUT_FOLDER=$(realpath $OUTPUT_FOLDER)

shift
shift

DATA_PLOT=""
while [ -n "$1" ]; do
    DATA_PLOT="${DATA_PLOT} $DATA_FOLDER/sp_$1/mt_probe/radius_5/level_5/gs_0.50/${1}.txt $1"
    shift
done

create_multiplot "$OUTPUT_FOLDER/perimeter-area-ratio.eps" "Perimeter-Area-Ratio" $DATA_PLOT