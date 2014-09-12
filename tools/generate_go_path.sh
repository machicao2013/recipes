#!/bin/bash

GOPATH=
path_root="/home/maxingsong/reposity/gotest/source/"

dirs=`ls ${path_root}`

for dir in ${dirs}; do
    if [ -d ${path_root}${dir} ]; then
        GOPATH=${GOPATH}${path_root}${dir}":"
    fi
done
echo ${GOPATH}
echo ${GOPATH%%:}
