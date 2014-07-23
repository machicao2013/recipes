CC=g++
INCLUDE=-I/home/maxingsong/opt/log4cplus1-1-3/include/
LIBS=/home/maxingsong/opt/log4cplus/lib/liblog4cplus.a -lpthread
CXXFLAGS=-Werror -g

target=test_log4cplus
.PHONY:all

all:$(target)

test_log4cplus: test_log4cplus.cpp
	$(CC) $(CPPFLAGS) -o $@ test_log4cplus.cpp $(INCLUDE) $(LIBS)

clean:
	- rm -rf *.o $(target) ./log/*
