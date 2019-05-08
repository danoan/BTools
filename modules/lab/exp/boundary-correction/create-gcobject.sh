#!/usr/bin/env bash

PROJECT_FOLDER=$1
BINARY_FOLDER=$PROJECT_FOLDER/$2

IMAGE_FOLDER=$PROJECT_FOLDER/images
INPUT_FOLDER=$PROJECT_FOLDER/modules/lab/exp/boundary-correction/input

function grabcut()
{
    FILE_NAME=$(basename $1)
    IMAGE_NAME=${FILE_NAME%.*}
    BASE_FOLDER=$INPUT_FOLDER/$IMAGE_NAME

    echo "Creating gcobject for $IMAGE_NAME..."

    $BINARY_FOLDER/grab-cut $IMAGE_FOLDER/$FILE_NAME \
    $BASE_FOLDER/mask-fg-0.pgm \
    $BASE_FOLDER/mask-bg-0.pgm \
    $BASE_FOLDER/gc-object.xml \
    -u $BASE_FOLDER/mask-pbfg-0.pgm
}

grabcut butterfly.jpg
grabcut cow.jpg
grabcut giraffe.jpg
grabcut honeybee.jpg
grabcut cameraman.png
grabcut quixote.pgm
