#!/bin/bash

for (( i = 0; i < 10; i++ )); do
    echo $(expr $i \* 4)
done

echo "==================================="
for i in `ls`; do
    echo $i
done

echo "==================================="
for i in $*; do
    echo $i
done

echo "==================================="
for line in $(<for.sh); do
    echo $line
done

echo "==================================="
LIST="one two three"
for a in $LIST; do
    echo $a
done
echo "==================================="
for a in "$LIST"; do
    echo $a
done

