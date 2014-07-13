#!/bin/sh

MYSQL="/usr/local/mysql/bin/mysql -uroot -psnakeman -h10.1.1.129 -P3306 sandai_hub -A"
sql='SELECT * FROM  sd_bcid_info_4 limit 5 \G'
echo "$sql" | $MYSQL
