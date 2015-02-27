#!/bin/bash

# 获取END的前一行和后面的三行
grep -A1 -B3 END example.awk
