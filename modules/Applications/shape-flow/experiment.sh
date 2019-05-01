#!/usr/bin/env bash

SF_APP=$1
OUTPUT_FOLDER=$2

IT=100

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q 1.0 -t 0 -g 0 -m improve -o -S triangle \
$OUTPUT_FOLDER/triangle&

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S square \
$OUTPUT_FOLDER/square&

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S pentagon \
$OUTPUT_FOLDER/pentagon&

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S heptagon \
$OUTPUT_FOLDER/heptagon&

wait

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S ball \
$OUTPUT_FOLDER/ball&

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S flower \
$OUTPUT_FOLDER/flower&

$SF_APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S ellipse \
$OUTPUT_FOLDER/ellipse