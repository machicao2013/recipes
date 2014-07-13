#!/usr/bin/awk -f

BEGIN {
    X = 0
}
$1 !~ /^tcp/ {
    X = X + 1
}
END {
    print X
}

