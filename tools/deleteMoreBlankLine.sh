#!/bin/bash

PWD=`pwd`
# 如果有连续的两个或者多个，删除部分空行，留一个
files=(`find ${PWD} -type f -a -name "*.cpp" -o -name "*.h"`)

function processFile()
{
    file=$1
    echo "process $file ing..."
    cat /dev/null > $file
    has_blank=0
    while IFS= ; read -r line; do
        if [[ "a" == "a$line" ]]; then
            has_blank=1
            echo "$line">>${file}
            while read -r line; do
                if [[ "a" == "a$line" ]]; then
                    continue
                else
                    has_blank=0
                    echo "$line">>${file}
                    break
                fi
            done
        else
            echo "$line">>${file}
        fi
    done < ${file}.orig
}

for file in ${files[*]}; do
    cp ${file} ${file}.orig
    processFile ${file}
    rm -rf ${file}.orig
done
