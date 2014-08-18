CC="cc"
CFLAG="-Werror -g -std=gnu99 -D_GNU_SOURCE -DTESTMODE"
HEADER="-I/home/maxingsong/opt/CUnit/include/"
LIB="-L/home/maxingsong/opt/CUnit/lib -lcunit"
OUT="-o test.out"

cputs()
{
    printf "\033[01;36;40m$1\033[00m\n"
}

gputs()
{
    printf "\033[01;32m$1\033[00m\n"
}

yputs()
{
    printf "\033[01;33m$1\033[00m\n"
}

rputs()
{
    printf "\033[01;31;40m$1\033[00m\n"
}

puts_title()
{
    printf "\033[07;34;43m$1\033[00m\n"
}

warn_puts()
{
    printf "\033[01;33;41m$1\033[00m\n"
}

green_color()
{
    printf "\033[07;30;42m"
}

reset_color()
{
    printf "\033[00m"
}

run_cmd()
{
    printf "\033[01;32m$1\033[00m\n"
    printf "\033[01;30;40m"
    $1
    if [ $? != 0 ]
    then
        printf "\033[01;33;41mFailed: $1\033[00m\n"
        exit 1
    fi
    printf "\033[00m"
}

run_ts()
{
    rm -rf data
    if [ -x $1 ]
    then
        CNT=$[ $CNT + 1 ]
        printf "\n                "
        puts_title "[$CNT] $1"
        $1 | sed -n '7,$p' | perl -lne 's/asserts(\s+\d+)(\s+\d+)(\s+\d+)(\s+\d+)(\s+.*)$/asserts\033[01;32m\1\033[00m\033[01;32m\2\033[00m\033[01;34m\3\033[00m\033[01;31m\4\033[00m\033[01;32m\5\033[00m/g; s!^(stat:.+)!\033[04;36;40m\1\033[00m!; print;'
    else
        warn_puts "\n ####### $1 doesn't exists ########\n"
        exit
    fi

    if [ $2 ]
    then
        rm -f $1
    fi
}

# vim: foldmethod=marker
