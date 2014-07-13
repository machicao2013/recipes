#!/bin/sh

backup_table_date=$(date -d -1day +"%Y%m")
today_day=$(date +"%d")

backup_tables=`cat <<end
sd_upload_accelerate_stat
end`

MYSQL="/usr/bin/mysql -uroot -p945497622 -hlocalhost student_db"

if [ "$today_day" = "01" ]; then
    echo "========  begin backup table  ==========="
    for table_name in $backup_tables; do
        sql="RENAME TABLE $table_name to $table_name$backup_table_date"
        echo "   $sql"
        echo $sql | $MYSQL
        sql="CREATE TABLE $table_name LIKE $table_name$backup_table_date"
        echo "   $sql"
        echo $sql | $MYSQL
    done
    echo "========  end backup table   ==========="
fi


