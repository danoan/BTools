#!/usr/bin/env bash


_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${_BASE_DIR}/gnu-config/elastica.sh

_SHAPE=$1
_DATA_FOLDER=$(realpath $2)
_OUTPUT_FOLDER="$3/$1" && mkdir -p ${_OUTPUT_FOLDER}
_OUTPUT_FOLDER=$(realpath $_OUTPUT_FOLDER)

_DATA_RADIUS3=$_DATA_FOLDER/sp_$SHAPE/mt_improve/radius_3/level_3/gs_0.50/${_SHAPE}.txt
_DATA_RADIUS5=$_DATA_FOLDER/sp_$SHAPE/mt_improve/radius_5/level_5/gs_0.50/${_SHAPE}.txt

create_multiplot "$_OUTPUT_FOLDER/radius.eps" "Radius_3_x_Radius_5" \
$_DATA_RADIUS3 "Radius_3" \
$_DATA_RADIUS5 "Radius_5"