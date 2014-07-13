#!/bin/bash

source ./share.sh

#cd .. && make

if [ -z $1 ]
then
    run_cmd "$CC $OUT network_util_test.c network_util.c $CFLAG $HEADER $LIB"
    run_ts "./test.out" del
else
    if [ $1 == 'c' ]
    then
        run_cmd "$CC $OUT network_util_test.c network_util.c $CFLAG $HEADER $LIB"
    fi
fi
