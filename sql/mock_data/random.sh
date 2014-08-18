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

function generate_gcid_line()
{
    # gcid   bcid
    data="('"
    gcid=`generate_str 20`
    data=$data$gcid"','"
    bcid=`generate_str 3000`
    data=$data"$bcid""')"
    echo $data
}

function generate_gcid_bcid_values()
{
    datas=""
    for ((i = 0; i < $1; ++i)); do
        data=`generate_gcid_line`
        datas=$datas","$data
    done
    datas=${datas%,}
    datas=${datas#,}
    echo $datas
}

function generate_url_line()
{
    # url cid gcid filesize
    data="('"
    url=`generate_str 25`
    data=$data$url"','"
    cid=`generate_str 20`
    data=$data$cid"','"
    gcid=`generate_str 20`
    data=$data$gcid"',"
    filesize=$RANDOM
    data=$data$filesize")"
    echo $data
}

function generate_url_cid_values()
{
    datas=""
    for ((i = 0; i < $1; ++i)); do
        data=`generate_url_line`
        datas=$datas","$data
    done
    datas=${datas%,}
    datas=${datas#,}
    echo $datas
}

