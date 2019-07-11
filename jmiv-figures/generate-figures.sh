#!/usr/bin/env bash

SCRIPT_FOLDER=$( cd $(dirname ${BASH_SOURCE[0]}) >/dev/null 2>&1 && pwd)

BTOOLS_BIN=$(realpath $1)
EXT_BIN=$(realpath $2)

${SCRIPT_FOLDER}/fig1/jmiv-fig1.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig2-3/jmiv-fig2.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig4/jmiv-fig4.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig5/jmiv-fig5.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig6/jmiv-fig6.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig7/jmiv-fig7.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig8-9/jmiv-fig8.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig10/jmiv-fig10.sh ${BTOOLS_BIN} ${EXT_BIN}
${SCRIPT_FOLDER}/fig11-12/jmiv-fig11.sh ${BTOOLS_BIN} ${EXT_BIN}