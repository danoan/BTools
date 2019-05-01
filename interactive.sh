#!/usr/bin/env bash

PROJECT_FOLDER=$PWD
GRAB_CUT_APP="${PROJECT_FOLDER}/cmake-build-debug/modules/Applications/grabcut/grab-cut"
SEED_PICKER_APP="${PROJECT_FOLDER}/cmake-build-debug/modules/Applications/seed-selector/seed-selector"

INPUT_IMAGE=$(realpath $1)

IMAGE_NAME=$(basename $INPUT_IMAGE | grep ".*\." -o | tr -d ".")
TEMP_FOLDER=$(realpath .temp)

echo $IMAGE_NAME
SP_OUT="${TEMP_FOLDER}/${IMAGE_NAME}"

mkdir $TEMP_FOLDER

    ${SEED_PICKER_APP} -o ${INPUT_IMAGE} $TEMP_FOLDER
    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/cow2.xml" -u "${SP_OUT}/mask-pbfg-0.pgm" -s

while :
do
    ${SEED_PICKER_APP} -o ${INPUT_IMAGE} $TEMP_FOLDER -u "${SP_OUT}/mask-pbfg-0.pgm" -f "${SP_OUT}/mask-fg-0.pgm" -b "${SP_OUT}/mask-bg-0.pgm"
    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/cow2.xml" -u "${SP_OUT}/mask-pbfg-0.pgm" -s
done

rm -rf $TEMP_FOLDER