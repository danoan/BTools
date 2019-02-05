#!/bin/sh

#$1: Flow root folder
#$2: Plot Title
#$3: Data file
#$4: Mode (0: Energy; 1:Energy/Length)
#$5-..: List of flow folder path relative to flow root folder

MY_PROJECT_FOLDER="/home-local/dantu1/GIT/PhD/BTools"
GRAPH_PLOT_APP="${MY_PROJECT_FOLDER}/exp/utils/graph-plot.sh"

MAIN_FOLDER=${1}; shift;
TITLE=${1}; shift;
DATA_FILENAME=${1}; shift;
MODE=${1}; shift;

NUM_FLOWS=${#}

PLOT_FOLDER=${MAIN_FOLDER}/plots/mode-${MODE}
mkdir -p $PLOT_FOLDER

cmd="${GRAPH_PLOT_APP} ${PLOT_FOLDER}/${TITLE}.eps ${TITLE} $MODE "
i=0

while [ $i -lt $NUM_FLOWS ]
do
    if [ "$1" != "plots" ]
    then
        DATA_FILE_FOLDER=${MAIN_FOLDER}/${1}
        cmd="${cmd} ${DATA_FILE_FOLDER}/${DATA_FILENAME} ${1} "
    fi

    shift
    i=`expr $i + 1`
done

$cmd