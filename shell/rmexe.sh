#!/bin/bash

if [ $# -eq 0 ]; then
    find . -perm -u=x -a -type f #| xargs rm -vf
elif [ $# -eq 1 ]; then
    find "$1" -perm -u=x -a -type f #| xargs rm -vf
else
    echo "$0 " "path"
fi
