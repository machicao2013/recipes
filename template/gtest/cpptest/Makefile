CC=g++
INCLUDE=-I/home/maxingsong/opt/gtest-1.7.0/include
LIBS=-L/home/maxingsong/opt/gtest-1.7.0/lib -lgtest -lpthread
CPPFLAGS=-Werror -g -Wall -Wextra

target=oo_test
.PHONY:all

all:$(target)

oo_test: oo_test.cpp FooCalc.cpp
	$(CC) $(CPPFLAGS) -o $@ oo_test.cpp FooCalc.cpp $(INCLUDE) $(LIBS)

clean:
	- rm -rf *.o $(target)
