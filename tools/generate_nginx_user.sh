#!/bin/bash

PASSWORD_FILE=./etc/htpasswd.conf

[[ ! -d `dirname ${PASSWORD_FILE}` ]] && mkdir -p `dirname ${PASSWORD_FILE}`
[[ ! -f $PASSWORD_FILE ]] && touch $PASSWORD_FILE

while read username password; do
    htpasswd -b -d ${PASSWORD_FILE} $username $password
done << EOF
maxingsong      maxingsong123
yezhihui        yezhihui123
shenbo          shenbo123
yaochenggang    yaochenggang123
yueyizhen       yueyizhen123
liyan           liyan123
zhuwen          zhuwen123
qiuzhicong      qiuzhicong123
zhouenjie       zhouenjie123
chenbaiheng     chenbaiheng123
EOF
