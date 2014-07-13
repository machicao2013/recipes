CC=g++
CPPFLAG=-g -O2 -Wextra -Wall -DLOGGER -D_DEBUG
INCLUDE=-I/home/maxingsong/opt/hiredis/include -I/home/maxingsong/opt/log4cplus1-1-3/include/ -I/home/maxingsong/opt/gtest-1.7.0/include
LIBS=/home/maxingsong/opt/log4cplus1-1-3/lib/liblog4cplus.a /home/maxingsong/opt/hiredis/lib/libhiredis.a /home/maxingsong/opt/gtest-1.7.0/lib/libgtest.a -lpthread -lrt

target=test

all:$(target)

test:test.cpp RedisClient.cpp
	$(CC) $(CPPFLAG) $(INCLUDE) -o $@ $^ $(LIBS)

.PHONY:clean

clean:
	rm -rf *.o $(target)
