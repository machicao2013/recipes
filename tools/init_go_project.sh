#!/bin/bash

project_name=
if [ $# -ne 1 ]; then
    echo "Usage: ${0} <project_name>"
    exit 1
else
    project_name=${1}
fi

base_dir=`pwd`"/"
# echo ${base_dir}

for dir in `ls ${base_dir}`; do
    if [ "a"${dir} == "a"${project_name} ]; then
        echo "${project_name} is already exists"
        exit 1
    fi
done

mkdir -p ${base_dir}${project_name}"/src/"
mkdir -p ${base_dir}${project_name}"/bin/"
mkdir -p ${base_dir}${project_name}"/pkg/"
