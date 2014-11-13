#!/bin/bash

INSTALL_DIR=/home/maxingsong/opt/vim74/

test -d ${INSTALL_DIR} || mkdir -p ${INSTALL_DIR}

if [[ "a`whoami`" != "aroot" ]]; then
    echo "You must be root"
    exit 1
fi

if [[ ! -f ./vim-7.4.tar.bz2 ]]; then
    # Bugfix: download
    exit 0
fi

yum install -y ruby ruby-devel lua lua-devel luajit luajit-devel ctags mercurial python python-devel python3 python3-devel tcl-devel \
    perl perl-devel perl-ExtUtils-ParseXS perl-ExtUtils-XSpp perl-ExtUtils-CBuilder perl-ExtUtils-Embed

tar jxvf ./vim-7.4.tar.bz2

cd ./vim74/

./configure --with-features=huge --enable-rubyinterp --enable-pythoninterp --with-python-config-dir=/usr/lib64/python2.6/config/ --enable-perlinterp --enable-gui=gtk2 --enable-cscope --enable-luainterp --enable-perlinterp --enable-multibyte --prefix=${INSTALL_DIR}

make && make install

chown -R maxingsong:maxingsong ${INSTALL_DIR}/*
