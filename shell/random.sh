#!/bin/bash

# generate number
# echo $RANDOM

#echo "======================================"
# generate all character
# 20: the number of character
# 10: line count
#cat /dev/urandom | strings -n 20 | head -n 10

#echo "======================================="
#generate number + alpha
#cat /dev/urandom | sed 's/[^a-zA-Z0-9]//g' | strings -n 2 | head -n 10

function generate_str()
{
    MATRIX="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+="
    LENGTH="$1"
    while [ "${n:=1}" -le "$LENGTH" ]
    do
        PASS="$PASS${MATRIX:$(($RANDOM%${#MATRIX})):1}"
        let n+=1
    done
    echo $PASS
}

function generate_line()
{
    # gcid   bcid
    data="('"
    gcid=`generate_str 20`
    data=$data$gcid"','"
    bcid=`generate_str 40`
    data=$data"$bcid""')"
    echo $data
}

function generate_values()
{
    datas=""
    for ((i = 0; i < $1; ++i)); do
        data=`generate_line`
        datas=$datas","$data
    done
    echo ${datas%,}
}

