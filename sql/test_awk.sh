#!/bin/bash

while read line; do
    array=(`echo ${line} | awk '{print $1,$2,$3}'`)
    echo ${array[0]},${array[1]},${array[2]}
done < message
