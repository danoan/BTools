#!/usr/bin/env bash

PROJECT_FOLDER=$1
BINARY_FOLDER=$PROJECT_FOLDER/$2

IMAGE_FOLDER=$PROJECT_FOLDER/images
INPUT_FOLDER=$PROJECT_FOLDER/modules/lab/exp/boundary-correction/input

function grabcut()
{
    IMAGE_NAME=$1
    BASE_FOLDER=$INPUT_FOLDER/$IMAGE_NAME

    echo "Creating gcobject for $IMAGE_NAME..."

    $BINARY_FOLDER/grab-cut $IMAGE_FOLDER/$IMAGE_NAME.jpg \
    $BASE_FOLDER/mask-fg-0.pgm \
    $BASE_FOLDER/mask-bg-0.pgm \
    $BASE_FOLDER/gc-object.xml \
    -u $BASE_FOLDER/mask-pbfg-0.pgm
}

grabcut butterfly
grabcut cow
grabcut giraffe
grabcut honeybee

