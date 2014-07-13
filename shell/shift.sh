if [ $# -ge 2 ]
then
    con_str=$1
    shift
    log_path=$1
    shift
    while [ $# -gt 0 ]
    do
        log_str_tmp="$log_str_tmp $1"
        shift
    done
    log_str=${log_str_tmp#" "}
fi
echo ${log_str}
