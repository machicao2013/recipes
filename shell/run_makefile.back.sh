#!/bin/bash

. ../configure/share

HOME_DIR=`cd ../../ && pwd`

run_cmd "cd ../../"

run_cmd "./configure" > /dev/null 2>&1

for makefile in `find ${HOME_DIR} -iname "Makefile" | grep -v "redis3m/docs"`; do
    path=${makefile%\/*}
    run_cmd "cd ${path}"
    run_cmd "make"

    run_cmd "cd ${HOME_DIR}"
done

filter="cn_query|third_lib|votebox|s2s_protocol/query|s2s_protocol/updator|mshub_client_cmd|data_center/dc_query|data_channel_interface|dc_updator"
for makefile in `find ${HOME_DIR} -iname "Makefile" | grep -v "redis3m"`; do
    path=${makefile%\/*}
    run_cmd "cd ${path}"
    echo "${path}" | grep -E "${filter}"
    if [ $? -eq 0 ]; then
        if [ -e ${makefile} ]; then
            run_cmd "make clean"
        fi
    else
        run_cmd "make veryclean"
    fi
    run_cmd "cd ${HOME_DIR}"
done
