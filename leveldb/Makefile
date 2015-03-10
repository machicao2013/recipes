CC=g++
INCLUDE=-I/home/maxingsong/opt/gtest/include -I/home/maxingsong/opt/leveldb/include
LIBS=/home/maxingsong/opt/gtest/lib/libgtest.a /home/maxingsong/opt/leveldb/lib/libleveldb.a -lpthread
CPPFLAGS=-Werror -g -O2 $(INCLUDE)

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

target=$(OBJS)

.PHONY:all

all:$(target)

%.o:%.cpp
	$(CC) $(CPPFLAGS) -o $@ $< $(LIBS)

clean:
	- rm -rf *.o $(target)
