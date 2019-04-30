#!/usr/bin/env bash

APP="$HOME/GIT/PhD/BinOCS/cmake-build-debug/modules/Applications/boundary-correction/boundary-correction-app"

$APP /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/grabcut/output/cow2.xml -r 3 -i 50 -q 1.0 \
-t 0.0 -g 0 -m improve \
-o /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/boundary-correction/output/no-data-term-it50

$APP /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/grabcut/output/cow2.xml -r 3 -i 50 -q 1.0 \
-t 1.0 -g 0 -m improve \
-o /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/boundary-correction/output/with-data-term1-it50

$APP /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/grabcut/output/cow2.xml -r 3 -i 50 -q 1.0 \
-t 10.0 -g 0 -m improve \
-o /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/boundary-correction/output/with-data-term10-it50

$APP /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/grabcut/output/cow2.xml -r 3 -i 100 -q 1.0 \
-t 10.0 -g 0 -m improve \
-o /home-local/dantu1/GIT/PhD/BinOCS/modules/Applications/boundary-correction/output/with-data-term10-it100