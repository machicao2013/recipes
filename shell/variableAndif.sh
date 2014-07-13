#!/bin/sh

# $#: the number of arguments
if [ $# -lt 3 ]; then
cat <<HELP
    echo "the number of arguments less than 3"
HELP
    exit 0
fi

# 除了$0外，其它所有的参数
for file in $*; do
    if [ -f $file ]; then
        echo $file
    else
        echo "$file not exists"
    fi
done
