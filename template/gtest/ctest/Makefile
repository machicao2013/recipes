CC=g++
INCLUDE=-I/home/maxingsong/opt/gtest-1.7.0/include
LIBS=-L/home/maxingsong/opt/gtest-1.7.0/lib -lgtest -lpthread
CPPFLAGS=-Werror -g

target=tests
.PHONY:all

all:$(target)

tests: tests.cpp
	$(CC) $(CPPFLAGS) -o $@ tests.cpp $(INCLUDE) $(LIBS)

clean:
	- rm -rf *.o $(target)
