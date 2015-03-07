#!/bin/sh

awk -F ":" 'BEGIN {
    X = 0
}
$1 !~/^tcp/ {
    X = X + 1
}
END {
    print X
}' $1

# 向awk传递shell变量

totoal_line=20

awk -v max_line=${totoal_line} 'BEGIN {
    cur_line = 0
}
{
    if(cur_line < max_line) {
        print $1
        print $2
    }
    cur_line++
}
END {
    print cur_line
}' $0

echo "===================="

# 在awk中打印‘和"

awk 'BEGIN {
    cur_line = 0
}
{
    if(cur_line < 15) {
        print "'\''"$0"'\''"
    } else {
        print "\""$0"\""
    }
    cur_line++
}' $1

