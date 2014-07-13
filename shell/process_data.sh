#!/bin/bash

while read line
do
    echo $line | \
        awk -F , '{
            for(i=1; i<=NF;i++) if(counts[$i] == "") {counts[$i] = 1} else {counts[$i]++}
            }
            END{
            for(key in counts)
                print key":"counts[key]
            }'
done < data.txt

echo "============================================="
while read line; do
    echo $line | \
        awk -F , '{
            for(i = 1; i <= NF; ++i)
                if($i in counts) {
                    counts[$i]++
                } else {
                    counts[$i] = 1
                }
        }
        END{
            for(key in counts)
                print key":"counts[key]
        }'
done < data.txt
