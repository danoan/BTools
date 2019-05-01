#!/usr/bin/env bash

BC_APP=$1
GC_OBJ=$2
OUTPUT_FOLDER=$3

$BC_APP $GC_OBJ -r 3 -i 50 -q 1.0 -t 0.0 -g 0 -m improve \
-o $OUTPUT_FOLDER/no-data-term-it50&

$BC_APP $GC_OBJ -r 3 -i 50 -q 1.0 -t 1.0 -g 0 -m improve \
-o $OUTPUT_FOLDER/with-data-term1-it50&

$BC_APP $GC_OBJ -r 3 -i 50 -q 1.0 -t 10.0 -g 0 -m improve \
-o $OUTPUT_FOLDER/with-data-term10-it50&

$BC_APP $GC_OBJ -r 3 -i 100 -q 1.0 -t 10.0 -g 0 -m improve \
-o $OUTPUT_FOLDER/with-data-term10-it100