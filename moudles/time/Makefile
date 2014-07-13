CC=g++
INCLUDE=-I/home/maxingsong/opt/gtest-1.7.0/include
LIBS=-L/home/maxingsong/opt/gtest-1.7.0/lib -lgtest -lpthread
CXXFLAGS=-Werror -g

target=test
.PHONY:all

all:$(target)

test: test.cpp Date.cpp Date.h
	$(CC) $(CPPFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)

clean:
	- rm -rf *.o $(target)
