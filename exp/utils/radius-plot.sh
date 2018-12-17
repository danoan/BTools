#!/bin/sh

#$1: Flow root folder
#$2: Plot Title
#$3: Data file
#$4: Mode (0: Energy; 1:Energy/Length)
#$5-..: List of flow folder path relative to flow root folder

PROJECT_FOLDER="/home-local/dantu1/GIT/PhD/BTools"
GRAPH_PLOT_APP="${PROJECT_FOLDER}/exp/utils/graph-plot.sh"

MAIN_FOLDER=${1}; shift;
TITLE=${1}; shift;
DATA_FILENAME=${1}; shift;
MODE=${1}; shift;

NUM_FLOWS=${#}

cmd="${GRAPH_PLOT_APP} ${MAIN_FOLDER}/${TITLE}.eps ${TITLE} $MODE "
i=0

while [ $i -lt $NUM_FLOWS ]
do
    cmd="${cmd} ${MAIN_FOLDER}/${1}/${DATA_FILENAME} ${1} "
    shift
    i=`expr $i + 1`
done

$cmd