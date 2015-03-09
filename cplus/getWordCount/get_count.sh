#!/bin/sh

awk 'BEGIN {
    RS = " "
}
{
    counts[$1]++
}
END{
    for(key in counts) {
        print key"\t"counts[key]
    }
}' < $1
