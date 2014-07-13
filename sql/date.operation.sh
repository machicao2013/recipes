!/bin/sh

echo "today"
today=$(date +"%Y%m%d")
year=$(date  +"%Y")
month=$(date +"%m")
day=$(date +"%d")
echo date: $date
echo year: $year
echo month: $month
echo day: $day

echo ""
echo " yesterday"
date=$(date -d"$days days ago" +"%Y%m%d")
year=$(date -d"$days days ago" +"%Y")
month=$(date -d"$days days ago" +"%m")
day=$(date -d"$days days ago" +"%d")
seconds=$(date -d"${yesterday} 23:59:59" +"%s")
echo date: $date
echo year: $year
echo month: $month
echo day: $day
echo seconds: $seconds

echo ""
echo "two days ago:"
date=`date -d -2day +"%Y%m%d"`
year=`date -d -2day +"%Y"`
month=`date -d -2day +"%m"`
day=`date -d -2day +"%d"`
echo date: $date
echo year: $year
echo month: $month
echo day: $day

