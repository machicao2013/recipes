#!/bin/sh

# add it to .git/hooks/pre-commit

base_dir=`pwd`

dirs=`find $base_dir -name "Makefile"`

for dir in $dirs; do
    echo ${dir%/*}
    cd ${dir%/*} && make -f ./Makefile clean
done
