#!/bin/sh

today_day=$(date -d -1day +"%d")

backup_tables=`cat <<end
sd_upload_accelerate_stat
end`

if [ ${today_day} = "01" ]; then
    for table in $backup_tables; do
        echo $table
    done
else
    echo "today is not 01"
fi
