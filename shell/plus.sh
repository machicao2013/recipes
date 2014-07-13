#!/bin/bash

n=1
echo -n "$n "
echo

let "n = $n + 1"
echo $n

((n = n + 1))
echo $n

: $[ n = $n + 1 ]
echo $n

let "n++"
echo $n

((n++))
echo $n
