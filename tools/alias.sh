#!/bin/bash
alias ll='ls -lAh'
alias gst='git status'
alias svnst='svn status'
alias glog="git log --all --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --date=relative"
alias vim="/home/maxingsong/opt/vim74/bin/vim"
alias git="/home/maxingsong/opt/git/bin/git"
alias findc='find . -name "*.c" -print0'
alias findcpp='find . -name "*.cpp" -print0'
alias findh='find . -name "*.h" -print0'
alias xgrep='xargs -0 grep'
alias findcgrep='find . -name "*.c" -print0 | xargs -0 grep'
alias findhgrep='find . -name "*.h" -print0 | xargs -0 grep'
alias findcppgrep='find . -name "*.cpp" -print0 | xargs -0 grep'
