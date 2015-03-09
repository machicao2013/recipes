#!/bin/sh

awk '
{
    for(i=1; i <= NF; i++) {
        counts[$i]++
    }
}
END{
    for(key in counts) {
        print key"\t"counts[key]
    }
}' < $1
