#!/bin/bash

find . -name "statistic.log_20140415*" |xargs ls -lsh | awk '{print $1}' | sed 's/.$//'p | awk 'BEGIN{sum=0}{sum+=$1}END{print sum/1024"G"}'
