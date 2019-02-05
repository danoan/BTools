#!/bin/bash

MAX_IT=50
PROJECT_FOLDER=/home-local/dantu1/GIT/PhD/BTools
FLOW_SCRIPTS=${PROJECT_FOLDER}/exp/flows

#bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} probe "probe" opt
#wait
#bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} probe "probe" around
#wait
bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} improve "improve" opt
wait
bash ${FLOW_SCRIPTS}/pixel-space.sh ${MAX_IT} improve "improve" around
wait


#bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" opt
#wait
#bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} probe "probe" inner
#wait
bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} improve "improve" opt
wait
bash ${FLOW_SCRIPTS}/linels.sh ${MAX_IT} improve "improve" inner
wait

