#!/usr/bin/env bash

_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${_BASE_DIR}/gnu-config/elastica.sh

_SHAPE=$1
_DATA_FOLDER=$(realpath $2)
_OUTPUT_FOLDER="$3/$1" && mkdir -p ${_OUTPUT_FOLDER}
_OUTPUT_FOLDER=$(realpath $_OUTPUT_FOLDER)

_DATA_LEVEL_1=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_1/gs_0.50/${_SHAPE}.txt
_DATA_LEVEL_2=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_2/gs_0.50/${_SHAPE}.txt
_DATA_LEVEL_3=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_3/gs_0.50/${_SHAPE}.txt
_DATA_LEVEL_4=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_4/gs_0.50/${_SHAPE}.txt
_DATA_LEVEL_5=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_5/gs_0.50/${_SHAPE}.txt

create_multiplot "$_OUTPUT_FOLDER/levels.eps" "Levels"  \
$_DATA_LEVEL_1 "Level_1" \
$_DATA_LEVEL_2 "Level_2" \
$_DATA_LEVEL_3 "Level_3" \
$_DATA_LEVEL_4 "Level_4" \
$_DATA_LEVEL_5 "Level_5"