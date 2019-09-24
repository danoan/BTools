#!/usr/bin/env bash

_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${_BASE_DIR}/gnu-config/elastica.sh

_SHAPE=$1
_DATA_FOLDER=$(realpath $2)
_OUTPUT_FOLDER="$3/$1" && mkdir -p ${_OUTPUT_FOLDER}
_OUTPUT_FOLDER=$(realpath $_OUTPUT_FOLDER)

_DATA_PROBE=$_DATA_FOLDER/sp_$_SHAPE/mt_probe/radius_5/level_5/gs_0.50/${_SHAPE}.txt
_DATA_IMPROVE=$_DATA_FOLDER/sp_$_SHAPE/mt_improve/radius_5/level_5/gs_0.50/${_SHAPE}.txt

create_multiplot "$_OUTPUT_FOLDER/method.eps" "Methods" \
$_DATA_PROBE "Probe" \
$_DATA_IMPROVE "Improve"
