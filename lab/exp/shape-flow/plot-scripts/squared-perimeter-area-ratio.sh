#!/usr/bin/env bash

_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${_BASE_DIR}/gnu-config/squared-perimeter-area-ratio.sh

_SHAPE=$1
_RADIUS=$2
_GS=$3
_UP=$4
_NLEVELS=$5

_DATA_FOLDER=$(realpath $6)
_OUTPUT_FOLDER="$7" && mkdir -p ${_OUTPUT_FOLDER}
_OUTPUT_FOLDER=$(realpath $_OUTPUT_FOLDER)

_NLEVELS=$( decode_interval $_NLEVELS )

_DATA_PLOT=""
for i in $_NLEVELS
do
    _DATA_PLOT="$_DATA_PLOT $_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_$_RADIUS/level_$i/gs_$_GS/up_$_UP/${_SHAPE}.txt Level_$i "
    i=$(($i-1))
done

create_multiplot "$_OUTPUT_FOLDER/${_SHAPE}-squared-perimeter-area-ratio.eps" "Squared-Perimeter-Area-Ratio" $_DATA_PLOT