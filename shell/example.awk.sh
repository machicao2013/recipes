#!/bin/sh

awk -F ":" 'BEGIN {
    X = 0
}
$1 !~/^tcp/ {
    X = X + 1
}
END {
    print X
}' $1

