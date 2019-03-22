#!/bin/bash

MAX_IT=100
PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
FLOW_SCRIPTS=${PROJECT_FOLDER}/exp/flows

#--------------LINELS---------------
for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" inner no-opt $l
    wait
done

for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" inner add-opt $l
    wait
done


for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" around-inner no-opt $l
    wait
done

for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" around-inner add-opt $l
    wait
done



#--------------PIXELS---------------
for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} probe "probe" opt no-opt $l closer
    wait
done

for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} probe "probe" around no-opt $l farther
    wait
done

for l in 0 0.5 1.0 2.0
do
    bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} probe "probe" around no-opt $l closer
    wait
done
