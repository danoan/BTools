#!/bin/bash

#$1: Flow root folder
#$2: Plot Title
#$3: Data file
#$4: Mode (0: Energy; 1:Energy/Length)
#$5-..: List of flow folder path relative to flow root folder

SCRIPT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
source ${SCRIPT_FOLDER}/interpixel-space.sh
source ${SCRIPT_FOLDER}/pixel-space.sh

GRAPH_PLOT_APP=${SCRIPT_FOLDER}/graph-plot.sh


SHAPE=$1
DATA_FOLDER=$2
OUTPUT_FOLDER=$3
MODE=$4

create_all_plots_pixel $1 $2 $3 $4
