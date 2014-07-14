#!/bin/bash

BASE_DIR="/home/maxingsong/opt"

MY_PATH="."
MY_LD_LIBRARY_PATH="."
for dir in `ls ${BASE_DIR}`; do
    if [[ -d ${dir}/bin ]]; then
        MY_PATH=${MY_PATH}:${dir}/bin
    fi
    if [[ -d ${dir}/lib ]]; then
        MY_LD_LIBRARY_PATH=${MY_LD_LIBRARY_PATH}:${dir}/lib
    fi
done
PATH=$MY_PATH:$PATH
LD_LIBRARY_PATH=$MY_LD_LIBRARY_PATH:$LD_LIBRARY_PATH
echo $PATH
#echo "=============================================="
#echo $LD_LIBRARY_PATH
