#!/bin/sh

DATE=`date +"%Y%m%d"`

config_files=`find . -name "*.conf" -o -name "*.config"`
for config_file in ${config_files}; do
        echo "========== process ${config_file} ============"
        cp ${config_file} ${config_file}_${DATE}
        sed -i 's/10.10.13.31/10.10.159.15/g' ${config_file}
        sed -i 's/10.10.13.32/10.10.159.16/g' ${config_file}
        sed -i 's/10.10.13.33/10.10.159.17/g' ${config_file}
        sed -i 's/10.10.13.34/10.10.159.18/g' ${config_file}
        sed -i 's/10.10.13.35/10.10.159.19/g' ${config_file}
        # 分隔符可以改变
        sed -i 's:10.10.13.35:10.10.159.19:g' ${config_file}
done
