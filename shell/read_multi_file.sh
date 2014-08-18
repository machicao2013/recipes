#!/bin/bash
# 同时读取file1 file2 file3的内容
while read -u3 a1 b1 && read -u4 a2 b2 && read -u5 a3 b3;do
    echo $a $b $c
done 3<file1 4<file2 5<file3
