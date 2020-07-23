#!/bin/sh

#SCRIPT_DIR defined in the docker image dipacus:env

./lab/test/seed-selector-grabcut/test-seed-selector-grabcut.sh
./lab/test/segmentation/test-segmentation.sh "${SRC_DIR}/install/bin"
./lab/test/shape-flow/test-shape-flow.sh "${SRC_DIR}/install/bin" "${SRC_DIR}/lab/test/shape-flow/output"
