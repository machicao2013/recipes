#!/bin/sh

filename="tablenames"

while read tablename ; do
  echo $tablename
  sql="/usr/local/mysql/bin/mysql -uroot sandai_hub -hdbc02 -A -e \"truncate table $tablename\""
  echo $sql | sh
done  < "$filename"
