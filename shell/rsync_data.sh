#!/bin/sh

yesterday=$(date --date='yesterday' +'%Y%m%d')
echo "rsync -av -e ssh --progress /usr/local/statServer/log/logA root@192.168.102.100:/usr/local/statServer/fastlog/statistic.log_${yesterday}*"
echo "rsync -av -e ssh --progress /usr/local/statServer/log/logA root@192.168.102.100:/usr/local/statServer/fastlog/al_traceroute.log_${yesterday}*"
