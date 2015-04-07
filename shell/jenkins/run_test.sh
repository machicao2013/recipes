#!/bin/bash

. ../configure/share

HOME_DIR=`cd ../../ && pwd`

run_cmd "cd ../../"

run_cmd "./configure" > /dev/null 2>&1

for testcase in `find ${HOME_DIR} -name "runtest.sh"`; do
    path=${testcase%\/*}
    exe="./${testcase##*\/}"
    run_cmd "cd ${path}"
    run_cmd "${exe}"
    run_cmd "cd ${HOME_DIR}"
done

