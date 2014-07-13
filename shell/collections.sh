#!/bin/bash

arrays=(aa bb cc dd)

for array in ${arrays[*]}; do
    echo $array
done
