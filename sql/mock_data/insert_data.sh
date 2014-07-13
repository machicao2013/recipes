#!/bin/bash

# include other functions shell
. /home/maxingsong/reposity/codesnipets/sql/mock_data/random.sh

MYSQL="mysql -uroot -p945497622 -h127.0.0.1 test"
SQL="insert into sd_gcid_bcid_white_list values";

datas=`generate_gcid_bcid_values 100`
echo "$SQL ${datas}" | $MYSQL

SQL="insert into sd_url_cid_white_list values";
datas=`generate_url_cid_values 250`
echo "$SQL ${datas}" | $MYSQL
