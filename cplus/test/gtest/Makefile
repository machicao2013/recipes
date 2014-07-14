CC=g++
INCLUDE=-I/home/maxingsong/opt/gtest-1.7.0/include
LIBS=-L/home/maxingsong/opt/gtest-1.7.0/lib -lgtest -lpthread
CPPFLAGS=-Werror -g -Wall -Wextra

target=string_test common_test
.PHONY:all

all:$(target)

string_test: string_test.cpp SDBase64Code.cpp
	$(CC) $(CXXFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)

common_test: common_test.cpp
	$(CC) $(CXXFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)

clean:
	- rm -rf *.o $(target)
