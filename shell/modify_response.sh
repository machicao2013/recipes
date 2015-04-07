#!/bin/bash

for file in `ls *response_proxy.h`; do
    sed -i '/get_message_type/a\    virtual void set_error_message(const std::string &);' ${file}
done

function get_class_name()
{
    file_name="$1"
    file_name=${file_name%.cpp}

    results1=`echo ${file_name} | awk -F "_" '{for(i=1; i <=NF; i++) print $i}' | sed 's/^\(.\)/\u\1/'`
    results2=`echo ${file_name} | awk -F "_" '{for(i=1; i <NF; i++) print $i}' | sed 's/^\(.\)/\u\1/'`

    local result1=
    local result2=

    for tmp in ${results1}; do
        result1="${result1}${tmp}"
    done
    for tmp in ${results2}; do
        result2="${result2}${tmp}"
    done

    echo "${result1} ${result2}"
}

for file in `ls *response_proxy.cpp`; do
    result=(`get_class_name ${file}`)
    class_name=${result[0]}
    message_name=${result[1]}
    cat content | sed -e "s;FlushBcidInfoResponseProxy;${class_name};g" -e "s;FlushBcidInfoResponse;${message_name};g" >> ${file}
done

