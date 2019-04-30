#!/usr/bin/env bash

APP="$HOME/GIT/PhD/BinOCS/cmake-build-debug/modules/Applications/shape-flow/shape-flow"

IT=100

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q 1.0 -t 0 -g 0 -m improve -o -S triangle \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/triangle

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S square \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/square

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S pentagon \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/pentagon

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S heptagon \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/heptagon

wait

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S ball \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/ball

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S flower \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/flower

$APP -r 3 -i $IT -a pixel -c pixel -s pixel -p double -n 4 \
-l -2 -q1.0 -t0 -g0 -m improve -o -S ellipse \
/home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/shape-flow/output/ellipse