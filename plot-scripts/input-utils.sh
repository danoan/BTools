#!/usr/bin/env bash

function decode_interval()
{
    INPUT_INTERVAL="$1"

    intervalBegin="$(echo "$INPUT_INTERVAL" | cut -d":" -f1)"
    intervalEnd="$(echo "$INPUT_INTERVAL" | cut -d":" -f2)"

    i="$intervalBegin"
    decode=""
    while [ "$i" -le "$intervalEnd" ]
    do
        decode="$decode $i "
        i=$(("$i"+1))
    done

    echo "$decode"
}