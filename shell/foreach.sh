#!/bin/sh

db_names=`cat <<end
17173_stats
sd_al_mode_statistic
sd_al_stat_summary
sd_bcid_info_stat
sd_bt_query_server_statistic
sd_cid_downtimes
sd_conn_stat_summary
sd_connect_info_statistic
sd_crack_stat_summary
sd_idle_detector_stat
sd_idle_mode1_peerid
sd_idle_mode2_peerid
sd_new_query_server_statistic
sd_old_query_server_statistic
sd_p2p_cloud_stat_summary
sd_p2p_network_summary
sd_p2p_stat_summary
sd_p2perr_stat_summary
sd_p2pobj_stat_summary
sd_ptl_stat_summary
sd_router_info_statistic
sd_server_res_statistic
sd_traceroute_stat_summary
sd_ttl_stat_summary
sd_upload_accelerate_stat
sd_url_info_stat
xl_speed_stats
end`
#echo $db_names

for db_name in $db_names
do
    #echo $db_name
    count=`grep $db_name *.cpp | wc -l`
    if [ $count -ne 0 ]
    then
        echo $db_name:$count
    fi
done
