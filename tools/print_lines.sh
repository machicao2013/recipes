#!/bin/bash

begin=""
end=""
file=""
if [[ $# -lt 2 ]]; then
    echo "$0 begin [end] fileName"
    exit -1
elif [[ $# -eq 2 ]]; then
    begin=$1
    file=$2
elif [[ $# -eq 3 ]]; then
    begin=$1
    end=$2
    file=$3
else
    echo "too many arguments"
    exit -1
fi


if [[ "AA"$end == "AA" ]]; then
    echo "sed -n '${begin}p' $file" | sh
else
    echo "sed -n '${begin},${end}p' $file" | sh
fi
