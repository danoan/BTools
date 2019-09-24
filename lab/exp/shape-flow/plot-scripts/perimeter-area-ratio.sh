#!/usr/bin/env bash

_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${_BASE_DIR}/gnu-config/perimeter-area-ratio.sh

_DATA_FOLDER=$(realpath $1)
_OUTPUT_FOLDER="$2" && mkdir -p ${_OUTPUT_FOLDER}
_OUTPUT_FOLDER=$(realpath $_OUTPUT_FOLDER)

shift
shift

_DATA_PLOT=""
while [ -n "$1" ]; do
    _DATA_PLOT="${_DATA_PLOT} $_DATA_FOLDER/sp_$1/mt_probe/radius_5/level_5/gs_0.50/${1}.txt $1"
    shift
done

create_multiplot "$_OUTPUT_FOLDER/perimeter-area-ratio.eps" "Perimeter-Area-Ratio" $_DATA_PLOT