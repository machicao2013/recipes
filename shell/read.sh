#!/bin/bash

while read line
do
    if [ ! -z "$line" ]
    then
        echo "$line" | grep "^Run Summary"
        if [ $? == 0 ]
        then
            for((i = 1; i <= 3; ++i))
            do
                read line
            done
            echo $line
            resd=`echo $line | awk '{print $5}'`
            #echo $resd
            if [ ${resd:0:1} == "0" ]
            then
                echo "pass"
            else
                echo "no pass"
                #exit 1
            fi
        fi
    fi
done < result
rm -rf result

# 读取多个字段
tablename="sd_gcid_res"
MYSQL="/usr/local/mysql/bin/mysql -uroot -psnakeman sandai_hub -hdbc01 -N "
SQL="select start,end,mysqlHost,mysqlDatabase from sd_hash_table_db_map where tablename = '$tablename' order by start"
$MYSQL -e "$SQL" > log

while read start end host dbname ; do
    MYSQL="/usr/local/mysql/bin/mysql -uroot -psnakeman $dbname -h$host -N "
    for ((i=start-1; i<end; i++)); do
        SQL="create table ${tablename}_cache_$i like ${tablename}_$i"
        echo $SQL
        $MYSQL -e "$SQL"
    done
done < log

