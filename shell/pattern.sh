#!/bin/bash

x="a1 b1 c2 d2"
echo "x = ${x}"

echo -n '${x#*1}:'
echo ${x#*1}        #从PARAMETER 扩展后的值的开头删除最短的匹配模式

echo -n '${x##*1}:'
echo ${x##*1}

echo -n '${x%1*}:'
echo ${x%1*}

echo -n '${x%%1*}:'
echo ${x%%1*}

echo -n '${x/1/3}:'
echo ${x/1/3}

echo -n '${x//1/3}:'
echo ${x//1/3}

echo -n '${x//?1/z3}:'
echo ${x//?1/z3}

echo -n '${x#$}:'
echo ${x#$}

echo -n '${x#@}:'
echo ${x#@}
