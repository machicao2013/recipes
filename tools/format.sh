#!/bin/sh
#################################################
# 该文件调用 astyle 工具，实现代码的格式化，设置
# 了一些默认的参数，可以通过命令行再增加参数，如
# 使用递归的 -r 参数等。
#################################################

if [ $# -ge 1 ]; then
    CMD_OPS=$*
else
    echo "too less param..."
    echo " eg: ${0} a.cpp"
    echo "-r: recursive process subdirectories."
    echo " eg: ${0} -r \"\${DIR}/\\*.cpp \${DIR}/\\*.h\""
    exit
fi

FORMAT_OPS="--style=linux
--indent=spaces=4
--convert-tabs
--lineend=linux
--add-brackets
--attach-inlines
--indent-namespaces
--indent-switches
--indent-preprocessor
--indent-col1-comments
--delete-empty-lines
--max-code-length=150
--break-after-logical
--align-pointer=name
--align-reference=name"

astyle ${FORMAT_OPS} ${CMD_OPS}
