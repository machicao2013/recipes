#!/bin/sh

#在当前目录下有两个for开头的文件
#使用双引号可引用除字符$、`、\外的任意字符或字符串
#由单引号括起来的字符都作为普通字符出现
date="for*"
echo $date
echo "$date"
#对于bash的来说，命令的解释是从左到右的
echo '$date'
echo "'$date'"
echo '"$date"'
echo '`date`'
